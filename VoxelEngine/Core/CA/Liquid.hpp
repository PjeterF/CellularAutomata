#pragma once
#include "Cell.hpp"

class Liquid : public Cell
{
public:
	Liquid(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid) = 0;

	float downwardsVelocity = 2.0f;
	float dispersionRate = 3.0f;
protected:
	glm::ivec2 validDownwardsPos(glm::ivec2 startPos, CellGrid& grid);
	glm::ivec2 validHorizontalPos(glm::ivec2 startPos, CellGrid& grid, bool right);
};