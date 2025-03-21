#pragma once
#include <SDL.h>
#include <glad/glad.h> 

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

	void renderCircle();

	bool running() { return isRunning; }

private:

	bool isRunning = true;

	int width;
	int height;

	SDL_Window* window;
	SDL_GLContext glContext;
	SDL_Event event;
};

