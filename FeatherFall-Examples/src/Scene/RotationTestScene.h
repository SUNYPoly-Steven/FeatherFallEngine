#pragma once
#include "Scene.h"
#include "FeatherFall-graphics.h"

namespace Application { namespace Scene {

	class RotationTestScene : public Scene
	{
	private:

		core::particles::ParticleSystem2D* system;
		core::graphics::BatchRenderer2D renderer;
		glm::mat4 ortho;
		core::graphics::Shader shader;
		core::graphics::Texture texture;

		core::graphics::Sprite* testSprite;

	public:
		RotationTestScene();
		~RotationTestScene();

		void OnUpdate(float deltaTime);
		void OnRender();
		void OnImGuiRender();

	private:

	};

} }
