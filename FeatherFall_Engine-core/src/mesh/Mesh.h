#pragma once
#include "../graphics/Renderable3D.h"

namespace core {
	namespace mesh {
		class Mesh : public graphics::Renderable3D {
		private:

						

		public:

			Mesh(const char* filepath);
			~Mesh();



		private:

			void ReadFile(const char* filepath);

		};
	}
}
