#pragma once
#include "Renderer2D.h"
#include "Shader.h"
#include <deque>
#include "../buffers/IBO.h"
#include "../buffers/VBO.h"
#include "../buffers/VAO.h"

namespace core { namespace graphics {

	class SimpleRenderer2D : public Renderer2D {
	private:

		glm::mat4* projectionMatrix;
		Shader* shader;
		buffers::IBO* ibo;
		buffers::VBO* vbo;
		buffers::BufferLayout layout;
		buffers::VAO vao;

		std::deque<const Renderable2D*> renderQueue;

	public:

		SimpleRenderer2D(glm::mat4* pprojectionMatrix, Shader* pshader);
		~SimpleRenderer2D();
		
		void begin() override;
		void submit(const Renderable2D* renderable) override;
		void end() override;
		void flush() override;

	private:



	};

} }