#pragma once
#include "Cell.hpp"

class ImmovableSolid : public Cell
{
public:
	ImmovableSolid(glm::vec4 color);
	virtual void update(glm::vec2 position, CellGrid& grid) = 0;
};