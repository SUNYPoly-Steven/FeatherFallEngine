#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vColor;

uniform mat4 prMatrix = mat4(1.0);
uniform mat4 vwMatrix = mat4(1.0);
uniform mat4 mlMatrix = mat4(1.0);

void main() {

	vColor = color;
	gl_Position = prMatrix * vwMatrix * mlMatrix * position;

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;
in vec4 vColor;

void main() {

	out_color = vColor;
	//out_color = vec4(vColor.x, 0.0, 0.0, 1.0);

}