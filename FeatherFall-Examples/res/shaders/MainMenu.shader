#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 prMatrix;
out vec2 vTexCoord;
out vec4 vColor;

void main() {
	vTexCoord = texCoord;
	gl_Position = prMatrix * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 vTexCoord;
uniform sampler2D ffTex;
uniform sampler2D iconTex;
uniform float percentage; //range 0.0 - 1.0

void main() {
	vec4 ffColor = texture(ffTex, vTexCoord);
	vec4 iconColor = texture(iconTex, vTexCoord);

	out_color = mix(ffColor, iconColor, percentage);

}