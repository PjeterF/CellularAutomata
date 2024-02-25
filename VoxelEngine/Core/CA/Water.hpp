#pragma once
#include "Cell.hpp"

class Water : public Cell
{
public:
	Water(glm::vec4 color);
	virtual void update(glm::vec2 position, CellGrid& grid) override;
};