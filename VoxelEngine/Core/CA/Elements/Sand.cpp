#include "Sand.hpp"
#include "../CellGrid.hpp"
#include "Vaccum.hpp"
#include "../ImmovableSolid.hpp"
#include "../MovableSolid.hpp"
#include <algorithm>

Sand::Sand(glm::vec4 color) : MovableSolid(color)
{

}

void Sand::update(glm::ivec2 position, CellGrid& grid)
{
	Cell* target = nullptr;
	glm::ivec2 targetPos = position;

	this->downwardsVelocity = std::min(this->downwardsVelocity + velIncrease, maxVel);

	auto tPos = validDownwardsPos(position, grid);

	if (tPos != position)
	{
		grid.swapCells(position, tPos);
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
