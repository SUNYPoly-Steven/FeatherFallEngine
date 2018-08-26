#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

struct PointLight {
	vec3 pos;
	vec3 color;
};

uniform PointLight light;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 normalMat;
uniform mat4 projMat;

out vec3 view_Half;
out vec3 view_Normal;

out vec3 view_LightDir;

void main() {

	view_Normal = vec3(normalMat * vec4(normal, 0.0));

	vec3 vertPos = vec3(viewMat * modelMat * vec4(position, 1.0));
	vec3 lightpos = vec3(viewMat * vec4(light.pos, 1.0));

	view_LightDir = normalize(lightpos - vertPos);

	vec3 viewDir = normalize(-vertPos);

	view_Half = normalize(view_LightDir + viewDir);

	gl_Position = projMat * vec4(vertPos, 1.0);

}

//------------------------------------------------------------

#shader fragment
#version 330 core

in vec3 view_Half;
in vec3 view_Normal;
in vec3 view_LightDir;

struct PointLight {
	vec3 pos;
	vec3 color;
};

struct Material {
	float shininess;
	vec3 kd;
	vec3 ks;
};

uniform Material material;
uniform PointLight light;

layout(location = 0) out vec4 out_color;

void main() {

	vec3 H = normalize(view_Half);
	vec3 N = normalize(view_Normal);
	vec3 L = normalize(view_LightDir);

	float diffuse = max(0, dot(N, L));
	float specular = pow(max(0, dot(H, N)), material.shininess);

	vec3 color = light.color * diffuse * (material.kd + material.ks * specular);

	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));

	out_color = vec4(color, 1);
	//out_color = vec4(N, 1);

}