#version 330 core

layout (location = 0) out vec4 color;

in DATA{
	vec4 color;
}fs_in;

void main()
{
	color = vec4(1.0, 0.0f, 1.0, 1.0); //fs_in.color;
}