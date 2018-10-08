#include "BatchRenderer2D.h"
#include <memory>

namespace core { namespace graphics {

	BatchRenderer2D::BatchRenderer2D()
	{
		//Setup BufferLayout
		layout.push<float>(4); //push position data
		layout.push<unsigned char>(4); //push color data

		//create vertex buffer of size RENDERER_BUFFER_SIZE without data
		vbo = new buffers::VBO(nullptr, RENDERER_BUFFER_SIZE, false);

		//create index buffer of size RENDERER_MAX_INDEX_COUNT
		std::unique_ptr<unsigned int[]> indices = std::make_unique<unsigned int[]>(RENDERER_MAX_INDEX_COUNT);
		/*
		 * Once data is in OpenGL we don't need it CPU side,
		 * it will be deleted using unique_ptr leaving scope
		 * to make sure that a memory leak will not happen
		 * if anything else in this ctor should fail or throw
		 */

		unsigned int offset = 0;
		for (int i = 0; i < RENDERER_MAX_INDEX_COUNT; i += 6) {

			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}
		ibo = new buffers::IBO(indices.get(), RENDERER_MAX_INDEX_COUNT);

		vao.addBuffer(*vbo, layout);

		vao.unbind();

	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete vbo;
		delete ibo;
	}

	void BatchRenderer2D::begin() {
		vbo->bind();
		GLCall(renderBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{
		const glm::vec3& pos = renderable->getPosition();
		const glm::vec4& color = renderable->getColor();
		const glm::vec2& size = renderable->getSize();

		/*
		 * Converting the glm::vec4 into an unsigned int 
		 * makes the copying of colors faster.
		 */
		unsigned int c = (int)(color.a * 255.0f) << 24 | 
						 (int)(color.b * 255.0f) << 16 | 
						 (int)(color.g * 255.0f) <<  8 | 
						 (int)(color.r * 255.0f);

		//#NOTE: doing this glm::vec4 construction is expensive.
		//       try to optimize the excessive copies when 
		//       multiplying with m_StackTop 
		//       This is a Critical optimization to make.
		renderBuffer->position = /*(*m_StackTop) */ glm::vec4(pos, 1.0f);
		renderBuffer->color = c;
		renderBuffer++;

		renderBuffer->position = /*(*m_StackTop) */ glm::vec4(pos.x + size.x, pos.y, 0.0f, 1.0f);
		renderBuffer->color = c;
		renderBuffer++;

		renderBuffer->position = /*(*m_StackTop) */ glm::vec4(pos.x + size.x, pos.y + size.y, 0.0f, 1.0f);
		renderBuffer->color = c;
		renderBuffer++;

		renderBuffer->position = /*(*m_StackTop) */ glm::vec4(pos.x, pos.y + size.y, 0.0f, 1.0f);
		renderBuffer->color = c;
		renderBuffer++;

		indexCount += 6;
	}
	
	void BatchRenderer2D::end() 
	{
		//vbo->bind();
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		vbo->unbind();
	}

	void BatchRenderer2D::flush() 
	{
		vao.bind();
		ibo->bind();

		GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));

		vao.unbind();
		ibo->unbind();

		indexCount = 0;
	}

	void BatchRenderer2D::line(float x0, float y0, float x1, float y1, unsigned int agbr, float thickness) 
	{ 
		using namespace glm;

		vec2 normal = normalize(vec2(y1 - y0, -(x1 - x0))) * thickness;

		renderBuffer->position = (*m_StackTop) * vec4(x0 + normal.x, y0 + normal.y, 0.0f, 1.0f);
		renderBuffer->color = agbr;
		renderBuffer++;

		renderBuffer->position = (*m_StackTop) * vec4(x1 + normal.x, y1 + normal.y, 0.0f, 1.0f);
		renderBuffer->color = agbr;
		renderBuffer++;

		renderBuffer->position = (*m_StackTop) * vec4(x1 - normal.x, y1 - normal.y, 0.0f, 1.0f);
		renderBuffer->color = agbr;
		renderBuffer++;

		renderBuffer->position = (*m_StackTop) * vec4(x0 - normal.x, y0 - normal.y, 0.0f, 1.0f);
		renderBuffer->color = agbr;
		renderBuffer++;

		indexCount += 6;
	}

	void BatchRenderer2D::line(const glm::vec2& start, const glm::vec2& end, unsigned int agbr, float thickness) 
	{
		line(start.x, start.y, end.x, end.y, agbr, thickness);
	}

	void BatchRenderer2D::rect(float x, float y, float width, float height, unsigned int abgr, float thickness) 
	{
		line(x, y, x + width, y, abgr, thickness);
		line(x + width, y, x + width, y + height, abgr, thickness);
		line(x + width, y + height, x, y + height, abgr, thickness);
		line(x, y + height, x, y, abgr, thickness);
	}

	void BatchRenderer2D::rect(const glm::vec2& pos, const glm::vec2& size, unsigned int abgr, float thickness) 
	{
		rect(pos.x, pos.y, size.x, size.y, abgr, thickness);
	}

	void BatchRenderer2D::fillRect(float x, float y, float width, float height, unsigned int abgr) 
	{
		
		renderBuffer->position = (*m_StackTop) * glm::vec4(x, y, 0.0f, 1.0f);
		renderBuffer->color = abgr;
		renderBuffer++;

		renderBuffer->position = (*m_StackTop) * glm::vec4(x + width, y, 0.0f, 1.0f);
		renderBuffer->color = abgr;
		renderBuffer++;

		renderBuffer->position = (*m_StackTop) * glm::vec4(x + width, y + height, 0.0f, 1.0f);
		renderBuffer->color = abgr;
		renderBuffer++;

		renderBuffer->position = (*m_StackTop) * glm::vec4(x, y + height, 0.0f, 1.0f);
		renderBuffer->color = abgr;
		renderBuffer++;

		indexCount += 6;

	}

	void BatchRenderer2D::fillRect(const glm::vec2& pos, const glm::vec2& size, unsigned int abgr) 
	{
		fillRect(pos.x, pos.y, size.x, size.y, abgr);
	}



} }