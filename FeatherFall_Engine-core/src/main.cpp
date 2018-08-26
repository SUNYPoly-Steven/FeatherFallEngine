#include "FeatherFallEngine.h"
#include "buffers/BufferLayout.h"

//std includes
#include <iostream>

//glm includes 
#include <glm/vec3.hpp>
#include <glm/detail/func_matrix.hpp>

//imgui includes
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw_gl3.h>



//defines
#define WINDOW_FULLSCREEN false
#if WINDOW_FULLSCREEN
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#else
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576
#endif
#define WINDOW_TITLE "FeatherFall Engine"
#define WINDOW_VSYNC true


/*
	Ideas:
	   - Multithreading Job System (MJS) to update particles simultainiously

	   - Consider making setUniform***() to non-static and use the getUniformLoc()
	     inside of set function instead of passing and int pass the char*

*/

using namespace core;
using namespace graphics;
using namespace buffers;


void update(const Window& window, Camera* camera);

int main() {

	Log::init();
	Log::printText("White for Nominal Message.");
	Log::printWarning("Yellow for Warning Message.");
	Log::printError("Red for Error Message.");

	Window window = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, WINDOW_FULLSCREEN, WINDOW_VSYNC);

	window.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));


	float verts[] = {
//        X        Y      Z         R     G     B     A
		-0.25f, -0.25f, -2.0f,     1.0f, 0.0f, 0.0f, 1.0f,//0 (Bottom Left) **FRONT**
		 0.25f, -0.25f, -2.0f,     0.0f, 1.0f, 0.0f, 1.0f,//1 (Bottom Right)
		 0.25f,  0.25f, -2.0f,     0.0f, 0.0f, 1.0f, 1.0f,//2 (Top Right)
		-0.25f,  0.25f, -2.0f,     1.0f, 1.0f, 1.0f, 1.0f,//3 (Top Left)

		-0.25f, -0.25f, -2.5f,     1.0f, 0.0f, 0.0f, 1.0f,//4 (Bottom Left) **BACK**
		 0.25f, -0.25f, -2.5f,     0.0f, 1.0f, 0.0f, 1.0f,//5 (Bottom Right)
		 0.25f,  0.25f, -2.5f,     0.0f, 0.0f, 1.0f, 1.0f,//6 (Top Right)
		-0.25f,  0.25f, -2.5f,     1.0f, 1.0f, 1.0f, 1.0f //7 (Top Left)
	};

	unsigned int indices[] = {  //BUG_REPORT: The engine is rendering the verts 
		                        //            in this order, and not based on 
		                        //            the depth buffer.

		0, 1, 2, //front face 
		2, 3, 0, 

		1, 5, 6, //right face
		6, 2, 1, 

		5, 4, 7, //back face
		7, 6, 5,

		4, 0, 3, //left face
		3, 7, 4,

		3, 2, 6, //top face
		6, 7, 3,
		
		4, 5, 1, //bottom face
		1, 0, 4

	};

	VAO vao = VAO();

	VBO vbo = VBO(verts, 8 * 7 * sizeof(float));
	IBO ibo = IBO(indices, 36);
	BufferLayout layout = BufferLayout();
	layout.push<float>(3); //adds layout for positions
	layout.push<float>(4); //adds layout for colors
	vao.addBuffer(vbo, layout);

	glm::vec4 color(0.2f, 0.4f, 0.8f, 1.0f);
	glm::mat4 proj;
	glm::mat4 view;

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1000.0f, 
		WINDOW_WIDTH, WINDOW_HEIGHT);

	window.camera = &camera; //for mouse look
	
	glm::mat4 modelMat;
	glm::mat4 normalMat = glm::transpose(glm::inverse(camera.getViewMatrix() * modelMat));


	Shader shader_main("res/shaders/Basic.shader");
	Shader debug("res/shaders/debug.shader");


	//TEMP: ImGui Code
	ImGui::CreateContext();

	/*NOTE: this function removes the keyboard and mouse inputs. find a way around this*/
	//ImGui_ImplGlfwGL3_Init(window.window, true); //NOTE: PLEASE MOVE THE IMGUI
										 //INTO THE WINDOW CLASS, OR DIFFERENT
										//SOLUTION. PUTTING IT IN THE MAIN 
									   //FILE IS UGLY.
	//ImGui::StyleColorsDark();
	//bool show_demo_window = true;
	//bool show_another_window = false;
	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!window.windowShouldClose()) {
		window.clear();

		//TEMP: ImGui Code
		//ImGui_ImplGlfwGL3_NewFrame();


		update(window, &camera);

		proj = camera.getProjectionMatrix();
		view = camera.getViewMatrix();

		shader_main.bind();
		
		shader_main.setUniformMat4("projMat", proj);
		shader_main.setUniformMat4("viewMat", view);
		//Shader::setUniformMat4(shader_main.getUniformLocation("modelMat"), modelMat);
		//Shader::setUniformMat4(shader_main.getUniformLocation("normalMat"), normalMat);

		//renderer.draw(vao, ibo, shader_main);
		shader_main.unbind();

		//renders debug shader if the tab key is being pressed
		if (window.isKeyPressed(GLFW_KEY_TAB)) {
			debug.bind();
			debug.setUniformMat4("projMat", proj);
			debug.setUniformMat4("viewMat", view);

			//renderer.draw(vao, ibo, debug);
		}



		//TEMP: ImGui Code
		/*{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}*/

		// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
		/*if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
		if (show_demo_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
			ImGui::ShowDemoWindow(&show_demo_window);
		}





		//TEMP: ImGui Code
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		*/

		window.update();

	}

	//TEMP: ImGui Code
	//ImGui_ImplGlfwGL3_Shutdown();
	//ImGui::DestroyContext();

	return 0;

}

void update(const Window& window, Camera* camera) {
	bool w = window.isKeyPressed(GLFW_KEY_W);
	bool a = window.isKeyPressed(GLFW_KEY_A);
	bool s = window.isKeyPressed(GLFW_KEY_S);
	bool d = window.isKeyPressed(GLFW_KEY_D);

	bool i = window.isKeyPressed(GLFW_KEY_I);
	bool j = window.isKeyPressed(GLFW_KEY_J);
	bool k = window.isKeyPressed(GLFW_KEY_K);
	bool l = window.isKeyPressed(GLFW_KEY_L);

	if (w) camera->forward(0.1f);
	if (a) camera->strafeRight(-0.1f);
	if (s) camera->forward(-0.1f);
	if (d) camera->strafeRight(0.1f);

	if (i) camera->rotateUp(0.1f);
	if (j) camera->rotateRight(0.1f);
	if (k) camera->rotateUp(-0.1f);
	if (l) camera->rotateRight(-0.1f);

}
