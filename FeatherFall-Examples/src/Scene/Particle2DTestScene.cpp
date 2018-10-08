#include "Particle2DTestScene.h"

namespace Application { namespace Scene {

	Particle2DTestScene::Particle2DTestScene()
		: ortho(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)),
			shader("res/shaders/ParticleSystem2DTest.shader")
	{
		shader.bind();
		shader.setUniformMat4("prMatrix", ortho);
	}

	Particle2DTestScene::~Particle2DTestScene()
	{

	}

	void Particle2DTestScene::OnUpdate(float deltaTime)
	{
		system.Create(deltaTime);
		system.Update(deltaTime);
	}

	void Particle2DTestScene::OnRender()
	{
		renderer.begin();

		//submit all the particles to be rendered
		system.Submit(renderer);

		renderer.end();

		renderer.flush();
	}

	void Particle2DTestScene::OnImGuiRender()
	{

	}

} }