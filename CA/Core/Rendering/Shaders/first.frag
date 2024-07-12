#version 460
precision highp float;

layout(std140, binding = 0) buffer ColorGrid
{
	ivec2 gridDimensions;
	vec4 pixelColors[];
} grid;

out vec4 finalColour;

uniform int cellSize;
uniform vec2 viewPortSize;

void main()
{
	ivec2 convCoord;
	convCoord.x = int(gl_FragCoord.x)/cellSize;
	convCoord.y = int(gl_FragCoord.y)/cellSize;

	if(convCoord.x >= grid.gridDimensions.x || convCoord.y >= grid.gridDimensions.y)
		discard;

	int index = convCoord.y*grid.gridDimensions.x + convCoord.x;

	finalColour = grid.pixelColors[index].rgba;
}