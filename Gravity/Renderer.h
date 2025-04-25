#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init();

	void setUpShader();

	void setUpCircle(int segments, float r, float centerX, float centerY, GLuint& circleVAO, GLuint& circleVBO, bool initialized);

	void renderCircle(int segments, GLuint circleVAO);

	void clean();

private:

	const float PI = 3.1415926f;

	GLuint sharedProgram;
};

