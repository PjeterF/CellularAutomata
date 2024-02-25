#pragma once
#include "ImmovableCell.hpp"

class Stone : public ImmovableCell
{
public:
	Stone(float hue);
	virtual void update(glm::vec2 position, CellGrid& grid);
};