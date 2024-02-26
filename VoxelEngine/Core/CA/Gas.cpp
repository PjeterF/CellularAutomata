#include "Gas.hpp"

Gas::Gas(glm::vec4 color) : Cell(color)
{
	this->type = CellType::Gas;
}
