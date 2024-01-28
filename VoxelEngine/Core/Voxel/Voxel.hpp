#pragma once
#include <glm/vec4.hpp>

struct Voxel
{
	Voxel(glm::vec4 rgba = { 1, 1, 1, 1 });
	glm::vec4 rgba;
};