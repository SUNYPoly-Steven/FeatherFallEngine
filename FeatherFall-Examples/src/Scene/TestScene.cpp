#include "TestScene.h"
#include <GL\glew.h>
#include <ImGui/imgui.h>
#include "debuging.h"


namespace Application { namespace Scene {  

	TestScene::TestScene()
		: clearColor { 0.2f, 0.5f, 0.1f, 1.0f }
	{
	}

	TestScene::~TestScene() {}

	void TestScene::OnUpdate(float deltaTime) {}

	void TestScene::OnRender() {
		GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
	}

	void TestScene::OnImGuiRender() {

		ImGui::ColorEdit4("Clear Color", clearColor);

	}

}}