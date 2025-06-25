#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	Camera(glm::vec3 startPos) : position(startPos), direction(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

	glm::mat4 getViewMatrix() const {
		return glm::lookAt(position, position + direction, up);
	}

	void move(glm::vec3 delta) {
		position += delta;
	}
};

