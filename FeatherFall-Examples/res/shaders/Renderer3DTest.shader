#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 oColor;

uniform mat4 prMatrix;
uniform mat4 vwMatrix;

void main() {

	oColor = color;
	gl_Position = prMatrix * vwMatrix * position;

}

#shader fragment
#version 330 core

in vec4 iColor;
out vec4 out_color;

void main() {

	out_color = iColor;

}