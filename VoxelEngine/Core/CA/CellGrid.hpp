#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include "Cell.hpp"

class CellGrid
{
public:
	CellGrid(int dimensions);
	void insertCell(int x, int y, Cell* cell);
	void updateAll();
	Cell* getCell(int x, int y);
	void swapCells(glm::vec2 pos1, glm::vec2 pos2);
	glm::vec4* getColorGrid();
	std::vector<std::vector<Cell*>> cellGrid;
private:
	int coordsToIndex(int x, int y);

	float dimensions;

	std::vector<glm::vec4> colorGrid;
	friend class Cell;
};