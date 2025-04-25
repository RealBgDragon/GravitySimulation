#pragma once
#include <SDL.h>
#include <glad/glad.h> 
#include <iostream>
#include <vector>
#include "CircleObjects.h"
#include "Renderer.h"

class DisplayManager
{
public:

	std::unique_ptr<Renderer> renderer;

	//Renderer* renderer;
	
	DisplayManager();
	
	~DisplayManager();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	
	bool running() { return isRunning; }

private:

	std::vector<CircleObjects> circleObjects;
	
	bool isRunning = true;

	int width;
	int height;

	SDL_Window* window;
	SDL_GLContext glContext;
	SDL_Event event;
};

