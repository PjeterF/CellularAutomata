#include "Stone.hpp"

Stone::Stone(float hue) : Cell({hue, hue, hue, 1.0f})
{
	type = ImmovableSolid;
}

void Stone::update(glm::vec2 position, CellGrid& grid)
{

}
