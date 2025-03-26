#include "CircleObjects.h"

CircleObjects::CircleObjects(WindowManager* windowManager) {
	this->windowManager = windowManager;
}

CircleObjects::~CircleObjects() {

	glDeleteVertexArrays(1, &circleVAO);
	glDeleteBuffers(1, &circleVBO);

}

void CircleObjects::init(int segments, float r, float centerX, float centerY, double mass) {

	this->segments = segments;
	this->r = r;
	this->centerX = centerX;
	this->centerY = centerY;
	this->mass = mass;

}

void CircleObjects::draw() {
	windowManager->setupCircle(segments, r, centerX, centerY, circleVAO, circleVBO, initialized);
	initialized = true;
	windowManager->renderCircle(segments, r, centerX, centerY, circleVAO);
}

void CircleObjects::update(float deltaTime) {
	std::cout << "X: " << centerX << "Y: " << centerY << std::endl;

	if (centerY < -1) {
		centerY = -1;
		velocity.y = -velocity.y;
	}

	velocity += acceleration * deltaTime;

	centerX += velocity.x;
	centerY += velocity.y;

}