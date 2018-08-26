#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_color;

//out vec3 pos;
//out vec4 color;
//out vec3 light_pos;

uniform vec2 win_size;
uniform vec2 mousePos;
uniform vec4 col;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 rotMat;


void main() {

	//light_pos = vec3(((mousePos.x - (win_size.x * 0.5)) / (win_size.x * 0.5)) * 2, -((mousePos.y - (win_size.y * 0.5)) / (win_size.y * 0.5)), -1.0);
	//pos = vec3(position);
	//color = in_color;
	gl_Position = projMat * viewMat * position;

};

#shader fragment
#version 330 core

layout (location = 0) out vec4 out_color;

//in vec3 pos;
//in vec4 color;
//in vec3 light_pos;

void main() {

	//float intensity = 1.0 / length(pos - light_pos) * 0.25;
	//out_color = color * intensity;
	out_color = vec4(1.0, 1.0, 1.0, 1.0);

};

#shader geometry
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 60) out;

void main() {


	/*Notes:
		width  = 0.150 (per key)
		height = 0.600 (per key)
		space  = 0.001 (between keys)
		total  = 0.151 (from one vert to the next)

		      Original Points
		    X        Y       Z
		-0.075f, -0.300f, -1.000f,
		 0.075f, -0.300f, -1.000f,
		 0.075f,  0.300f, -1.000f,
		-0.075f,  0.300f, -1.000f,

	*/
	
	//left hand//

	gl_Position = gl_in[0].gl_Position + vec4(-0.904, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(-0.904, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(-0.904, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(-0.753, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(-0.753, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(-0.753, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(-0.602, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(-0.602, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(-0.602, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(-0.451, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(-0.451, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(-0.451, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(-0.3, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(-0.3, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(-0.3, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	//wrist bar
	gl_Position = vec4( -0.828, -0.1, -1.0,  1.0);
	EmitVertex();

	gl_Position = vec4( -0.376, -0.1, -1.0,  1.0);
	EmitVertex();

	gl_Position = vec4( -0.376,  0.0, -1.0,  1.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = vec4( -0.828, -0.1, -1.0,  1.0);
	EmitVertex();

	gl_Position = vec4( -0.376,  0.0, -1.0,  1.0);
	EmitVertex();

	gl_Position = vec4( -0.828,  0.0, -1.0,  1.0);
	EmitVertex();

	EndPrimitive();



	//right hand//

	gl_Position = gl_in[0].gl_Position + vec4(0.3, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(0.3, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(0.3, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(0.451, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(0.451, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(0.451, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(0.602, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(0.602, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(0.602, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(0.753, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(0.753, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(0.753, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(0.904, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(0.904, 0.5, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(0.904, 0.5, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	//two extra on right hand//
	gl_Position = gl_in[0].gl_Position + vec4(0.149, 0.3, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(0.149, 0.3, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(0.149, 0.3, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = gl_in[0].gl_Position + vec4(-0.002, 0.3, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(-0.002, 0.3, 0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(-0.002, 0.3, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	//three center horizontal bars
	gl_Position = vec4(-0.2, -0.35, -1.0, 1.0);
	EmitVertex();

	gl_Position = vec4( 0.2, -0.35, -1.0, 1.0);
	EmitVertex();

	gl_Position = vec4( 0.2, -0.20, -1.0, 1.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = vec4(-0.2, -0.35, -1.0, 1.0);
	EmitVertex();

	gl_Position = vec4(0.2, -0.20, -1.0, 1.0);
	EmitVertex();

	gl_Position = vec4(-0.2, -0.20, -1.0, 1.0);
	EmitVertex();

	EndPrimitive();
	

	gl_Position = vec4(-0.2, -0.35, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(0.2, -0.35, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(0.2, -0.20, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = vec4(-0.2, -0.35, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(0.2, -0.20, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(-0.2, -0.20, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


	gl_Position = vec4(-0.2, -0.35, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(0.2, -0.35, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(0.2, -0.20, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = vec4(-0.2, -0.35, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(0.2, -0.20, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(-0.2, -0.20, -1.0, 1.0) + vec4(0.0, -0.20, 0.0, 0.0) + vec4(0.0, -0.20, 0.0, 0.0);
	EmitVertex();

	EndPrimitive();


}