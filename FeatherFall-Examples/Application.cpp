#include "FeatherFall.h"
//std includes
#include <iostream>

//glm includes 
#include <glm/vec3.hpp>
#include <glm/detail/func_matrix.hpp>

//imgui includes
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw_gl3.h>

//Example includes
#include "src/Scene/Scene.h"
#include "src/Scene/MainMenuScene.h"
#include "src/Scene/TestScene.h"
#include "src/Scene/SandboxScene.h"
#include "src/Scene/BuffersTestScene.h"
#include "src/Scene/TextureTestScene.h"
#include "src/Scene/SimpleRendererScene.h"
#include "src/Scene/BatchRendererScene.h"
#include "src/Scene/BoidScene.h"
#include "src/Scene/MandelbrotScene.h"
#include "src/Scene/ComputeShaderScene.h"
#include "src/Scene/LayerScene.h"

//defines
#define WINDOW_FULLSCREEN false
#if WINDOW_FULLSCREEN
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#else
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576
#endif
#define WINDOW_TITLE "FeatherFall Examples"
#define WINDOW_VSYNC true


/* TODO:
 *     - Refactor ImGui into the window class
 *	   - Add texture support to the Batch Renderer
 *     - Fix the Simple Renderer
 *     - Refactor some examples to use proper
 *       abstracted methods, instead of raw OpenGL code
 *     - Begin work on 3D Renderer
 */

/*
 * NOTES:
 *    When making motion integrators, use verlet algorithm, or forestRuth
 *    integrator. They preserve motion (unlike traditional Euler and RK4)
 *    and are more precise then modified Euler
 */

using namespace Application;
using namespace Scene;
using namespace core;



int main(int argc, char** argv) {

	core::graphics::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_FULLSCREEN, WINDOW_VSYNC);

	//open ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window.window, true);
	ImGui::StyleColorsDark();

	Application::Scene::Scene* currScene = nullptr;

	//load the main menu scene (scene set up to pick example scene)
	MainMenuScene* mms = new MainMenuScene(currScene);
 
	mms->RegisterScene<TestScene>("Clear Color Test");
	mms->RegisterScene<SandboxScene>("Sandbox");
	mms->RegisterScene<BuffersTestScene>("Buffers");
	mms->RegisterScene<TextureTestScene>("Textures");
	mms->RegisterScene<SimpleRendererScene>("Simple Renderer");
	mms->RegisterScene<BatchRendererScene>("Batch Renderer");
	mms->RegisterScene<LayerScene>("Layer Scene");
	mms->RegisterScene<BoidScene>("Flocking (Boids)");
	mms->RegisterScene<MandelbrotScene>("Mandelbrot Set");
	mms->RegisterScene<ComputeShaderScene>("Simple Compute Shader");

	currScene = mms;//make the current scene the main menu scene (this will be changed by components inside main menu later)

	while (!window.windowShouldClose()) {
		//Clear the window for the new frame
		window.clear();

		ImGui_ImplGlfwGL3_NewFrame();
		if (currScene) {

			//profile this
			currScene->OnUpdate(ImGui::GetIO().DeltaTime);
			
			//profile this
			currScene->OnRender();

			//for switching scenes
			ImGui::Begin("Main Menu");
			if (currScene != mms && ImGui::Button("<--")) {
				SAFE_DELETE(currScene);
				currScene = mms;
				mms->OnReloadScene();
			}

			//profile this
			currScene->OnImGuiRender();

			ImGui::End();

		}

		//print framerate in "Profiler" window
		#if _DEBUG
		ImGui::Begin("Profiler (DEBUG Mode)");
		#else
		ImGui::Begin("Profiler (RELEASE Mode)");
		#endif
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		
		//end profiling stage and crate imGui window for collected data


		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();

	}
	if (currScene != mms) {
		SAFE_DELETE(mms);
	}
	SAFE_DELETE(currScene);


	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	

	return 0;

}