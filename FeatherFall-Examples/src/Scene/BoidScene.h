#pragma once

#include "Scene.h"
#include "FeatherFall-graphics.h"
#include "../Boids/Boid.h"

namespace Application { namespace Scene {

		class BoidScene : public Scene {
		private:

			std::vector<Application::Boid::Boid*> boids;

			core::graphics::Renderer2D* renderer;
			core::graphics::Shader* shader;
			glm::mat4* ortho;

			

		public:

			static bool doSeparation;
			static bool doAlignment;
			static bool doCohesion;
			static bool doNoise;
			static bool doAvoid;
			static bool doMouseTracking;
			static glm::vec2 trackPos;

			BoidScene();
			~BoidScene();

			void OnUpdate(float deltaTime) override ;
			void OnRender() override ;
			void OnImGuiRender() override ;

		private:

			void ResetBoids();

		};

} }