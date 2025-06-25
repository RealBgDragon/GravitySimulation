#include "CircleObjects.h"

CircleObjects::CircleObjects(Renderer* renderer) {
	this->renderer = renderer;	
}

CircleObjects::~CircleObjects() {

	//! When I add a new object to the vector all of the items are deleted and moved
	//! so the destructor runs. After the code bellow is executed the VAO and VBO start again
	//! from 1 onwards (causing 2 obj to have the same VAO and VBO
	//TODO Find a way to fix this issue
	
	/*glDeleteVertexArrays(1, &circleVAO);
	glDeleteBuffers(1, &circleVBO);*/

}

void CircleObjects::init(unsigned int id, int segments, float r, float centerX, float centerY, double mass, double xAcceleration, double yAcceleration) {

	this->id = id;
	this->segments = segments;
	this->r = r;
	this->centerX = centerX;
	this->centerY = centerY;
	this->mass = mass;

	velocity = glm::dvec2(xAcceleration, yAcceleration);

	/*renderer->setUpCircle(segments, r, centerX, centerY, circleVAO, circleVBO, initialized);
	initialized = true;*/
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
	int currentTime = SDL_GetTicks();
	if (currentTime - lastColisionTime > delay) {
		lastColisionId = -1;
	}
	if (distance <= r * 2 && !(other.getLastColisionId() == id)) {
		lastColisionId = other.getId();
		lastColisionTime = SDL_GetTicks();
		//std::cout << "Colision with: " << lastColisionId << std::endl;

		// Push objects apart
		float overlap = (r * 2) - distance;

		// Avoid division by zero
		if (distance != 0.0f) {
			glm::vec2 correctionDir = glm::normalize(direction);
			glm::vec2 correction = correctionDir * (overlap / 2.0f);

			// Move each object apart
			centerX -= correction.x;
			centerY -= correction.y;

			other.centerX += correction.x;
			other.centerY += correction.y;
		}

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

	centerX += velocity.x * (double)deltaTime; //? Just added * delta time
	centerY += velocity.y * (double)deltaTime;

}