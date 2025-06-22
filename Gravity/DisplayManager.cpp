#include "DisplayManager.h"

DisplayManager::DisplayManager(){}

DisplayManager::~DisplayManager(){
	delete renderer;
	renderer = nullptr;
}

void DisplayManager::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	this->width = width;
	this->height = height;

	int flags = 0;

	/*if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}*/

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to initialize SDL!" << std::endl;
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!window) {
		std::cerr << "Failed to create window!" << std::endl;
		return;
	}

	glContext = SDL_GL_CreateContext(window);

	if (!glContext) {
		std::cerr << "Failed to create OpenGL context!" << std::endl;
		return;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		return;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	std::cout << "===== Gravity Simulation Controls =====" << std::endl;
	std::cout << " [L]  Spawn new object" << std::endl;
	std::cout << " [P]  Pause simulation" << std::endl;
	std::cout << " [O]  Print object coordinates" << std::endl;
	std::cout << " [F]  Advance one frame (while paused)" << std::endl;
	std::cout << "=======================================" << std::endl;


	renderer->setUpShader();
}

void DisplayManager::clean() {
	
	renderer->clean();

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}