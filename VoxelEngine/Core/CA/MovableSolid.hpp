#pragma once
#include "Cell.hpp"

class MovableSolid : public Cell
{
public:
	MovableSolid(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid) = 0;

	float downwardsVelocity = 3.0f;

	const static float velIncrease;
	const static float maxVel;
	const static float frictionScale;
	const static float horizontalScale;
protected:
	glm::ivec2 validDownwardsPos(glm::ivec2 startPos, CellGrid& grid);
	glm::ivec2 validHorizontalPos(glm::ivec2 startPos, CellGrid& grid, bool right);
};