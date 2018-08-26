#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vColor;
out vec2 vPos;
flat out vec2 lightPos;

uniform mat4 prMatrix;
uniform vec2 mousePos;

void main() {
	vColor = color;
	lightPos = mousePos;
	vPos = position.xy;
	gl_Position = prMatrix * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec4 vColor;
in vec2 vPos;
flat in vec2 lightPos;

uniform float strength = 40.0f;
uniform int doLight = 1;

void main() {

	float intensity = (1.0 / length(vPos.xy - lightPos.xy)) * strength;


	if (doLight == 1) {
		out_color = vColor * intensity;
	} 
	else {
		out_color = vColor;
	}
}