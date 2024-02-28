#include "Vaccum.hpp"

glm::vec4 Vaccum::vaccumColor = { 0.94, 1, 1, 1 };

Vaccum::Vaccum()
{
	type = Empty;
	this->color = vaccumColor;
}

void Vaccum::update(glm::ivec2 position, CellGrid& grid)
{
}
