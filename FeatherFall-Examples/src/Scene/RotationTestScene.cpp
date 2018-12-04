#include "RotationTestScene.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <glm/gtx/vector_angle.hpp>

#define PI 3.14159265f

namespace Application { namespace Scene {

	RotationTestScene::RotationTestScene()
		: ortho(glm::ortho(-8.0f, 8.0f, -5.0f, 4.0f, -1.0f, 1.0f)),
		shader("res/shaders/RotationTest.shader"),
		texture("res/textures/feather_texture.png")
	{

		srand((unsigned)time(NULL));

		auto FeatherRainEffectSpawnLambda = [](const glm::vec3& spawnPoint) -> core::particles::Particle2D* {
				
			return new core::particles::Particle2D(
				spawnPoint + glm::vec3(
				(((float)rand() / (float)RAND_MAX) * 16.0) - 8.0f,
					0.0f,
					0.0f
				),                               // pos
				glm::vec3(0.0f, 0.0f, 0.0f),     // vel
				glm::vec3(0.0f, 0.0f, 0.0f)      // acc
												 // age = 0.0f
			);
		};

		auto FeatherRainEffectUpdateLambda = [](core::particles::Particle2D* particle, float deltaTime) {

			auto dampedSin = [](float t) {
				return sin(4*t);
			};


			auto Cd = 1.0f; // coefficient of drag
			auto airDensity = 1.0f; 
			auto vel = particle->velocity;
			auto area = 1.0f;

			auto drag = Cd * (airDensity * (vel * vel) / 2.0f) * area;

			glm::vec3 swing = glm::vec3(dampedSin(particle->age), 0.0f, 0.0f);

			auto newAcc = drag + swing;

			particle->acceleration = newAcc; //update acc

			auto angle = glm::angle(glm::normalize(newAcc), glm::vec3(0.0f, 1.0f, 0.0f));

			particle->StaticRotate(
				(newAcc.x < 0) 
					? (angle *  2.0f + (PI/3.0f)) 
					: (angle * -2.0f + (PI/3.0f)),
				glm::vec3(0.0f, 0.0f, 1.0f)
			);
			

		};

		system = new core::particles::ParticleSystem2D(
			glm::vec3(0.0f, 4.5f, 0.0f),   // emitter pos
			glm::vec3(0.0f, -10.0f, 0.0f), // gravity
			5.0f,                          // spawn rate
			15.0f,                         // life span
			FeatherRainEffectSpawnLambda,
			FeatherRainEffectUpdateLambda
		);

		shader.bind();
		shader.setUniformMat4("prMatrix", ortho);

		texture.bind();
		shader.setUniform1i("tex", 0);


		testSprite = new core::graphics::Sprite(
			-1.0f, -1.0f,                     // (x, y)
			 2.0f,  2.0f,                     // (w, h)
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // color (RGBA)
		);

	}

	RotationTestScene::~RotationTestScene()
	{
		delete system;
	}

	void RotationTestScene::OnUpdate(float deltaTime)
	{
		system->Create(deltaTime);
		system->Update(deltaTime);
		//testSprite->Rotate(1.0 * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));

	}
	
	void RotationTestScene::OnRender()
	{
		renderer.begin();
		/*
		for (auto& particle : system->particles) {
			renderer.line(
				glm::vec2(particle->getPosition()),
				glm::vec2(particle->getPosition() + particle->acceleration)
			);
		}
		*/

		//submit all the particles to be rendered
		system->Submit(renderer);
		//renderer.submit(testSprite);

		renderer.end();

		renderer.flush();
	}
	
	void RotationTestScene::OnImGuiRender()
	{
		
	}

} }
