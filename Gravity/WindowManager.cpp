#include "WindowManager.h"
#include <SDL.h>
#include <glad/glad.h> 
#include <iostream>
#include <glm/glm.hpp>

WindowManager::WindowManager() {}

WindowManager::~WindowManager() {}

void WindowManager::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	this->height = height;
	this->width = width;

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		glContext = SDL_GL_CreateContext(window);

		if (!glContext) {
			std::cout << "OpenGL context could not be created!" << std::endl;
			isRunning = false;
			return;
		}

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			std::cerr << "Failed to initialize GLAD!" << std::endl;
			isRunning = false;
			return; // Exit initialization if GLAD fails
		}

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


	}
	else {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		isRunning = false;
	}


}

void WindowManager::handleEvents() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		isRunning = false;
	}
}

void WindowManager::update() {

}

void WindowManager::render() {
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderCircle();

	SDL_GL_SwapWindow(window);
}

void WindowManager::renderCircle() {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(centerX, centerY);

}

void WindowManager::clean() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}