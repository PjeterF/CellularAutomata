#pragma once
#include "../Cell.hpp"

class Vaccum : public Cell
{
public:
	Vaccum();
	virtual void update(glm::vec2 position, CellGrid& grid) override;

	static glm::vec4 vaccumColor;
};
