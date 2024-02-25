#include "Water.hpp"
#include "CellGrid.hpp"

Water::Water(glm::vec4 color) : Cell(color)
{
	type = Liquid;
}

void Water::update(glm::vec2 position, CellGrid& grid)
{
	Cell* target;

	target = grid.getCell(position.x, position.y - 1);
	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas)
	{
		grid.swapCells(position, { position.x, position.y - 1 });
		return;
	}

	int direction;
	if (rand() % 2)
		direction = 1;
	else
		direction = -1;

	target = grid.getCell(position.x + direction, position.y);
	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas)
	{
		grid.swapCells(position, { position.x + direction, position.y});
		return;
	}
}
