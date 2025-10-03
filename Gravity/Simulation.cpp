#include "Simulation.h"

Simulation::Simulation() {}

Simulation::~Simulation() {}

void Simulation::init(DisplayManager* displayManager) {
	this->displayManager = displayManager;

	//Camera camera(glm::vec3(0.0f, 0.0f, 10.0f)); // Start a bit away from origin

	//double weight = 7.34e7; // moon
	double weight = 5.972e10; // earth

	circleObjects.emplace_back(CircleObjects(displayManager->renderer));
	//						id, segments, r, cX, cY, mass,   xAcc, yAcc
	circleObjects.back().init(0, 60, 0.05f, 0.0f, 0.0f, weight, 0, 0);

	/*circleObjects.emplace_back(CircleObjects(displayManager->renderer));
	circleObjects.back().init(1, 60, 0.05f, 0.25f, 0.25f, weight, 0, 0);*/
	
}

void Simulation::handleEvents() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		displayManager->setRunning(false);
	}
	if (event.type == SDL_KEYDOWN) {
		const float cameraSpeed = 0.1f;
		/*switch (event.key.keysym.sym) {
		case SDLK_w:
			camera.move(glm::vec3(0.0f, 0.0f, -cameraSpeed)); break;
		case SDLK_s:
			camera.move(glm::vec3(0.0f, 0.0f, cameraSpeed)); break;
		case SDLK_a:
			camera.move(glm::vec3(-cameraSpeed, 0.0f, 0.0f)); break;
		case SDLK_d:
			camera.move(glm::vec3(cameraSpeed, 0.0f, 0.0f)); break;
		case SDLK_q:
			camera.move(glm::vec3(0.0f, cameraSpeed, 0.0f)); break;
		case SDLK_e:
			camera.move(glm::vec3(0.0f, -cameraSpeed, 0.0f)); break;
		}*/
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_l) {
			int lastId = circleObjects.back().getId();
			double weight = 7.34e-7; // 1e5
			circleObjects.emplace_back(CircleObjects(displayManager->renderer));
			double orbitSpeed = sqrt((G * (5.972e10 + weight)) / sqrt(pow(0, 2) + pow(0.5, 2)));
			std::cout << "Speed" << orbitSpeed << std::endl;
			circleObjects.back().init(lastId, 60, 0.05f, 0.0f, 0.5f, weight, orbitSpeed, 0);
			std::cout << "Object spawned" << std::endl;
			//displayManager->setRunning(false);
		}
		if (key == SDLK_p) {
			paused = !paused;
			std::cout << "Simulation paused" << std::endl;
		}
		if (key == SDLK_f) {
			paused = !paused;
			tempPaused = true;
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

		int lastId = circleObjects.back().getId();

		circleObjects.emplace_back(CircleObjects(displayManager->renderer));
		circleObjects.back().init(lastId, 60, 0.05f, ndcX, ndcY, weight, 0, 0);
		std::cout << "Object spawned at location: " << ndcX << " " << ndcY << std::endl;
		std::cout << "Object cound: " << circleObjects.size() << std::endl;
	}
}

void Simulation::update(float deltaTime) {
	if (!paused) {
		for (CircleObjects& circle : circleObjects) {
			circle.update(deltaTime, circleObjects);
		}
		if (tempPaused) {
			paused = !paused;
			tempPaused = false;
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