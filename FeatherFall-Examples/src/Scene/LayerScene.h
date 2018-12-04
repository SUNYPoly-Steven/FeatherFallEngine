#pragma once
#include "Scene.h"
#include "FeatherFall-graphics.h"
#include "layers/Layer2D.h"


namespace Application { namespace Scene {

	class LayerScene : public Scene {
	private:

		core::Layer2D* tileLayer;
		glm::mat4* ortho;
		core::graphics::Shader* shader;

	public:

		LayerScene();
		~LayerScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private:



	};

} }