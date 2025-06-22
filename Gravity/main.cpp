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

	/*int frameCount = 0;
	int lastTime = SDL_GetTicks();
	int maxFps = 0;*/

	while (displayManager->running()) {

		simulation->handleEvents();
		simulation->update();
		simulation->render();

		SDL_Delay(16); // 16 ~60 FPS
		
		/*frameCount++;
		int currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000) {
			if (maxFps < frameCount) { maxFps = frameCount; }
			std::cout << "FPS: " << frameCount << " MAX: " << maxFps<< std::endl;
			
			lastTime = currentTime;
			frameCount = 0;
		}*/

	}

	if (displayManager) {
		displayManager->clean();
		delete displayManager;
		displayManager = nullptr;
	}

	return 0;
}