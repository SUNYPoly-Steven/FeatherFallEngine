#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_color;

uniform mat4 projMat;
uniform mat4 viewMat;

void main() {

	gl_Position = projMat * viewMat * position;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

void main() {

	out_color = vec4(0.95, 0.75, 0.15, 0.5);

};