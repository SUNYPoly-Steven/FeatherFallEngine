#include "FeatherFall-gl.h"
#include "Renderer3DScene.h"
#include <ImGui/imgui.h>
#include "math (depricated)/misc_math.h"
#include "FeatherFall-graphics.h"
#include "logging/Logging.h"

#include <iostream>


namespace Application { namespace Scene {

	Renderer3DScene::Renderer3DScene()
		: m_Renderer(new core::graphics::Shader("res/shaders/Renderer3DTest.shader"),
		new core::graphics::Camera(glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			core::math::toRads(100.0f),
			0.1f,
			100.0f,
			16.0f,
			9.0f)),
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

		float floor_verts[] = {
//            X      Y      Z     nX    nY    nZ    R      G      B      A    
			-8.0f, -2.0f, -8.0f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,  1.0f,  1.0f, // 0
			-8.0f, -2.0f,  8.0f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,  1.0f,  1.0f, // 1
			 8.0f, -2.0f,  8.0f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,  1.0f,  1.0f, // 2
			 8.0f, -2.0f, -8.0f, 0.0f, 0.0f, 1.0f, 1.0f,  1.0f,  1.0f,  1.0f  // 3
		};

		unsigned int floor_index[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_Cube = new core::graphics::Renderable3D(intern_vert, intern_index, 7 * 8 * 4, 3 * 12);
		m_Floor = new core::graphics::Renderable3D(floor_verts, floor_index, 4 * 8 * 4, 3 * 6);
		//m_Feather = core::mesh::Mesh::ReadFile("res/models/feather.obj");
		m_DebugIco = core::mesh::Mesh::ReadFile("res/models/debug-ico.fbx");
		m_Renderer.m_Shader->bind();
		m_Renderer.m_Shader->setUniformMat4("projMat", m_Renderer.m_Camera->getProjectionMatrix());
		m_Renderer.m_Shader->setUniformMat4("viewMat", m_Renderer.m_Camera->getViewMatrix());
		

		m_Renderer.m_Shader->setUniformVec3("light.pos", glm::vec3(2.0f, 2.0f, 2.0f));
		m_Renderer.m_Shader->setUniformVec3("light.color", glm::vec3(1.0f, 1.0f, 1.0f));

		m_Renderer.m_Shader->setUniformVec3("material.kd", glm::vec3(1.0f, 0.5f, 1.0f));
		m_Renderer.m_Shader->setUniformVec3("material.ks", glm::vec3(1.0f, 0.5f, 0.5f));
		m_Renderer.m_Shader->setUniform1f("material.shininess", 0.5f);


		//set background to Grey
		GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

	}

	Renderer3DScene::~Renderer3DScene()
	{ 
		delete m_Cube;
		delete m_Floor;

		delete m_Feather;
		delete m_DebugIco;
	}

	void Renderer3DScene::OnUpdate(float deltaTime)
	{
		static float angle = 0.0f;
		mlMatrix = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
		angle += deltaTime * 2.0f;
		m_Cube->m_mlMatrix = mlMatrix;

		//glm::mat4 scale = glm::scale(glm::vec3(0.5f));

		m_DebugIco->m_mlMatrix = mlMatrix;
		//m_Renderer.m_Shader->bind();
		//m_Renderer.m_Shader->setUniformMat4("mlMatrix", mlMatrix);

		if (ImGui::IsKeyPressed('W')) {
			 m_Renderer.m_Camera->forward(0.1f);
		}
		if (ImGui::IsKeyPressed('S')) {
			 m_Renderer.m_Camera->forward(-0.1f);
		}
		if (ImGui::IsKeyPressed('A')) {
			 m_Renderer.m_Camera->strafeRight(-0.1f);
		}
		if (ImGui::IsKeyPressed('D')) {
			 m_Renderer.m_Camera->strafeRight(0.1f);
		}

		if (ImGui::IsKeyPressed('I')) {
			 m_Renderer.m_Camera->rotateUp(0.1f);
		}
		if (ImGui::IsKeyPressed('K')) {
			 m_Renderer.m_Camera->rotateUp(-0.1f);
		}
		if (ImGui::IsKeyPressed('J')) {
			 m_Renderer.m_Camera->rotateRight(0.1f);
		}
		if (ImGui::IsKeyPressed('L')) {
			 m_Renderer.m_Camera->rotateRight(-0.1f);
		}


		m_Renderer.m_Shader->setUniformMat4("projMat", m_Renderer.m_Camera->getProjectionMatrix());
		m_Renderer.m_Shader->setUniformMat4("viewMat", m_Renderer.m_Camera->getViewMatrix());



	}

	void Renderer3DScene::OnRender()
	{

		m_Renderer.begin();
		
		//m_Renderer.submit(m_Cube);
		//m_Renderer.submit(m_Floor);
		//m_Renderer.submit(m_Feather);


		m_Renderer.submit(m_DebugIco);
		
		m_Renderer.end();

		m_Renderer.flush();

	}

	void Renderer3DScene::OnImGuiRender()
	{
	}

} }
