#include "MovableSolid.hpp"
#include "CellGrid.hpp"

const float MovableSolid::velIncrease = 0.5f;
const float MovableSolid::maxVel = 3.0f;
const float MovableSolid::frictionScale = 0.5f;
const float MovableSolid::horizontalScale = 0.5f;

MovableSolid::MovableSolid(glm::vec4 color) : Cell(color)
{
	this->type = CellType::MovableSolid;
}

glm::ivec2 MovableSolid::validDownwardsPos(glm::ivec2 startPos, CellGrid& grid)
{
	Cell* target = nullptr;
	for (int i = 0; i < this->downwardsVelocity; i++)
	{
		startPos.y -= 1;
		target = grid.getCell(startPos.x, startPos.y);
		if (target == nullptr)
			return { startPos.x, startPos.y + 1 };
		if (!(target->type == Empty || target->type == Gas || target->type == Liquid))
			return { startPos.x, startPos.y + 1 };
	}
	return startPos;
}

glm::ivec2 MovableSolid::validHorizontalPos(glm::ivec2 startPos, CellGrid& grid, bool right)
{
	Cell* target = nullptr;
	int offset = -1;
	if (right)
		offset = 1;

	startPos.y -= 1;
	for (int i = 0; i < downwardsVelocity * horizontalScale; i++)
	{
		startPos.x += offset;
		target = grid.getCell(startPos.x, startPos.y);
		if (target == nullptr)
			return { startPos.x - offset, startPos.y };
		if (!(target->type == Empty || target->type == Gas || target->type == Liquid))
			return { startPos.x - offset, startPos.y };
	}
	return startPos;
}
