#pragma once
#include "Renderer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <SDL.h>

class Renderer;

class CircleObjects
{

public:
	CircleObjects(Renderer* renderer);
	~CircleObjects();

	void init(unsigned int id, int segments, float r, float centerX, float centerY, double mass, double xAcceleration, double yAcceleration);

	float getCenterX() { return centerX; }
	float getCenterY() { return centerY; }

	void setCenterX(float newCenterX) { centerX = newCenterX; }
	void setCenterY(float newCenterY) { centerY = newCenterY; }

	unsigned int getId() { return id; }

	int getLastColisionId() { return lastColisionId; }

	double getMass() { return mass; }

	void draw();

	void update(float deltaTime, std::vector<CircleObjects>& allObjects);

	void applyGravity(CircleObjects& other);

	GLuint getCircleVAO() { return circleVAO; }
	GLuint getCircleVBO() { return circleVBO; }

private:

	const double G = 6.6743 * (pow(10, -11));

	double xAcceleration;
	double yAcceleration;

	glm::dvec2 velocity = glm::dvec2(0.0f, 0.0f);
	glm::dvec2 acceleration = glm::dvec2(0.0f, 0.0f); // y = -9.81f for gravity

	unsigned int id;
	int segments;
	float r;
	double centerX;
	double centerY;
	double mass;

	bool initialized = false;

	int lastColisionId = -1;
	int lastColisionTime = 0;
	int delay = 500;

	GLuint circleVAO;
	GLuint circleVBO;

	Renderer* renderer;

};

