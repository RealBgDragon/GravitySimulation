#pragma once
#include <SDL.h>
#include <glad/glad.h> 
#include <iostream>

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

	void setupCircle(int segments, float r);
	void renderCircle(int segments, float r);

	bool running() { return isRunning; }

	void checkShaderCompileErrors(unsigned int shader, std::string type);

private:

	bool isRunning = true;

	int width;
	int height;

	GLuint triangleVAO;
	GLuint triangleVBO;
	
	GLuint circleVAO;
	GLuint circleVBO;
	
	GLuint shaderProgram;

	SDL_Window* window;
	SDL_GLContext glContext;
	SDL_Event event;
};

