#include "Acid.hpp"
#include "../CellGrid.hpp"
#include "../Elements/Vaccum.hpp"

Acid::Acid(glm::vec4 color) : Liquid(color)
{
	this->acidResistance = 1000;
}

void Acid::update(glm::ivec2 position, CellGrid& grid)
{
	Cell* target = nullptr;
	glm::ivec2 targetPos = position;

	targetPos = validDownwardsPos(position, grid);
	if (targetPos != position)
	{
		grid.swapCells(position, targetPos);
		return;
	}
	else
	{
		targetPos = position;
		targetPos.y--;
		target = grid.getCell(targetPos.x, targetPos.y);
		if (target != nullptr)
		{
			if (target->acidResistance < this->acidStrength)
			{
				grid.insertCell(targetPos, new Vaccum());
				if (this->charge-- > 0)
					grid.insertCell(position, new Vaccum());
				return;
			}
		}
	}

	bool right = rand() % 2;
	targetPos = validHorizontalPos(position, grid, right);
	if (targetPos != position)
	{
		grid.swapCells(position, targetPos);
		return;
	}
	else
	{
		targetPos = position;
		if (right)
			targetPos.x++;
		else
			targetPos.x--;

		target = grid.getCell(targetPos.x, targetPos.y);
		if (target != nullptr)
		{
			if (target->acidResistance < this->acidStrength)
			{
				grid.insertCell(targetPos, new Vaccum());
				if (this->charge-- > 0)
					grid.insertCell(position, new Vaccum());
				return;
			}
		}
	}

}
