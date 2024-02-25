#include "Sand.hpp"
#include "CellGrid.hpp"
#include "Vaccum.hpp"
#include "ImmovableCell.hpp"
#include "MovableCell.hpp"

Sand::Sand(glm::vec4 color) : MovableCell(color)
{
}

void Sand::update(glm::vec2 position, CellGrid& grid)
{
	Cell* target = grid.getCell(position.x, position.y - 1);

	if (target == dynamic_cast<Vaccum*>(target));
	{
		grid.swapCells(position, { position.x, position.y - 1 });
		return;
	}
	if (target == dynamic_cast<ImmovableCell*>(target));
	{
		return;
	}
	if (target == dynamic_cast<MovableCell*>(target));
	{
		return;
	}
}
