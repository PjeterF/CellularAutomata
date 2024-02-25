#pragma once
#include "Cell.hpp"

class ImmovableCell : public Cell
{
public:
	ImmovableCell(glm::vec4 color) : Cell(color) {}
	virtual void update(glm::vec2 position, CellGrid& grid) = 0;
};