#pragma once

#include "Scene.h"
#include "graphics/BatchRenderer2D.h"
#include "graphics/Renderable2D.h"
#include "graphics/Shader.h"

namespace Application { namespace Scene {

	class BatchRendererScene : public Scene {
	private:

		core::graphics::BatchRenderer2D* renderer;

		glm::mat4* ortho;
		core::graphics::Shader* shader;
		glm::vec2 mousePos;
		int lightStr = 40;
		bool doLighting = true;

		std::vector<core::graphics::Renderable2D*> sprites;

	public:

		BatchRendererScene();
		~BatchRendererScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private:



	};

} }