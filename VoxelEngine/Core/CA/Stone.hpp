#pragma once
#include "ImmovableCell.hpp"

class Stone : public Cell
{
public:
	Stone(float hue);
	virtual void update(glm::vec2 position, CellGrid& grid);
};