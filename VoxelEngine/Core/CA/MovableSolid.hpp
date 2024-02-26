#pragma once
#include "Cell.hpp"

class MovableSolid : public Cell
{
public:
	MovableSolid(glm::vec4 color);
	virtual void update(glm::vec2 position, CellGrid& grid) = 0;

	float downwardsVelocity = 0;
};