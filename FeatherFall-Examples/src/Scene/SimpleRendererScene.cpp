#include "SimpleRendererScene.h"
#include <ImGui/imgui.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/Renderable2D.h"

namespace Application { namespace Scene {

	SimpleRendererScene::SimpleRendererScene()
		: rpos{ 0.0f, 0.0f, 0.0f }, rsize{ 1.0f, 1.0f }, rcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, numRenderables(1)
	{
		glm::mat4* ortho = new glm::mat4(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f));
		core::graphics::Shader* shader = new core::graphics::Shader("res/shaders/SimpleRendererTest.shader");

		renderer = new core::graphics::SimpleRenderer2D(ortho, shader);

		sprite = new core::graphics::Sprite(
			rpos[0], rpos[1], rsize[0], rsize[1], 
			glm::vec4(rcolor[0], rcolor[1], rcolor[2], rcolor[3])
		);
	}

	SimpleRendererScene::~SimpleRendererScene() { 
		delete renderer;
		delete sprite;
	}

	void SimpleRendererScene::OnUpdate(float deltaTime) { }

	void SimpleRendererScene::OnRender() {
		
		renderer->begin();

		//Submit Renderables to be rendered
		for (int i = 0; i < numRenderables; ++i) {
			renderer->submit(sprite);
		}

		renderer->end();

		//flush the render queue
		renderer->flush();

	}
	
	void SimpleRendererScene::OnImGuiRender() {
		//ImGui::Text("Simple Renderer Test!");

		ImGui::Text("SimpleRenderer2D is BROKEN! PLEASE FIX ME!!");

		//ImGui::SliderFloat3("Renderable Position", rpos, -8.0f, 8.0f);
		//ImGui::SliderFloat2("Renderable Size", rsize, 0.25f, 5.0f);
		//ImGui::ColorEdit4("Renderable Color", rcolor);
		//ImGui::InputInt("Number of Renderables", &numRenderables);

	}

} }