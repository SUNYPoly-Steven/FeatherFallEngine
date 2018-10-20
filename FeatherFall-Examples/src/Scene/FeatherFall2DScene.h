#pragma once

#include "Scene.h"
#include <FeatherFall-graphics.h>
#include "particles/ParticleSystem2D.h"

namespace Application {
	namespace Scene {

		class FeatherFall2DScene : public Scene {
		private:

			core::particles::ParticleSystem2D* system;
			core::graphics::BatchRenderer2D renderer;
			glm::mat4 ortho;
			core::graphics::Shader shader;
			core::graphics::Texture texture;

		public:

			FeatherFall2DScene();
			~FeatherFall2DScene();

			void OnUpdate(float deltaTime);
			void OnRender();
			void OnImGuiRender();

		private:



		};

	}
}