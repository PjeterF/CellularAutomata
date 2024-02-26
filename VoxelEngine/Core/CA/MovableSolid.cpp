#include "MovableSolid.hpp"

MovableSolid::MovableSolid(glm::vec4 color) : Cell(color)
{
	this->type = CellType::MovableSolid;
}
