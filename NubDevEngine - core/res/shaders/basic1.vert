#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec4 color;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA{
	vec4 color;
}vs_out;

void main(){

	vec4 worldPosition = ml_matrix * vec4(position, 1.0);
	vec4 positionRelativeToCamera = vw_matrix * worldPosition;
	gl_Position = pr_matrix * positionRelativeToCamera;
	
	vs_out.color = color;
}