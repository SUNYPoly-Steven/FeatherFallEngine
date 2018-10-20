#include "FeatherFall2DScene.h"
#include <cstdlib>
#include <ctime>

namespace Application {
	namespace Scene {

		FeatherFall2DScene::FeatherFall2DScene()
			: ortho(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)),
			shader("res/shaders/ParticleSystem2DTest.shader"),
			texture("res/textures/feather_texture.png")
		{
			srand((unsigned) time(NULL));
			system = new core::particles::ParticleSystem2D(glm::vec3(0.0f, 4.5f, 0.0f), 10.0f, 5.0f, [](const glm::vec3& spawnPoint) -> core::particles::Particle2D* {
				return new core::particles::Particle2D(spawnPoint + glm::vec3((((float)rand() / (float)RAND_MAX) * 16.0) - 8.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -10.0f, 0.0f));
			});

			shader.bind();
			shader.setUniformMat4("prMatrix", ortho);

			texture.bind();
			shader.setUniform1i("tex", 0);
		}

		FeatherFall2DScene::~FeatherFall2DScene()
		{

		}

		void FeatherFall2DScene::OnUpdate(float deltaTime)
		{
			system->Create(deltaTime);
			system->Update(deltaTime);
		}

		void FeatherFall2DScene::OnRender()
		{
			renderer.begin();

			//submit all the particles to be rendered
			system->Submit(renderer);

			renderer.end();

			renderer.flush();
		}

		void FeatherFall2DScene::OnImGuiRender()
		{

		}

	}
}