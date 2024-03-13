#include "CellGrid.hpp"
#include "Elements/Vaccum.hpp"
#include "Elements/Water.hpp"
#include "Elements/Sand.hpp"
#include "Elements/Stone.hpp"
#include "Elements/Acid.hpp"
#include "Elements/Metal.hpp"

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

void CellGrid::insertCell(glm::ivec2 pos, Cell* cell)
{
    delete cellGrid[pos.y][pos.x];
    cellGrid[pos.y][pos.x] = cell;
    colorGrid[coordsToIndex(pos.x, pos.y)] = cell->color;
}

void CellGrid::insertSquare(glm::ivec2 pos, Element element, int radius, int dispersion)
{
    if (pos.y + radius >= dimensions - 1)
        radius = dimensions - 1 - pos.y;
    if (pos.x + radius >= dimensions - 1)
        radius = dimensions - pos.x;

    for (int x = 0; x < radius; x++)
    {
        for (int y = 0; y < radius; y++)
        {
            if (rand() % dispersion)
                continue;
            switch (element)
            {
            case Element::Vaccum:
                insertCell(pos.x + x, pos.y + y, new Vaccum());
                break;
            case Element::Water:
                insertCell(pos.x + x, pos.y + y, new Water({ 0.1, 0.4, 0.9, 1 }));
                break;
            case Element::Sand:
                insertCell(pos.x + x, pos.y + y, new Sand({ 1, 0.9, 0.3, 1 }));
                break;
            case Element::Stone:
                insertCell(pos.x + x, pos.y + y, new Stone((float)(rand()%100)/255));
                break;
            case Element::Acid:
                insertCell(pos.x + x, pos.y + y, new Acid({ 0.1, 0.9, 0.4, 1 }));
                break;
            case Element::Metal:
                insertCell(pos.x + x, pos.y + y, new Metal((((float)(rand() % 2) / 100) + 0.5f) * glm::vec4(0.9, 0.9, 0.9, 1)));
                break;
            }
        }
    }
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
