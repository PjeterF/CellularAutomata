#include "Sand.hpp"
#include "../CellGrid.hpp"
#include "Vaccum.hpp"
#include "../ImmovableSolid.hpp"
#include "../MovableSolid.hpp"
#include <algorithm>

Sand::Sand(glm::vec4 color) : MovableSolid(color)
{

}

void Sand::update(glm::vec2 position, CellGrid& grid)
{
	Cell* target = nullptr;
	glm::ivec2 targetPos = position;

	for (int i = 0; i < this->downwardsVelocity; i++)
	{
		target = grid.getCell(position.x, position.y - 1 - i);
		targetPos = { position.x, position.y - 1 - i };
		if (target == nullptr)
		{
			target = grid.getCell(position.x, position.y - i);
			targetPos = { position.x, position.y - i };
			break;
		}
		if (!(target->type == Empty || target->type == Gas || target->type == Liquid))
		{
			target = grid.getCell(position.x, position.y - i);
			targetPos = { position.x, position.y - i };
			break;
		}
	}

	this->downwardsVelocity = std::min(this->downwardsVelocity + velIncrease, maxVel);

	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas || target->type == Liquid)
	{
		grid.swapCells(position, targetPos);
		return;
	}

	target = grid.getCell(position.x + 1, position.y - 1);
	targetPos = { position.x + 1 + this->downwardsVelocity/2 , position.y - 1 };
	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas || target->type == Liquid)
	{
		this->downwardsVelocity = frictionScale * this->downwardsVelocity;
		grid.swapCells(position, targetPos);
		return;
	}

	target = grid.getCell(position.x - 1, position.y - 1);
	targetPos = { position.x - 1 - this->downwardsVelocity * horizontalScale , position.y - 1 };
	if (target == nullptr)
		return;
	if (target->type == Empty || target->type == Gas || target->type == Liquid)
	{
		this->downwardsVelocity = frictionScale * this->downwardsVelocity / 10;
		grid.swapCells(position, targetPos);
		return;
	}
}
