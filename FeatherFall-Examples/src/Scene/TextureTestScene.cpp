#include "TextureTestScene.h"
#include <ImGui/imgui.h>

namespace Application { namespace Scene {

	TextureTestScene::TextureTestScene() 
	{
		using namespace core;

		vao = new buffers::VAO();

		float vertexData[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, //0
			 0.5f, -0.5f, 1.0f, 0.0f, //1
			 0.5f,  0.5f, 1.0f, 1.0f, //2
			-0.5f,  0.5f, 0.0f, 1.0f  //3
		};
		vbo = new buffers::VBO((const void*)vertexData, 4 * 4 * sizeof(float));

		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		ibo = new buffers::IBO(indices, 6);

		layout = new buffers::BufferLayout();
		layout->push<float>(2); //add position data
		layout->push<float>(2); //add texture coord data

		vao->addBuffer(*vbo, *layout);

		shader = new graphics::Shader("res/shaders/TextureTest.shader");

		texture = new graphics::Texture("res/textures/TextureTest.png");

	}

	TextureTestScene::~TextureTestScene() {
	
		delete vao;
		delete vbo;
		delete ibo;
		delete layout;
		delete shader;
		delete texture;

	}

	void TextureTestScene::OnUpdate(float deltaTime) { }

	void TextureTestScene::OnRender() {
	
		texture->bind(1); //binds to slot 0 by default

		shader->bind();
		shader->setUniform1i("uTexture", 1); //setting the texture slot to use to 0

		vao->bind();
		ibo->bind();
		GLCall(glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr));
	
	}
	
	void TextureTestScene::OnImGuiRender() { 
	
		ImGui::Text("Texture Test!");

	}

} }