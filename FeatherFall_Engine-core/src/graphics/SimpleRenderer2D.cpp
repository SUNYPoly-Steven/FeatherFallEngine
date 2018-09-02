#include <GL/glew.h>
#include "SimpleRenderer2D.h"

namespace core { namespace graphics {

	SimpleRenderer2D::SimpleRenderer2D(glm::mat4* pprojectionMatrix, Shader* pshader)
		: projectionMatrix(pprojectionMatrix), shader(pshader)
	{
		layout.push<float>(3); //push position data
		layout.push<float>(4); //push color data

		//create buffer big enough for one sprite with dynamic draw
		vbo = new buffers::VBO(nullptr, layout.getStride(), false);

		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		ibo = new buffers::IBO(indices, 6);

		vao.addBuffer(*vbo, layout);
	}

	SimpleRenderer2D::~SimpleRenderer2D()
	{
		delete projectionMatrix;
		delete shader;
		delete ibo;
		delete vbo;
	}

	void SimpleRenderer2D::begin() { }

	void SimpleRenderer2D::submit(const Renderable2D* renderable)
	{
		renderQueue.push_back(renderable);
	}

	void SimpleRenderer2D::end() { }

	void SimpleRenderer2D::flush()
	{
		VertexData* buffer;
		vbo->bind();

		vao.bind();
		ibo->bind();

		shader->bind();
		shader->setUniformMat4("prMatrix", *projectionMatrix);

		while (!renderQueue.empty()) {
			GLCall(buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

			const Renderable2D* renderable = renderQueue.front();
			const glm::vec3& pos = renderable->getPosition();
			const glm::vec2& size = renderable->getSize();
			const glm::vec4& color = renderable->getColor();

			unsigned int c = (int)(color.w * 255.0f) << 24 |
				(int)(color.z * 255.0f) << 16 |
				(int)(color.y * 255.0f) << 8 |
				(int)(color.x * 255.0f);

			//create vertex data from renderable data and push it into vbo
			//(buffer + 0)->position = pos;
			(buffer + 0)->color = c;

			//(buffer + 1)->position = glm::vec3(pos.x + size.x, pos.y, pos.z);
			(buffer + 1)->color = c;

			//(buffer + 2)->position = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
			(buffer + 2)->color = c;

			//(buffer + 3)->position = glm::vec3(pos.x, pos.y + size.y, pos.z);
			(buffer + 3)->color = c;

			GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));

			//glDrawElements( ... );
			GLCall(glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr));

			renderQueue.pop_front();

		}

	}

} }