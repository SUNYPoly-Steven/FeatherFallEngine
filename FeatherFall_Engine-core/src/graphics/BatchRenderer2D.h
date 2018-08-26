#pragma once

#include "Renderer2D.h"
#include "../buffers/VAO.h"
#include "../buffers/VBO.h"
#include "../buffers/IBO.h"
#include "../buffers/BufferLayout.h"

namespace core { namespace graphics {

	class BatchRenderer2D : public Renderer2D {
	private:

		buffers::VAO vao;
		buffers::BufferLayout layout;

		buffers::VBO* vbo = nullptr;
		buffers::IBO* ibo = nullptr;

		VertexData* renderBuffer = nullptr;
		unsigned int indexCount = 0;

	public:

		BatchRenderer2D();
		~BatchRenderer2D();

		void begin() override;
		void submit(const Renderable2D* renderable) override;
		void end() override;
		void flush() override;

		void line(float x0, float y0, float x1, float y1, unsigned int agbr = 0xFFFFFFFF, float thickness = 0.02f);
		void line(const glm::vec2& start, const glm::vec2& end, unsigned int agbr = 0xFFFFFFFF, float thickness = 0.02f);
		void rect(float x, float y, float width, float height, unsigned int abgr = 0xFFFFFFFF, float thickness = 0.02f);
		void rect(const glm::vec2& pos, const glm::vec2& size, unsigned int abgr = 0xFFFFFFFF, float thickness = 0.02f);
		void fillRect(float x, float y, float width, float height, unsigned int abgr = 0xFFFFFFFF);
		void fillRect(const glm::vec2& pos, const glm::vec2& size, unsigned int abgr = 0xFFFFFFFF);

	private:



	};

} }