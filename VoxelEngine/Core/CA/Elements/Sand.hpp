#pragma once
#include "../MovableSolid.hpp"

class Sand : public MovableSolid
{
public:
	Sand(glm::vec4 color);
	virtual void update(glm::ivec2 position, CellGrid& grid) override;
};