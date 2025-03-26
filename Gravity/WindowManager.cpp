#include "WindowManager.h"
#include <SDL.h>
#include <glad/glad.h> 
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

WindowManager::WindowManager() {}

WindowManager::~WindowManager() {}

void WindowManager::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	this->height = height;
	this->width = width;

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		glContext = SDL_GL_CreateContext(window);

		if (!glContext) {
			std::cout << "OpenGL context could not be created!" << std::endl;
			isRunning = false;
			return;
		}

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			std::cerr << "Failed to initialize GLAD!" << std::endl;
			isRunning = false;
			return; // Exit initialization if GLAD fails
		}

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		setupTriangle();


		circleObjects.emplace_back(CircleObjects(this));
		circleObjects.back().init(60, 0.25f, 0, 0, 100);

		circleObjects.emplace_back(CircleObjects(this));
		circleObjects.back().init(60, 0.25f, 1.0f, 1.0f, 100);


	}
	else {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		isRunning = false;
	}

}

void WindowManager::handleEvents() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		isRunning = false;
	}
}

void WindowManager::update() {
	float deltaTime = 0.008f;  // Placeholder for 60 FPS (use proper time calculation)
	gravitySim(deltaTime);
	for (CircleObjects& circle : circleObjects) {
		circle.update(deltaTime);
	}
}

void WindowManager::gravitySim(float deltaTime) {
	for (CircleObjects& circleObjects : circleObjects) {  // Iterates directly over each projectile

		circleObjects.velocity += circleObjects.acceleration * deltaTime;
	}
}

void WindowManager::render() {
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (CircleObjects& circleObjects : circleObjects) {  // Iterates directly over each projectile
		circleObjects.draw();
	}
	//renderCircle(60, 0.25f, 0.0f, 0.0f);

	SDL_GL_SwapWindow(window);
}

void WindowManager::setupCircle(int segments, float r, float centerX, float centerY, GLuint& circleVAO, GLuint& circleVBO, bool initialized) {
	
	if (!initialized) {
		glGenVertexArrays(1, &circleVAO);
		glGenBuffers(1, &circleVBO);
	}

	glBindVertexArray(circleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);

	std::vector<float> vertices;
	vertices.push_back(centerX);
	vertices.push_back(centerY);
	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);

	for (int i = 0; i <= segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = centerX + r * cosf(theta);
		float y = centerY + r * sinf(theta);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
	}

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void WindowManager::renderCircle(int segments, float r, float centerX, float centerY, GLuint circleVAO) {
	glUseProgram(shaderProgram);
	glBindVertexArray(circleVAO);
	int vertexCount = segments + 1 + 1;
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	glBindVertexArray(0);
}

void WindowManager::setupTriangle() {

	float verticies[] = {
		// Pos				// Color
		0.0f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f, // Top
		-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, // Bottom left
		0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, // Bottom right
	};

	// Vertex shader source
	const char* vertexShaderSource = R"(
	#version 460 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec3 vertexColor;
	void main() {
		gl_Position = vec4(aPos, 1.0);
		vertexColor = aColor;
	}
	)";

	// Fragment shader source
	const char* fragmentShaderSource = R"(
	#version 460 core
	in vec3 vertexColor;
	out vec4 FragColor;
	void main() {
		FragColor = vec4(vertexColor, 1.0);
	}
	)";

	// Compile shaders and create shader program
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompileErrors(vertexShader, "VERTEX");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompileErrors(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();	// removed the u int cuz i added it into the .h file. If error revert
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkShaderCompileErrors(shaderProgram, "PROGRAM");

	// Delete shader object after linking 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Setup VAO and VBO defined in the .h file!
	glGenVertexArrays(1, &triangleVAO);
	glGenBuffers(1, &triangleVBO);

	glBindVertexArray(triangleVAO);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // x, y, z ; 6*sizeof becouse I have 6 floats (3 for position and 3 for color)
	glEnableVertexAttribArray(0);
	
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // rgb; starts from position 3
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void WindowManager::renderTriangle() {
	glUseProgram(shaderProgram);
	glBindVertexArray(triangleVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void WindowManager::clean() {
	// Delete OpenGL Buffers
	glDeleteVertexArrays(1, &triangleVAO);
	glDeleteBuffers(1, &triangleVBO);

	glDeleteProgram(shaderProgram);

	// Clean SDL
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void WindowManager::checkShaderCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
		}
	}
}