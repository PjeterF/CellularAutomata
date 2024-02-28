#include "CellGrid.hpp"
#include "Elements/Vaccum.hpp"

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
        colorGrid[i] = Vaccum::vaccumColor;
    }
}

void CellGrid::insertCell(int x, int y, Cell* cell)
{
    delete cellGrid[y][x];
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
    if (x < 0 || x >= dimensions || y < 0 || y >= dimensions)
        return nullptr;
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

glm::ivec2 CellGrid::lookForEmptyCell(glm::ivec2 start, int searchDistance, Direction direction)
{
    glm::ivec2 offsetVec  = { 0, 0 };
    switch (direction)
    {
    case CellGrid::Up:
        offsetVec = { 0, 1 };
        break;
    case CellGrid::Down:
        offsetVec = { 0, -1 };
        break;
    case CellGrid::Left:
        offsetVec = { -1, 0 };
        break;
    case CellGrid::Right:
        offsetVec = { -1, 0 };
        break;
    default:
        break;
    }

    glm::ivec2 returnOffset = { 0, 0 };
    for (int i = 0; i < searchDistance; i++)
    {
        Cell* target = getCell(start.x + offsetVec.x, start.y + offsetVec.y);
        if (target == nullptr)
            break;
        if (target->type == CellType::Empty)
            returnOffset = returnOffset + offsetVec;
        else
            break;
    }
    return returnOffset;
}

int CellGrid::coordsToIndex(int x, int y)
{
    return y * dimensions + x;
}
