#shader vertex
#version 430 core

layout(location = 0) in vec2 pos;
out vec2 texCoord;

void main() {
	texCoord = pos * 0.5f + 0.5f;
	gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
}

#shader fragment
#version 430 core

uniform sampler2D srcTex;
in vec2 texCoord;
out vec4 color;

void main() {
	float r = texture(srcTex, texCoord).x;
	float g = texture(srcTex, texCoord).y;
	float b = texture(srcTex, texCoord).z;
	float a = texture(srcTex, texCoord).w;
	color = vec4(r, g, b, a);
}