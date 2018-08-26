#include "BuffersTestScene.h"
#include <ImGui/imgui.h>
#include <GL/glew.h>
#include "debuging.h"

namespace Application { namespace Scene {


	BuffersTestScene::BuffersTestScene() {
		using namespace core;

		vao = new buffers::VAO();

		float vertexData[] = {
			-0.5f, -0.5f, //0
			 0.5f, -0.5f, //1
			 0.5f,  0.5f, //2
			-0.5f,  0.5f  //3
		};
		vbo = new buffers::VBO((const void*)vertexData, 2 * 4 * sizeof(float));

		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		ibo = new buffers::IBO(indices, 6);

		layout = new buffers::BufferLayout();
		layout->push<float>(2);

		vao->addBuffer(*vbo, *layout);

		shader = new graphics::Shader("res/shaders/BuffersTest.shader");

	}

	BuffersTestScene::~BuffersTestScene()
	{

		delete vao;
		delete vbo;
		delete ibo;
		delete layout;
		delete shader;

	}

	void BuffersTestScene::OnUpdate(float deltaTime)
	{
	}

	void BuffersTestScene::OnRender()
	{
		
		shader->bind();
		vao->bind();
		ibo->bind();
		GLCall(glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr));

	}

	void BuffersTestScene::OnImGuiRender()
	{
		ImGui::Text("Buffers Test!");
	}

} }

