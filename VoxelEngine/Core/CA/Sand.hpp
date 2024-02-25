#pragma once
#include "MovableCell.hpp"

class Sand : public MovableCell
{
public:
	Sand(glm::vec4 color);
	virtual void update(glm::vec2 position, CellGrid& grid) override;
};