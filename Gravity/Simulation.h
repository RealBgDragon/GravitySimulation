#pragma once
#include <glad/glad.h>
#include <vector>
#include "CircleObjects.h"
class Simulation
{

public:
	Simulation();

	~Simulation();

	void init();

	void update();

	std::vector<CircleObjects> circleObjects;

private:

	const float G = 6.6743 * (pow(10, -11));
	bool paused = false;

};

