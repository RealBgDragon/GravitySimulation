#include "Simulation.h"

Simulation::Simulation() {}

Simulation::~Simulation() {}

void Simulation::init(DisplayManager* displayManager) {
	this->displayManager = displayManager;

	double weight = 1e5;

	circleObjects.emplace_back(CircleObjects(displayManager->renderer));
	circleObjects.back().init(60, 0.05f, 0, 0, weight, 0, 0);

	circleObjects.emplace_back(CircleObjects(displayManager->renderer));
	circleObjects.back().init(60, 0.05f, 0.25f, 0.25f, weight, 0, 0);
}

void Simulation::handleEvents() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		displayManager->setRunning(false);
	}
}

void Simulation::update() {
	float deltaTime = 0.00016f;
	if (!paused) {
		for (CircleObjects& circle : circleObjects) {
			circle.update(deltaTime, circleObjects);
		}
	}
}

void Simulation::render() {
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (CircleObjects& circleObjects : circleObjects) {  // Iterates directly over each projectile
		circleObjects.draw();
	}
	//renderCircle(60, 0.25f, 0.0f, 0.0f);

	SDL_GL_SwapWindow(displayManager->window);
}