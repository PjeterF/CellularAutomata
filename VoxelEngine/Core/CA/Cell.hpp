#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class CellGrid;

class Cell
{
public:
	Cell(glm::vec4 color = { 0, 0, 0, 0 });
	virtual void update(glm::vec2 position, CellGrid& grid) = 0;
	glm::vec4 color;
};