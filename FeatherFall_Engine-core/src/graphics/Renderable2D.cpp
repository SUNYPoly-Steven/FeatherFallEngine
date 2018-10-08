#include "Renderable2D.h"

namespace core { namespace graphics {

	Renderable2D::Renderable2D(const glm::vec3& pposition, const glm::vec2& psize, const glm::vec4& pcolor)
		: position(pposition), size(psize), color(pcolor)
	{
	}

	Renderable2D::~Renderable2D() { }

} }