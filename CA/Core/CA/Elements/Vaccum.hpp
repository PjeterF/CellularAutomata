#pragma once
#include "../Cell.hpp"

class Vaccum : public Cell
{
public:
	Vaccum();
	virtual void update(glm::ivec2 position, CellGrid& grid) override;

	static glm::vec4 vaccumColor;
};
