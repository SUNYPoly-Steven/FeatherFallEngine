#pragma once
#include "Scene.h"
#include <glm/glm.hpp>


namespace Application { namespace Scene {

	class TestScene : public Scene {
	private:

		float clearColor[4];

	public:

		TestScene();
		~TestScene();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:



	};

}}