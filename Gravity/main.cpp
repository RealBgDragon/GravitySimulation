#include "main.h"
#include "WindowManager.h"
#include <SDL.h>
#include <glad/glad.h> 

WindowManager* windowManager = nullptr;

int main(int argc, char* argv[]) {
	windowManager = new WindowManager();

	windowManager->init("Gravity Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

	while (windowManager->running()) {

		windowManager->handleEvents();
		windowManager->update();
		windowManager->render();
	}

	if (windowManager) {
		windowManager->clean();
		delete windowManager;
		windowManager = nullptr;
	}

	return 0;
}