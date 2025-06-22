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

	Renderer* renderer = new Renderer;
	
	DisplayManager();
	
	~DisplayManager();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	
	bool running() { return isRunning; }
	void setRunning(bool running) { isRunning = running; }

	SDL_Window* window;
private:

	std::vector<CircleObjects> circleObjects;
	
	bool isRunning = true;

	int width;
	int height;

	SDL_GLContext glContext;
	SDL_Event event;
};

