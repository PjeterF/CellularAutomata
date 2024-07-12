#pragma once
#include "Cell.hpp"

class Gas : public Cell
{
public:
	Gas(glm::vec4 color);
	virtual void update(glm::vec2 position, CellGrid& grid) = 0;
};