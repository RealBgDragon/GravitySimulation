#include "main.h"
#include "DisplayManager.h"
#include "Simulation.h"
#include <SDL.h>
#include <glad/glad.h> 

DisplayManager* displayManager = nullptr;
Simulation* simulation = nullptr;

int main(int argc, char* argv[]) {
	displayManager = new DisplayManager();
	simulation = new Simulation();

	displayManager->init("Gravity Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false);
	simulation->init(displayManager);

	int frameCount = 0;
	int lastTime = SDL_GetTicks();
	int maxFps = 0;

	const float dt = 1.0f / 60.0f; // 60 updates per second
	float accumulator = 0.0f;
	Uint32 currentTime = SDL_GetTicks();

	while (displayManager->running()) {

		Uint32 newTime = SDL_GetTicks();
		float frameTime = (newTime - currentTime) / 1000.0f;  // convert ms to seconds
		if (frameTime > 0.25f) { frameTime = 0.25f; }  // clamp to avoid spiral of death
		currentTime = newTime;

		accumulator += frameTime;

		// Handle events once per frame
		simulation->handleEvents();

		// Update simulation in fixed time steps
		while (accumulator >= dt) {
			simulation->update(dt);  // pass fixed deltaTime
			accumulator -= dt;
		}
		
		simulation->render();

		//SDL_Delay(16); // 16 ~60 FPS
		
		frameCount++;
		int currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000) {
			if (maxFps < frameCount) { maxFps = frameCount; }
			std::cout << "FPS: " << frameCount << " MAX: " << maxFps<< std::endl;
			
			lastTime = currentTime;
			frameCount = 0;
		}

	}

	if (displayManager) {
		displayManager->clean();
		delete displayManager;
		displayManager = nullptr;
	}

	return 0;
}