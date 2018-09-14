#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

namespace core { namespace graphics {

	class Renderable2D {
	protected:

		glm::vec4 position;
		glm::vec2 size;
		glm::vec4 color;

	public:

		Renderable2D(const glm::vec4& pposition, const glm::vec2& psize, const glm::vec4& pcolor);

		virtual ~Renderable2D();

		inline const glm::vec2& getSize() const { return size; }
		inline const glm::vec4& getPosition() const { return position; }
		inline const glm::vec4& getColor() const { return color; }

	};

} }