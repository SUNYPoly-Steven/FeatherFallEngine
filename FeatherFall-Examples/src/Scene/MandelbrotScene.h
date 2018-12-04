#pragma once

#include "Scene.h"
#include "FeatherFall-graphics.h"

namespace Application { namespace Scene {

	class MandelbrotScene : public Scene {
	private:

		core::graphics::Renderer2D* renderer;
		core::graphics::Shader* shader;
		glm::mat4* ortho;

		core::graphics::Renderable2D* canvas;

		float movexy[2];
		float zoom = 1.0f;
		float radians = 0.0f;
		float rotSpeed = 0.001f;
		float r = 0.7885f;
		int iterDepth = 1000;

		bool autoZoom = false;
		bool autoRotate = false;
		bool doJulia = false; 

		core::graphics::Texture* palette;

	public:

		MandelbrotScene();
		~MandelbrotScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private:



	};

} }