#pragma once
#include "Scene.h"
#include "FeatherFall-graphics.h"

namespace Application { namespace Scene {

	class SandboxScene : public Scene {
	private:

		core::graphics::Sprite playerSprite;
		core::graphics::Sprite groundSprite;
		core::graphics::BatchRenderer2D renderer;
		core::graphics::Shader shader;
		glm::mat4 ortho;
		glm::vec2 mousePos;

	public:

		SandboxScene();
		~SandboxScene();

		void OnUpdate(float deltaTime);
		void OnRender();
		void OnImGuiRender();

	private:



	};

} }