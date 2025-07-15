#pragma once
#include <glad/glad.h>
#include <vector>
#include "CircleObjects.h"
#include "DisplayManager.h"
#include "Camera.h"

class Simulation
{

public:
	Simulation();

	~Simulation();

	void init(DisplayManager* displayManager);

	void handleEvents();

	void update(float deltaTime);

	void render();

	std::vector<CircleObjects> circleObjects;

private:

	const float G = 6.6743 * (pow(10, -11));
	bool paused = false;
	bool tempPaused = false;
	SDL_Event event;
	DisplayManager* displayManager;

	//Camera camera;
};
