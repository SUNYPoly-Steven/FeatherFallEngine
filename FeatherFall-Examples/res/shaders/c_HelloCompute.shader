#shader compute
#version 430 core

uniform float roll;
layout(rgba32f, binding = 0) uniform image2D destTex;
layout(local_size_x = 16, local_size_y = 16) in;

void main() {

	//retrieve the position of the current "texel"
	//to allow storing the data in the proper position
	ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);

	//some math based on work group location to make a cool texture
	float localCoef = length(vec2(ivec2(gl_LocalInvocationID.xy)-8)/8.0);
	float globalCoef = sin(float(gl_WorkGroupID.x + gl_WorkGroupID.y) * 0.1 + roll) * 0.5;

	//store the data in the output texture
	imageStore(destTex, storePos, vec4(globalCoef * localCoef, 0.0, globalCoef * localCoef, 1.0));

}