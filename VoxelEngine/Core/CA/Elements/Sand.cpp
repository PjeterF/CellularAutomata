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

	targetPos = validDownwardsPos(position, grid);
	if (targetPos != position)
	{
		grid.swapCells(position, targetPos);
		this->downwardsVelocity = std::min(this->downwardsVelocity + velIncrease, maxVel);
		return;
	}

	targetPos = validHorizontalPos(position, grid, rand()%2);
	if (targetPos != position)
	{
		grid.swapCells(position, targetPos);
		this->downwardsVelocity = this->downwardsVelocity * this->frictionScale;
		return;
	}
}
