#include "BoidScene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <ImGui/imgui.h>
#include <stdlib.h>
#include <time.h>

#define INIT_BOID_COUNT 100

namespace Application { namespace Scene {

	using namespace core::graphics;

	bool BoidScene::doSeparation;
	bool BoidScene::doAlignment;
	bool BoidScene::doCohesion;
	bool BoidScene::doNoise;
	bool BoidScene::doAvoid;
	bool BoidScene::doMouseTracking;
	glm::vec2 BoidScene::trackPos;

	BoidScene::BoidScene()
	{

		srand((unsigned int)time(NULL));

		renderer = new BatchRenderer2D();
		ortho = new glm::mat4(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f));
		shader = new Shader("res/shaders/Boids.shader");

		for (int i = 0; i < INIT_BOID_COUNT; ++i) {
			boids.push_back(new Boid::Boid(
				((rand() % 16000) / 1000.0f) - 8.0f, 
				((rand() %  9000) / 1000.0f) - 4.5f, 
				glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		}

		shader->bind();
		shader->setUniformMat4("prMatrix", *ortho);

		doSeparation    = true;
		doAlignment     = true;
		doCohesion      = true;
		doNoise         = true;
		doAvoid         = false;
		doMouseTracking = false;
		trackPos = glm::vec2(0.0f, 0.0f);
	}

	BoidScene::~BoidScene() {
		delete renderer;
		delete ortho;
		delete shader;
		for (int i = 0; i < boids.size(); ++i) {
			delete boids[i];
		}
	}

	void BoidScene::OnUpdate(float deltaTime) {
		
		trackPos = glm::vec2((ImGui::GetMousePos().x - 512.0f) / 32.0f, (288.0f - ImGui::GetMousePos().y) / 18.0f);


		for (int i = 0; i < boids.size(); ++i) {

			boids[i]->updateFlockMates(boids);
			boids[i]->updateSteer();
			boids[i]->updatePos();

		}



	}

	void BoidScene::OnRender() {

		renderer->begin();

		for (int i = 0; i < boids.size(); ++i) 
			renderer->submit((Renderable2D*)boids[i]);

		renderer->end();

		renderer->flush();

	}

	void BoidScene::OnImGuiRender() {
		ImGui::Text("BOIDS!!!!");
		if (ImGui::Button("Reset Boids"))
			ResetBoids();

		ImGui::Checkbox("doSeparation",    &doSeparation);
		ImGui::Checkbox("doAlignment",     &doAlignment);
		ImGui::Checkbox("doCohesion",      &doCohesion);
		ImGui::Checkbox("doNoise",         &doNoise);
		ImGui::Checkbox("doAvoid",         &doAvoid);
		ImGui::Checkbox("doMouseTracking", &doMouseTracking);
	}

	void BoidScene::ResetBoids() {

		for (int i = 0; i < boids.size(); ++i) {
			delete boids[i];
		}
		boids.clear();

		for (int i = 0; i < INIT_BOID_COUNT; ++i) {
			boids.push_back(new Boid::Boid(
				((rand() % 16000) / 1000.0f) - 8.0f,
				((rand() % 9000) / 1000.0f) - 4.5f,
				glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		}
	}


} }