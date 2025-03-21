//#include <SDL.h>     // Include SDL2
//#include <glad/glad.h>     // Include GLAD (must be before SDL_opengl.h)
//#include <iostream>
//
//int main(int argc, char* argv[]) {
//	// Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//		return -1;
//	}
//
//	// Set OpenGL attributes before creating window
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//	// Create SDL2 window with OpenGL context
//	SDL_Window* window = SDL_CreateWindow("SDL2 + OpenGL Test",
//		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//		800, 600,
//		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
//	if (!window) {
//		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//		return -1;
//	}
//
//	// Create OpenGL context
//	SDL_GLContext glContext = SDL_GL_CreateContext(window);
//	if (!glContext) {
//		std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//		SDL_DestroyWindow(window);
//		SDL_Quit();
//		return -1;
//	}
//
//	// Load OpenGL functions using GLAD
//	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
//		std::cerr << "Failed to initialize GLAD!" << std::endl;
//		SDL_GL_DeleteContext(glContext);
//		SDL_DestroyWindow(window);
//		SDL_Quit();
//		return -1;
//	}
//
//	// Print OpenGL version to confirm everything works
//	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
//
//	// Main loop flag
//	bool running = true;
//	SDL_Event event;
//
//	// Render loop
//	while (running) {
//		while (SDL_PollEvent(&event)) {
//			if (event.type == SDL_QUIT) {
//				running = false;
//			}
//		}
//
//		// Clear the screen (Set background color to dark blue)
//		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Swap buffers to display the updated frame
//		SDL_GL_SwapWindow(window);
//	}
//
//	// Cleanup and exit
//	SDL_GL_DeleteContext(glContext);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//	return 0;
//}
