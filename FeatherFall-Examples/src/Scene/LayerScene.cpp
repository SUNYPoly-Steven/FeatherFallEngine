#include "LayerScene.h"
#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

namespace Application { namespace Scene {

	LayerScene::LayerScene()
		: tileLayer(new core::Layer2D()),
		ortho(new glm::mat4(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))),
		shader(new core::graphics::Shader("res/shaders/LayerSceneTest.shader"))
	{
		srand((unsigned int)time(NULL));

		for (float y = -9.0f; y < 9.0f; y += 1.0f) {
			for (float x = -16.0; x < 16.0f; x += 1.0f) {
				tileLayer->add(new core::graphics::Sprite(
					x, y, 0.9f, 0.9f,
					glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
				));
			}
		}

		shader->bind();
		shader->setUniformMat4("prMatrix", *ortho);
	}

	LayerScene::~LayerScene()
	{
		delete tileLayer;
		delete ortho;
		delete shader;
	}

	void LayerScene::OnUpdate(float deltaTime)
	{

	}

	void LayerScene::OnRender() 
	{
		tileLayer->render();
	}

	void LayerScene::OnImGuiRender()
	{
		ImGui::Text("2D Layer Support!");
	}

} }