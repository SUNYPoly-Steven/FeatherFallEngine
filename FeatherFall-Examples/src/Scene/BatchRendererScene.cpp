#include "BatchRendererScene.h"
#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>
#include "graphics/Sprite.h"
#include "graphics/Window.h"


namespace Application { namespace Scene {

	BatchRendererScene::BatchRendererScene() 
	{
		ortho = new glm::mat4(glm::ortho(0.0f, 1024.0f, 0.0f, 576.0f, -1.0f, 1.0f));
		shader = new core::graphics::Shader("res/shaders/BatchRendererTest.shader");
		renderer = new core::graphics::BatchRenderer2D();

		srand((unsigned int)time(NULL));

		for (float y = 0; y < 576.0f; y += 5.0f) {
			for (float x = 0; x < 1024.0f; x += 5.0f) {
				sprites.push_back(new core::graphics::Sprite(
					x, y, 4.0f, 4.0f,
					//glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)
					glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
				));
			}
		}
	}

	BatchRendererScene::~BatchRendererScene() {
		delete ortho;
		delete shader;
		delete renderer;
	}

	void BatchRendererScene::OnUpdate(float deltaTime) {
	
		mousePos.x = ImGui::GetMousePos().x;
		mousePos.y = ImGui::GetMousePos().y;
		mousePos.y = 576.0f - mousePos.y;
			
	}

	void BatchRendererScene::OnRender() {

		renderer->begin();

		//renderer->submit( ... )
		for (int i = 0; i < sprites.size(); ++i) {
			renderer->submit(sprites[i]);
		}

		renderer->end();

		//shader setup here
		shader->bind();
		shader->setUniformMat4("prMatrix", *ortho);
		shader->setUniformVec2("mousePos", mousePos);
		shader->setUniform1f("strength", (float)lightStr);
		shader->setUniform1i("doLight", (int)doLighting);

		renderer->flush();
	
	}

	void BatchRendererScene::OnImGuiRender() {
	
		ImGui::Text("Batch Renderer Test!");
		float winWidth = ImGui::GetWindowWidth();
		float winHeight = ImGui::GetWindowHeight();
		ImGui::Text("Window Size: %.1f, %.1f", winWidth, winHeight);
		ImGui::Text("Sprite Count: %d", sprites.size());
		ImGui::Text("Light Position: %.1f, %.1f", mousePos.x, mousePos.y);
		ImGui::InputInt("Light Strength", &lightStr, 1, 10);
		ImGui::Checkbox("Do Lighting Calculation", &doLighting);


	}


} }