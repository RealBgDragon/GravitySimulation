#include "Simulation.h"

Simulation::Simulation() {}

Simulation::~Simulation() {}

void Simulation::init(DisplayManager* displayManager) {
	this->displayManager = displayManager;

	double weight = 1e5;

	circleObjects.emplace_back(CircleObjects(displayManager->renderer));
	//						segments, r, cX, cY, mass,   xAcc, yAcc
	circleObjects.back().init(60, 0.05f, 0.0f, 0.0f, weight, 0, 0);

	circleObjects.emplace_back(CircleObjects(displayManager->renderer));
	circleObjects.back().init(60, 0.05f, 0.25f, 0.25f, weight, 0, 0);
	
}

void Simulation::handleEvents() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		displayManager->setRunning(false);
	}
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_l) {
			double weight = 1e5;
			circleObjects.emplace_back(CircleObjects(displayManager->renderer));
			circleObjects.back().init(60, 0.05f, -0.25f, 0.25f, weight, 0, 0);
			std::cout << "Object spawned" << std::endl;
			//displayManager->setRunning(false);
		}
		if (key == SDLK_p) {
			paused = !paused;
			std::cout << "Simulation paused" << std::endl;
		}
		if (key == SDLK_f) {
			paused = !paused;
			std::cout << "Simulation unpaused for a single frame" << std::endl;
		}
		if (key == SDLK_o) {
			for (CircleObjects& circle : circleObjects) {
				std::cout << "X: " << circle.getCenterX() << "Y: " << circle.getCenterY() << std::endl;
				std::cout << "VAO: " << circle.getCircleVAO() << "VBO: " << circle.getCircleVBO() << std::endl;
			}
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		int windowWidth, windowHeight;
		SDL_GetWindowSize(displayManager->window, &windowWidth, &windowHeight);

		float ndcX = (2.0f * mouseX) / windowWidth - 1.0f;
		float ndcY = 1.0f - (2.0f * mouseY) / windowHeight;  // invert Y axis

		double weight = 1e5;

		circleObjects.emplace_back(CircleObjects(displayManager->renderer));
		circleObjects.back().init(60, 0.05f, ndcX, ndcY, weight, 0, 0);
		std::cout << "Object spawned at location: " << ndcX << " " << ndcY << std::endl;
	}
}

void Simulation::update() {
	if (!paused) {
		for (CircleObjects& circle : circleObjects) {
			circle.update(deltaTime, circleObjects);
		}
		if (tempPaused) {
			paused = !paused;
		}
	}
}

void Simulation::render() {
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (CircleObjects& circle : circleObjects) {  // Iterates directly over each projectile
		circle.draw();
	}
	//renderCircle(60, 0.25f, 0.0f, 0.0f);

	SDL_GL_SwapWindow(displayManager->window);
}