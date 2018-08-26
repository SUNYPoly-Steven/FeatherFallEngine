#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vColor;
out vec4 vPos;
flat out vec2 lightPos;

uniform mat4 prMatrix;
uniform vec4 playerPos;

void main() {

	vColor = color; //pixel color = interpolated vertex color
	lightPos = playerPos.xy; //lightPos = players world space coords
	vPos = position; //pixel position = interpolated vertex position
	gl_Position = prMatrix * vPos; //place vertex in screen space

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec4 vColor;
in vec4 vPos;
flat in vec2 lightPos;

uniform float strength = 1.0f;

void main() {

	float distance = length(vPos.xy - lightPos.xy);
	float intensity = (1.0 / distance) * strength;
	out_color = vColor * intensity;

}