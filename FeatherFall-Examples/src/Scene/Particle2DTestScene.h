#pragma once

#include "Scene.h"
#include <FeatherFall-graphics.h>
#include "particles/ParticleSystem2D.h"

namespace Application { namespace Scene {

	class Particle2DTestScene : public Scene {
	private:

		core::particles::ParticleSystem2D* system;
		core::graphics::BatchRenderer2D renderer;
		glm::mat4 ortho;
		core::graphics::Shader shader;
		core::graphics::Texture texture;

	public: 
		Particle2DTestScene();
		~Particle2DTestScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private:



	};

} }