#include "MainMenuScene.h"
//imgui includes
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw_gl3.h>
#include "debuging.h"

namespace Application { namespace Scene {
	
	MainMenuScene::MainMenuScene(Scene*& pcurrentScene)
		: currentScene(pcurrentScene)
	{

		using namespace core;
		using namespace graphics;

		vao = new buffers::VAO();

		float vertexData[] = {
//            X      Y      Z      U      V
			-4.0f, -4.0f,  0.0f,  0.0f,  0.0f, //0
			 4.0f, -4.0f,  0.0f,  1.0f,  0.0f, //1
			 4.0f,  4.0f,  0.0f,  1.0f,  1.0f, //2
			-4.0f,  4.0f,  0.0f,  0.0f,  1.0f  //3
		};
		vbo = new buffers::VBO((const void*)vertexData, 4 * 9 * sizeof(float));

		unsigned int indices[] = { 
			0, 1, 2, 2, 3, 0 //FF Textured Quad
		};
		ibo = new buffers::IBO(indices, 6);

		layout = new buffers::BufferLayout();
		layout->push<float>(3); //add position data
		layout->push<float>(2); //add texture coord data

		vao->addBuffer(*vbo, *layout);

		shader = new graphics::Shader("res/shaders/MainMenu.shader");

		ffTex = new graphics::Texture("res/textures/FeatherFall-MainMenu.png");
		iconTex = new Texture("res/textures/FeatherFall-Owl.png");

		ortho = new glm::mat4(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f));

		OnReloadScene(); //load Scene for first time

	}

	MainMenuScene::~MainMenuScene() 
	{

		delete vao;
		delete vbo;
		delete ibo;
		delete layout;

		delete ffTex;
		delete shader;

		delete ortho;

	}

	void MainMenuScene::OnUpdate(float deltaTime) 
	{

	}

	void MainMenuScene::OnRender() 
	{
		
		shader->setUniform1f("percentage", texMix);
		GLCall(glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr));

	}

	void MainMenuScene::OnImGuiRender() 
	{

		ImGui::Text("Select a Scene to load: ");
		for (auto& scene : scenes) {
			if (ImGui::Button(scene.first)) {
				currentScene = scene.second();
			}
		}

		ImGui::Begin("BG Texture Control");
		ImGui::SliderFloat("Texture Control", &texMix, 0.0f, 1.0f);
		ImGui::Text("TODO: Make Gradient BG!");
		ImGui::End();

	}

	void MainMenuScene::OnReloadScene() 
	{

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		ffTex->bind(0);
		iconTex->bind(1);

		shader->bind();
		shader->setUniformMat4("prMatrix", *ortho);
		shader->setUniform1i("ffTex", 0);
		shader->setUniform1i("iconTex", 1);

		vao->bind();
		ibo->bind();

	}

}}