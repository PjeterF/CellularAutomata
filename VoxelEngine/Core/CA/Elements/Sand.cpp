#include "Sand.hpp"
#include "../CellGrid.hpp"
#include "Vaccum.hpp"
#include "../ImmovableSolid.hpp"
#include "../MovableSolid.hpp"

Sand::Sand(glm::vec4 color) : MovableSolid(color)
{

}

void Sand::update(glm::vec2 position, CellGrid& grid)
{
	Cell* target;

	for (int i = 0; i < this->downwardsVelocity; i++)
	{
		target = grid.getCell(position.x, position.y - 1 - i);
	}

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
