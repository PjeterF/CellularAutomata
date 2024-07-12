#pragma once
#include "../Liquid.hpp"

class Acid : public Liquid
{
public:
	Acid(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid) override;

	int acidStrength = 10;
	int charge = 3;
};