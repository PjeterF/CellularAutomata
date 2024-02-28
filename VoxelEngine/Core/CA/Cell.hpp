#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class CellGrid;

enum class CellType
{
	NoType = 0,
	Empty,
	ImmovableSolid,
	MovableSolid,
	Gas,
	Liquid
};

class Cell
{
public:
	Cell(glm::vec4 color = { 0, 0, 0, 0 });
	virtual void update(glm::ivec2 position, CellGrid& grid) = 0;
	glm::vec4 color;
	CellType type = CellType::NoType;
};