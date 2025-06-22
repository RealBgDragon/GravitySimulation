#include "CircleObjects.h"

CircleObjects::CircleObjects(Renderer* renderer) {
	this->renderer = renderer;
}

CircleObjects::~CircleObjects() {

	glDeleteVertexArrays(1, &circleVAO);
	glDeleteBuffers(1, &circleVBO);

}

void CircleObjects::init(int segments, float r, float centerX, float centerY, double mass, double xAcceleration, double yAcceleration) {

	this->segments = segments;
	this->r = r;
	this->centerX = centerX;
	this->centerY = centerY;
	this->mass = mass;

	velocity = glm::dvec2(xAcceleration, yAcceleration);

}

void CircleObjects::draw() {
	renderer->setUpCircle(segments, r, centerX, centerY, circleVAO, circleVBO, initialized);
	initialized = true;
	renderer->renderCircle(segments, circleVAO);
}

void CircleObjects::applyGravity(CircleObjects& other) {
	glm::vec2 posA(centerX, centerY);
	glm::vec2 posB(other.centerX, other.centerY);

	glm::vec2 direction = posB - posA;
	double distanceSquared = glm::dot(direction, direction);

	double distance = sqrt(distanceSquared);

	//TODO Make it so it checks for future colision
	if (distance <= r) {
		std::cout << "Colision" << std::endl;
		velocity = -velocity;
		other.velocity = -other.velocity;
		return;
	}

	glm::dvec2 forceDirection = glm::normalize(direction);

	double forceMagnitude = (G * mass * other.mass) / distanceSquared;
	glm::dvec2 force = forceDirection * forceMagnitude;

	acceleration += force / mass;
}

void CircleObjects::update(float deltaTime, std::vector<CircleObjects>& allObjects) {

	acceleration = glm::vec2(0.0f);

	if (centerY < -1) {
		centerY = -1;
		velocity.y = -velocity.y;
	}
	else if (centerY > 1) {
		centerY = 1;
		velocity.y = -velocity.y;
	}

	if (centerX < -1) {
		centerX = -1;
		velocity.x = -velocity.x;
	}
	else if (centerX > 1) {
		centerX = 1;
		velocity.x = -velocity.x;
	}

	for (CircleObjects& other : allObjects) {
		if (&other != this) {
			applyGravity(other);
		}
	}

	//std::cout << "X: " << centerX << "Y: " << centerY << std::endl;

	velocity += acceleration * (double)deltaTime;

	centerX += velocity.x;
	centerY += velocity.y;

}