#include "SimpleRenderer3D.h"

namespace core { namespace graphics {

	SimpleRenderer3D::SimpleRenderer3D(Shader* pshader)
		: m_Shader(pshader) 
	{
		//buffers::BufferLayout layout = buffers::BufferLayout();
		
		//m_VAO.bind();
		//layout.push<float>(3); //add vertex position
		//layout.push<float>(4); //add vertex color

		//m_VAO.addBuffer(/*what VBO do I use for this?*/, layout);

	}

	SimpleRenderer3D::~SimpleRenderer3D() 
	{
		delete m_Shader;
	}

	void SimpleRenderer3D::begin()
	{

	}

	void SimpleRenderer3D::submit(const Renderable3D* renderable)
	{
		m_RenderQueue.push_back(renderable);
	}

	void SimpleRenderer3D::end()
	{

	}

	void SimpleRenderer3D::flush()
	{

		m_Shader->bind();
		while (!m_RenderQueue.empty()) {
			auto& renderable = m_RenderQueue.front();
			renderable->vao.bind();
			renderable->vbo.bind();
			renderable->ibo.bind();
			m_Shader->setUniformMat4("mlMatrix", renderable->m_mlMatrix);

			GLCall(glDrawElements(GL_TRIANGLES, renderable->ibo.getCount(), GL_UNSIGNED_INT, nullptr));
			
			m_RenderQueue.pop_front();
		}

	}

} }