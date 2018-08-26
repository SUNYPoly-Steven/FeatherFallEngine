#include "SandboxScene.h"
#include <GL\glew.h>
#include "debuging.h"
#include <ImGui\imgui.h>
#include <glm\glm.hpp>
#include <glm/detail/func_matrix.hpp>


namespace Application { namespace Scene {

	SandboxScene::SandboxScene()
		: playerSprite(-1.5, 0, 3, 3, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
		  groundSprite(-16, -9, 32, 8, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
		  shader("res/shaders/Sandbox.shader"),
		  ortho(glm::ortho(-16.0, 16.0, -9.0, 9.0, -1.0, 1.0))
	{
		shader.bind();
		shader.setUniformMat4("prMatrix", ortho);
	}

	SandboxScene::~SandboxScene() {}

	void SandboxScene::OnUpdate(float deltaTime) 
	{
	
		mousePos.x = ImGui::GetMousePos().x;
		mousePos.y = ImGui::GetMousePos().y;

		// #Dev_Note: when architechting the movement system, 
		//            set it up similar to the rendering system.
		//            it could be used a lot like the rendering API,
		//            where you will submit "movables" to the system,
		//            and the system will "flush" its buffer and update,
		//            all submitted "movables".
		//
		//            i.e.
		// 
		//            MotionSystem->submit(Movable2D);
		//            MotionSystem->flush();
		//
		//            P.S. - if its constructed this way. would it be
		//                   possible to map the position data to a buffer
		//                   on the GPU and get the updates rendered from 
		//                   a compute shader? (one problem with this is 
		//                   you will have to copy data into GPU and then
		//                   back out every frame?)
		//           
		//            P.P.S - if you could submit all the sprites that need
		//                    to be updated every frame at the setup of the
		//                    scene, you might not have to take that data off
		//                    of the GPU, and could instead just use texture
		//                    data to store and read vertex positions directly
		//                    on the GPU. which has the added benefit of not
		//                    needing to pass the position data to the renderer
		//                    every frame, right?

	}
	
	void SandboxScene::OnRender() 
	{

		//Set uniforms here
		shader.setUniformVec4("playerPos", playerSprite.getPosition());//glm::vec4(mousePos, 0.0f, 1.0f));

		renderer.begin();

		renderer.submit(&playerSprite);
		renderer.submit(&groundSprite);

		renderer.end();

		renderer.flush();

	}

	void SandboxScene::OnImGuiRender()
	{
	
		ImGui::Text("This is the Sandbox!");
	
	}

}}
