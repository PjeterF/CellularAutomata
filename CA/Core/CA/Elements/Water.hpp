#pragma once
#include "../Liquid.hpp"

class Water : public Liquid
{
public:
	Water(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid) override;
};