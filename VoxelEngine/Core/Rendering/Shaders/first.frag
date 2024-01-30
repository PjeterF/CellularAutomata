#version 460
precision highp float;

layout(std430, binding = 0) buffer VoxelGrid
{
	vec4 rgba[];
} grid;

out vec4 finalColour;

uniform vec3 camPos;
uniform vec3 gridOrigin;

void main()
{
	ivec3 gridDimensions = ivec3(100, 100, 100);
	int index = int(gl_FragCoord.x) % 100;

	finalColour = grid.rgba[index].rgba;
}