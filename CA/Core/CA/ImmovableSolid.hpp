#pragma once
#include "Cell.hpp"

class ImmovableSolid : public Cell
{
public:
	ImmovableSolid(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid) = 0;
};