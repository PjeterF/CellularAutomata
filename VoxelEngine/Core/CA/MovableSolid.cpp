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
		if (!(target->type == CellType::Empty || target->type == CellType::Gas || target->type == CellType::Liquid))
			return { startPos.x, startPos.y + 1 };
	}
	return startPos;
}

glm::ivec2 MovableSolid::validHorizontalPos(glm::ivec2 startPos, CellGrid& grid, bool right)
{
	Cell* target = nullptr;
	glm::ivec2 currentPos = startPos;
	int offset = -1;
	if (right)
		offset = 1;

	currentPos.y -= 1;
	for (int i = 0; i < downwardsVelocity * horizontalScale; i++)
	{
		currentPos.x += offset;
		target = grid.getCell(currentPos.x, currentPos.y);
		if (target == nullptr)
		{
			if (currentPos.x - offset == startPos.x)
				return startPos;
			else
				return { currentPos.x - offset, currentPos.y };
		}
		if (!(target->type == CellType::Empty || target->type == CellType::Gas || target->type == CellType::Liquid))
		{
			if (currentPos.x - offset == startPos.x)
				return startPos;
			else
				return { currentPos.x - offset, currentPos.y };
		}
	}
	return currentPos;
}
