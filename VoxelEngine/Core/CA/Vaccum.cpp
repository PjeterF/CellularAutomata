#include "Vaccum.hpp"

glm::vec4 Vaccum::vaccumColor = { 1, 1, 1, 1 };

Vaccum::Vaccum()
{
	this->color = vaccumColor;
}

void Vaccum::update(glm::vec2 position, CellGrid& grid)
{
}
