#pragma once
#include "../ImmovableSolid.hpp"

class Stone : public ImmovableSolid
{
public:
	Stone(float hue);
	virtual void update(glm::ivec2 position, CellGrid& grid);
};