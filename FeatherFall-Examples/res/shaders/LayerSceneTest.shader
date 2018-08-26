#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vColor;

uniform mat4 prMatrix;

void main() {
	vColor = color;
	gl_Position = prMatrix * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec4 vColor;

void main() {

	out_color = vColor;

}