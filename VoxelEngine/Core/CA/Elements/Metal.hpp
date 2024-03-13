#pragma once
#include "../ImmovableSolid.hpp"

class Metal : public ImmovableSolid
{
public:
	Metal(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid);
};