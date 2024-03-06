#include "Liquid.hpp"
#include "CellGrid.hpp"

Liquid::Liquid(glm::vec4 color) : Cell(color)
{
	this->type = CellType::Liquid;
}

glm::ivec2 Liquid::validDownwardsPos(glm::ivec2 startPos, CellGrid& grid)
{
	Cell* target = nullptr;
	for (int i = 0; i < this->downwardsVelocity; i++)
	{
		startPos.y -= 1;
		target = grid.getCell(startPos.x, startPos.y);
		if (target == nullptr)
			return { startPos.x, startPos.y + 1 };
		if (!(target->type == CellType::Empty || target->type == CellType::Gas))
			return { startPos.x, startPos.y + 1 };
	}
	return startPos;
}

glm::ivec2 Liquid::validHorizontalPos(glm::ivec2 startPos, CellGrid& grid, bool right)
{
	Cell* target = nullptr;
	glm::ivec2 currentPos = startPos;
	int offset = -1;
	if (right)
		offset = 1;

	for (int i = 0; i < dispersionRate; i++)
	{
		currentPos.x += offset;
		target = grid.getCell(currentPos.x, currentPos.y);
		if (target == nullptr)
		{
			return { currentPos.x - offset, currentPos.y };
		}
		if (!(target->type == CellType::Empty || target->type == CellType::Gas))
		{
			return { currentPos.x - offset, currentPos.y };
		}
	}
	return currentPos;
}
