#include "ImmovableSolid.hpp"

ImmovableSolid::ImmovableSolid(glm::vec4 color) : Cell(color)
{
	this->type = CellType::ImmovableSolid;
}
