#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 vTexCoord;

void main() {
	vTexCoord = texCoord;
	gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 vTexCoord;
uniform sampler2D uTexture;

void main() {
	vec4 texColor = texture(uTexture, vTexCoord);
	out_color = texColor;
}