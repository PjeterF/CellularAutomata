#include "Liquid.hpp"

Liquid::Liquid(glm::vec4 color) : Cell(color)
{
	this->type = CellType::Liquid;
}
