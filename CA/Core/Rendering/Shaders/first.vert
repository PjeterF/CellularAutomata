#version 460
precision highp float;

layout(location = 0) in vec2 inPos;

void main()
{
	gl_Position = vec4(inPos.x, inPos.y, 0.0f, 1.0f);
}