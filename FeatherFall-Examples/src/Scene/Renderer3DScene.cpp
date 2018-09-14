#include "Renderer3DScene.h"

namespace Application { namespace Scene {

	Renderer3DScene::Renderer3DScene()
		: m_Renderer(new core::graphics::Shader("res/shaders/Renderer3DTest.shader")),
		m_Camera(glm::vec3(2.0f, 2.0f, 3.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				90.0f,
				0.1f,
				100.0f,
				16.0f,
				9.0f),
		mlMatrix(1.0f)
	{

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

		unsigned int intern_index[] = {
			0, 1, 2, // Left
			1, 3, 2, //

			4, 0, 2, // Bottom
			2, 6, 4, // 

			1, 5, 7, // Top 
			7, 3, 1, //

			7, 5, 4, // Right 
			4, 6, 7, //

			6, 2, 3, // Back
			3, 7, 6, //

			4, 5, 1, // Front
			1, 0, 4  //
		};

		m_Cube = new core::graphics::Renderable3D(intern_vert, intern_index, 7 * 8 * 4, 3 * 12);
		
		m_Renderer.m_Shader->bind();
		m_Renderer.m_Shader->setUniformMat4("prMatrix", m_Camera.getProjectionMatrix());
		m_Renderer.m_Shader->setUniformMat4("vwMatrix", m_Camera.getViewMatrix());
		
		//set background to Grey
		GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

	}

	Renderer3DScene::~Renderer3DScene()
	{ 
		delete m_Cube;
	}

	void Renderer3DScene::OnUpdate(float deltaTime)
	{
		static float angle = 0.0f;
		mlMatrix = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
		angle += deltaTime;
		m_Renderer.m_Shader->bind();
		m_Renderer.m_Shader->setUniformMat4("mlMatrix", mlMatrix);

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
