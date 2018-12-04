#pragma once
#include "../graphics/Renderable3D.h"

namespace core {
	namespace mesh {
		class Mesh : public graphics::Renderable3D {
		private:

						

		public:

			Mesh(const char* filepath);
			~Mesh();


			static core::graphics::Renderable3D* ReadFile(const char* filepath);

		private:


		};
	}
}
