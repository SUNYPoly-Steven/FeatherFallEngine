#pragma once
#include <vector>
#include "../FeatherFall-graphics.h"

namespace core {

	class Layer {
	private:

		graphics::Renderer2D* m_Renderer;
		std::vector<graphics::Renderable2D*> m_Renderables;

	public:

		void add(graphics::Renderable2D* renderable);
		void render();

	protected:

		Layer(graphics::Renderer2D* renderer);
		~Layer();

	private:



	};

}