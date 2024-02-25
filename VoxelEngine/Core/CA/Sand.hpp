#pragma once
#include "MovableCell.hpp"

class Sand : public Cell
{
public:
	Sand(glm::vec4 color);
	virtual void update(glm::vec2 position, CellGrid& grid) override;

	int velocity = 0;
};