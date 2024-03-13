#include "Metal.hpp"

Metal::Metal(glm::vec4 color) : ImmovableSolid(color)
{
	this->acidResistance = 100.0f;
}

void Metal::update(glm::ivec2 position, CellGrid& grid)
{
}
