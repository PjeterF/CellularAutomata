#pragma once
#include "../ImmovableSolid.hpp"

class Stone : public ImmovableSolid
{
public:
	Stone(float hue);
	virtual void update(glm::vec2 position, CellGrid& grid);
};