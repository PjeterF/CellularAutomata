#pragma once
#include "Cell.hpp"

class MovableCell : public Cell
{
public:
	MovableCell(glm::vec4 color) : Cell(color) {}
	virtual void update(glm::vec2 position, CellGrid& grid) = 0;
};