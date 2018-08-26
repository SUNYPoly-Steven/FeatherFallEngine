#pragma once
#include "Scene.h"
#include "graphics/Shader.h"

namespace Application { namespace Scene {

	class ComputeShaderScene : public Scene {
	private:

		core::graphics::Shader* compute;
		core::graphics::Shader* gfx;
		unsigned int tex;
		float time = 0;
		float lastDelta = 0;

	public:

		ComputeShaderScene();
		~ComputeShaderScene();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:



	};

} }