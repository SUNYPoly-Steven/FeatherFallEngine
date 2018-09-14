#pragma once
#include "FeatherFall-graphics.h"
#include <vector>

#define FLOCK_RADIUS 1.0f
#define CROWD_DIST   0.15f

namespace Application { namespace Boid {

		class Boid : public core::graphics::Renderable2D {
		private:

			glm::vec2 direction;
			std::vector<Boid*> flockMates;

		public:

			Boid(float px, float py, const glm::vec4& pcolor);
			~Boid();

			void updatePos();
			void updateFlockMates(const std::vector<Boid*>& boids);
			void updateSteer();

		private:

			bool inRadius(const Boid* boid) const;

		};

} }