#pragma once
#include "WindowManager.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class WindowManager;

class CircleObjects
{

public:
	CircleObjects(WindowManager* windowManager);
	~CircleObjects();

	void init(int segments, float r, float centerX, float centerY, double mass);

	int getCenterX() { return centerX; }
	int getCenterY() { return centerY; }

	void setCenterX(float newCenterX) { centerX = newCenterX; }
	void setCenterY(float newCenterY) { centerY = newCenterY; }

	double getMass() { return mass; }

	void draw();

	void update(float deltaTime);

	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	glm::vec2 acceleration = glm::vec2(0.0f, -9.81f);
private:

	int segments;
	float r;
	float centerX;
	float centerY;
	double mass;

	bool initialized = false;

	GLuint circleVAO;
	GLuint circleVBO;

	WindowManager* windowManager;

};

