#include "Particle2DTestScene.h"

namespace Application { namespace Scene {

	Particle2DTestScene::Particle2DTestScene()
		: ortho(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)),
			shader("res/shaders/ParticleSystem2DTest.shader"),
			texture("res/textures/feather_texture.png")
	{

		//std::function<core::particles::Particle2D*(const glm::vec3&)> lambda = [](const glm::vec3&) -> core::particles::Particle2D* {
		//	return new core::particles::Particle2D(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, -10.0f, 0.0f));
		//};
		system = new core::particles::ParticleSystem2D(
			glm::vec3(0.0f, 0.0f, 0.0f), 
			glm::vec3(0.0f, -10.0f, 0.0f),
			10.0f, 
			2.0f, 
			[](const glm::vec3&) -> core::particles::Particle2D* {
				return new core::particles::Particle2D(
					glm::vec3(1.0f, 0.0f, 0.0f), 
					glm::vec3(5.0f, 0.0f, 0.0f), 
					glm::vec3(0.0f, 0.0f, 0.0f)
				);
			},
			[](core::particles::Particle2D* p, float dt) -> void { /* empty lambda */ }
		);

		shader.bind();
		shader.setUniformMat4("prMatrix", ortho);

		//texture.bind();
		shader.setUniform1i("useTexture", 0);
	}

	Particle2DTestScene::~Particle2DTestScene()
	{
		delete system;
	}

	void Particle2DTestScene::OnUpdate(float deltaTime)
	{
		system->Create(deltaTime);
		system->Update(deltaTime);
	}

	void Particle2DTestScene::OnRender()
	{
		renderer.begin();

		//submit all the particles to be rendered
		system->Submit(renderer);

		renderer.end();

		renderer.flush();
	}

	void Particle2DTestScene::OnImGuiRender()
	{

	}

} }