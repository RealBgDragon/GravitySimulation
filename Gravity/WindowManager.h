#pragma once
#include <SDL.h>
#include <glad/glad.h> 
#include <iostream>
#include <vector>
#include "CircleObjects.h"

class CircleObjects;

class WindowManager
{
public:

	WindowManager();

	~WindowManager();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	void setupTriangle();
	void renderTriangle();

	void setupCircle(int segments, float r, float centerX, float centerY, GLuint& circleVAO, GLuint& circleVBO, bool initialized);
	void renderCircle(int segments, float r, float centerX, float centerY, GLuint circleVAO);

	void gravitySim();

	bool running() { return isRunning; }

	void checkShaderCompileErrors(unsigned int shader, std::string type);

private:

	const float G = 6.6743 * (pow(10, -11));

	std::vector<CircleObjects> circleObjects;

	bool isRunning = true;

	int width;
	int height;

	GLuint triangleVAO;
	GLuint triangleVBO;

	GLuint shaderProgram;

	SDL_Window* window;
	SDL_GLContext glContext;
	SDL_Event event;
};

