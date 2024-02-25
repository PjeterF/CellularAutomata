#include "CellGrid.hpp"
#include "Vaccum.hpp"

CellGrid::CellGrid(int dimensions)
{
    this->dimensions = dimensions;

    cellGrid.resize(dimensions);
    for (int y = 0; y < dimensions; y++)
    {
        cellGrid[y].resize(dimensions);
        for (int x = 0; x < dimensions; x++)
        {
            cellGrid[y][x] = new Vaccum();
        }
    }
    colorGrid.resize(dimensions * dimensions);
    for (int i = 0; i < dimensions * dimensions; i++)
    {
        colorGrid[i] = { 1, 1, 1, 1 };
    }
}

void CellGrid::insertCell(int x, int y, Cell* cell)
{
    cellGrid[y][x] = cell;
    colorGrid[coordsToIndex(x, y)]=cell->color;
}

void CellGrid::updateAll()
{
    for (int y = 0; y < dimensions; y++)
    {
        for (int x = 0; x < dimensions; x++)
        {
            if (cellGrid[y][x] != nullptr)
                cellGrid[y][x]->update({ x, y }, *this);
        }
    }
}

Cell* CellGrid::getCell(int x, int y)
{
    return cellGrid[y][x];
}

void CellGrid::swapCells(glm::vec2 pos1, glm::vec2 pos2)
{
    colorGrid[coordsToIndex(pos1.x, pos1.y)] = cellGrid[pos2.y][pos2.x]->color;
    colorGrid[coordsToIndex(pos2.x, pos2.y)] = cellGrid[pos1.y][pos1.x]->color;

    Cell* temp = getCell(pos1.x, pos1.y);
    cellGrid[pos1.y][pos1.x] = cellGrid[pos2.y][pos2.x];
    cellGrid[pos2.y][pos2.x] = temp;
}

glm::vec4* CellGrid::getColorGrid()
{
    return &colorGrid[0];
}

int CellGrid::coordsToIndex(int x, int y)
{
    return y * dimensions + x;
}
