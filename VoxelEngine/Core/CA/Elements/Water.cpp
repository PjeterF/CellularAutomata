#include "Water.hpp"
#include "../CellGrid.hpp"

Water::Water(glm::vec4 color) : Liquid(color)
{
	this->dispersionRate = 2.0f;
}

void Water::update(glm::ivec2 position, CellGrid& grid)
{
	Cell* target = nullptr;
	glm::ivec2 targetPos = position;

	targetPos = validDownwardsPos(position, grid);
	if (targetPos != position)
	{
		grid.swapCells(position, targetPos);
		return;
	}

	targetPos = validHorizontalPos(position, grid, rand() % 2);
	if (targetPos != position)
	{
		grid.swapCells(position, targetPos);
		return;
	}
}
