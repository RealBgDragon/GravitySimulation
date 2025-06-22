#include "Renderer.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}	

void Renderer::init() {

}

void Renderer::setUpShader() {

	// Vertex shader source
	const char* vertexShaderSource = R"(
    #version 460 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec3 vertexColor;
    void main(){
		gl_Position = vec4(aPos, 1.0);
		vertexColor = aColor;
	}
)";
	const char* fragmentShaderSource = R"(
	#version 460 core
    in vec3 vertexColor;
	out vec4 FragColor;
	void main() {
		FragColor = vec4(vertexColor, 1.0);
	}
	)";

	// Compile shader and create shader program
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // vertex is the position of a point in a 2d or 3d world
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompileErrors(vertexShader, "VERTEX");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // the pixel
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompileErrors(fragmentShader, "FRAGMENT");

	sharedProgram = glCreateProgram();
	glAttachShader(sharedProgram, vertexShader);
	glAttachShader(sharedProgram, fragmentShader);
	glLinkProgram(sharedProgram);
	checkShaderCompileErrors(sharedProgram, "PROGRAM");

	// Delete shader object after linking 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Renderer::setUpCircle(int segments, float r, float centerX, float centerY, GLuint& circleVAO, GLuint& circleVBO, bool initialized) {
	if (!initialized) {
		glGenVertexArrays(1, &circleVAO);
		glGenBuffers(1, &circleVBO);
	}

	glBindVertexArray(circleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);

	// Position
	std::vector<float> vertices;
	vertices.push_back(centerX);
	vertices.push_back(centerY);
	vertices.push_back(0.0f);
	// Color
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(1.0f);

	for (int i = 0; i <= segments; i++) {
		float theta = 2.0f * PI * float(i) / float(segments);
		float x = centerX + r * cosf(theta);
		float y = centerY + r * sinf(theta);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);
		
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
	}

	// Uploads from CPU to GPU
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::renderCircle(int segmesnts, GLuint circleVAO) {
	glUseProgram(sharedProgram);
	glBindVertexArray(circleVAO);
	int vertexCount = segmesnts + 1 + 1;
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	glBindVertexArray(0);
}

void Renderer::clean() {
	glDeleteProgram(sharedProgram);
}

void Renderer::checkShaderCompileErrors(unsigned int shader, std::string type) {
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