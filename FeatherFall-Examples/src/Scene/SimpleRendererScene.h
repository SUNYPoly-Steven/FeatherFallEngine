#pragma once
#include "Scene.h"

#include "graphics/SimpleRenderer2D.h"
#include "graphics/Renderable2D.h"
#include "graphics/Shader.h"
#include "graphics/Sprite.h"

namespace Application { namespace Scene {

	class SimpleRendererScene : public Scene {
	private:

		core::graphics::SimpleRenderer2D* renderer;

		float rpos[3];
		float rsize[2];
		float rcolor[4];

		int numRenderables;

		core::graphics::Sprite* sprite;

	public:

		SimpleRendererScene();
		~SimpleRendererScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private:



	};

} }