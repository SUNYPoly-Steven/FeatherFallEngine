#shader vertex
// - - - - VERTEX SHADER - - - - //
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 color;

out vec4 vPos;
out vec4 vColor;
out int vMaxIter;

uniform mat4 prMatrix;


void main() {
	vPos = pos;
	vColor = color;
	gl_Position = prMatrix * pos;
}

#shader fragment
// - - - - FRAGMENT SHADER - - - - //
#version 330 core

layout(location = 0) out vec4 out_color;

in vec4 vPos;
in vec4 vColor;

uniform int vMaxIter = 1000;
uniform sampler2D palette;
uniform vec2 vC = vec2(0.0, 0.0);
uniform int flag = 0; //default is mandelbrot

vec4 mandelbrot(in vec2 ppos, in float pmax_iters);
vec4 julia(in vec2 ppos, in vec2 c, in float pmax_iters);

void main() {

	if (flag == 0)
		out_color = mandelbrot(vPos.xy, vMaxIter);
	else
		out_color = julia(vPos.xy, vC, vMaxIter);
	
}

vec4 mandelbrot(in vec2 ppos, in float pmax_iters) {
	float iter = 0.0;
	float x = 0.0;
	float y = 0.0;
	float tempX = 0.0;
	while (x*x + y*y < (1 << 16) && iter < pmax_iters) {
		tempX = x*x - y*y + ppos.x;
		y = 2 * x*y + ppos.y;
		x = tempX;

		iter = iter + 1.0;
	}

	if (iter < pmax_iters) {
		float log_zn = log(x*x + y*y) / 2;
		float nu = log( log_zn / log(2) ) / log(2);
		iter = iter + 1.0 - nu;
	}

	vec2 texCoord1 = vec2(iter / pmax_iters, iter / pmax_iters);
	vec2 texCoord2 = vec2((iter + 1) / pmax_iters, (iter + 1) / pmax_iters);

	vec4 color1 = texture2D(palette, texCoord1);
	vec4 color2 = texture2D(palette, texCoord2);


	if (iter == 1.0)
		return vec4(0.0, 0.0, 0.0, 1.0);
	else
		return mix(color1, color2, iter);

}

vec4 julia(in vec2 ppos, in vec2 c, in float pmax_iters) {
	float iter = 0.0;
	float iterinc = 1.0 / pmax_iters;
	float x = ppos.x;
	float y = ppos.y;
	float tempX = 0.0;
	while (x*x + y*y < (1 << 16) && iter < 1.0) {
		tempX = x * x - y * y;
		y = 2 * x*y + c.y;
		x = tempX + c.x;

		iter = iter + iterinc;
	}

	vec2 texCoord = vec2(iter, iter);

	if (iter == 1.0)
		return vec4(0.0, 0.0, 0.0, 1.0);
	else
		return texture2D(palette, texCoord);

}