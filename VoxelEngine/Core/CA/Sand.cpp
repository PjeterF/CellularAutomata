#include "Sand.hpp"
#include "CellGrid.hpp"
#include "Vaccum.hpp"
#include "ImmovableCell.hpp"
#include "MovableCell.hpp"

Sand::Sand(glm::vec4 color) : Cell(color)
{
	type = MovableSolid;
}

void Sand::update(glm::vec2 position, CellGrid& grid)
{
	Cell* target;

	target = grid.getCell(position.x, position.y - 1);
	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas || target->type == Liquid)
	{
		grid.swapCells(position, { position.x, position.y - 1 });
		return;
	}

	target = grid.getCell(position.x + 1, position.y - 1);
	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas || target->type == Liquid)
	{
		grid.swapCells(position, { position.x + 1, position.y - 1 });
		return;
	}

	target = grid.getCell(position.x - 1, position.y - 1);
	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas || target->type == Liquid)
	{
		grid.swapCells(position, { position.x - 1, position.y - 1 });
		return;
	}
}
