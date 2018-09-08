#include "Renderer3DScene.h"

namespace Application { namespace Scene {

	Renderer3DScene::Renderer3DScene()
		: m_Renderer(new core::graphics::Shader("res/shaders/Renderer3DTest.shader")),
		m_Camera(glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				90.0f,
				0.1f,
				100.0f,
				16.0f,
				9.0f)
	{

		vert = new float[7 * 8];
		float intern_vert[] = {
//            X      Y      Z      R      G      B      A    
			-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // 0
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, // 1
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, // 2
			-1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f, // 3
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // 4
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, // 5
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, // 6
			 1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f  // 7
		};

		for (int i = 0; i < 7 * 8; ++i) {
			vert[i] = intern_vert[i];
		}

		index = new unsigned int[3 * 12];
		unsigned int intern_index[] = {
			0, 1, 2, 
			2, 3, 0,

			4, 0, 2, 
			2, 7, 4,

			1, 5, 6, 
			6, 2, 1,

			5, 4, 7, 
			7, 6, 5,

			3, 2, 6, 
			6, 7, 3,

			4, 5, 1, 
			1, 0, 4
		};

		for (int i = 0; i < 3 * 12; ++i) {
			index[i] = intern_index[i];
		}

		m_Cube = new core::graphics::Renderable3D(vert, index, 7 * 8, 3 * 12);
		m_Renderer.m_Shader->bind();
		m_Renderer.m_Shader->setUniformMat4("prMatrix", m_Camera.getProjectionMatrix());
		m_Renderer.m_Shader->setUniformMat4("vwMatrix", m_Camera.getViewMatrix());

	}

	Renderer3DScene::~Renderer3DScene()
	{
		delete[] index;
		delete[] vert; 
		delete m_Cube;
	}

	void Renderer3DScene::OnUpdate(float deltaTime)
	{
	}

	void Renderer3DScene::OnRender()
	{

		m_Renderer.begin();
		
		m_Renderer.submit(m_Cube);
		
		m_Renderer.end();

		m_Renderer.flush();

	}

	void Renderer3DScene::OnImGuiRender()
	{
	}

} }
