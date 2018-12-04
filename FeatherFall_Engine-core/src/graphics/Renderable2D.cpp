#include "Renderable2D.h"

namespace core { namespace graphics {

	Renderable2D::Renderable2D(const glm::vec3& pposition, const glm::vec2& psize, const glm::vec4& pcolor)
		: position(pposition), size(psize), color(pcolor),
		rotationMat(glm::mat4(1.0f))
	{
		setUVDefaults();
	}

	Renderable2D::~Renderable2D() { }

	void Renderable2D::Rotate(float radians, const glm::vec3& axis)
	{
		rotationMat = glm::rotate(rotationMat, radians, axis);
	}

	void Renderable2D::StaticRotate(float radians, const glm::vec3& axis)
	{
		rotationMat = glm::rotate(glm::mat4(1.0f), radians, axis);
	}


	void Renderable2D::setUVDefaults() {
		
		uv[0] = glm::vec2(0.0f, 0.0f);
		uv[1] = glm::vec2(1.0f, 0.0f);
		uv[2] = glm::vec2(1.0f, 1.0f);
		uv[3] = glm::vec2(0.0f, 1.0f);
		
	}

} }