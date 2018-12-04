#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;

out vec4 vColor;
out vec2 vUV;

uniform mat4 prMatrix;

void main() {
	vColor = color;
	vUV = uv;
	gl_Position = prMatrix * position;
}


#shader fragment
#version 330 core

in vec4 vColor;
in vec2 vUV;

uniform sampler2D tex;
uniform int useTexture = 1;

layout(location = 0) out vec4 out_color;

void main() {

	if (useTexture == 0) {
		out_color = vColor;
	}
	else {
		out_color = texture(tex, vUV);
	}

}
