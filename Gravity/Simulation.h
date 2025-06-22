#pragma once
#include <glad/glad.h>
#include <vector>
#include "CircleObjects.h"
#include "DisplayManager.h"

class Simulation
{

public:
	Simulation();

	~Simulation();

	void init(DisplayManager* displayManager);

	void handleEvents();

	void update();

	void render();

	std::vector<CircleObjects> circleObjects;

private:

	float deltaTime = 0.016f; //Old value 0.00016f

	const float G = 6.6743 * (pow(10, -11));
	bool paused = false;
	bool tempPaused = false;
	SDL_Event event;
	DisplayManager* displayManager;

};
