#version 460
precision highp float;

struct Voxel
{
	vec4 rgba;
};

layout(std430, binding = 0) buffer VoxelGrid
{
    Voxel grid[];
};

out vec4 finalColour;

uniform vec3 camPos;
uniform vec3 gridOrigin;

void main()
{
	finalColour = vec4(gl_FragCoord.y/(200.0f * camPos.z) * 1.0f, grid[0].rgba.y, 0.0f, 1.0f);
}