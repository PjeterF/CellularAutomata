#pragma once
#include "Cell.hpp"

class Liquid : public Cell
{
public:
	Liquid(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid) = 0;
};