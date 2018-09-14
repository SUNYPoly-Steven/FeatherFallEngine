#include "MandelbrotScene.h"
#include <ImGui/imgui.h>


namespace Application { namespace Scene {

	#define PI 3.1415926f 

	MandelbrotScene::MandelbrotScene()
		: renderer(new core::graphics::BatchRenderer2D()),
		  shader(  new core::graphics::Shader("res/shaders/Mandelbrot.shader")),
		  ortho(   new glm::mat4(glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 1.0f))),
		  canvas(  new core::graphics::Renderable2D(glm::vec4(-2.0f,-1.0f, 0.0f, 1.0f), glm::vec2(4.0f, 2.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)))
	{
		shader->bind();
		shader->setUniformMat4("prMatrix", *ortho);
		shader->setUniform1i("max_iter", 1000);

		movexy[0] = 0.0f;
		movexy[1] = 0.0f;

		palette = new core::graphics::Texture("res/textures/pal.png");
		palette->bind(1);
		shader->setUniform1i("palette", 1);
	}

	MandelbrotScene::~MandelbrotScene() 
	{
		delete renderer;
		delete shader;
		delete ortho;
		delete canvas;
		delete palette;
	}

	void MandelbrotScene::OnUpdate(float deltaTime) {

		if (autoZoom) {
			static float acc = 0.1f;
			static float vel = acc;
			vel = vel + acc;
			zoom = zoom + vel;
		}

		if (autoRotate) {
			radians += rotSpeed; //should range from 0 - 2pi
			if (radians >= 2 * PI) radians = 0.0f;
			float sin = r * glm::sin(radians);
			float cos = r * glm::cos(radians);
			shader->setUniformVec2("vC", glm::vec2(cos, sin));
		}

		shader->setUniform1i("vMaxIter", iterDepth);

		//reset ortho
		*ortho = glm::mat4(glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 1.0f));

		//construct transform matrix (for zooming)

		glm::mat4 moveMat = glm::mat4(glm::translate(glm::vec3(movexy[0], movexy[1], 0.0f)));
		glm::mat4 zoomMat = glm::mat4(glm::scale(glm::vec3(zoom, zoom, 1.0f)));
		glm::mat4 transform = zoomMat * moveMat;

		//apply transform matrix
		*ortho = transform * (*ortho);

		shader->setUniformMat4("prMatrix", *ortho);
	}
	
	void MandelbrotScene::OnRender() {
	
		renderer->begin();

		renderer->submit(canvas);

		renderer->end();

		renderer->flush();
	
	}

	void MandelbrotScene::OnImGuiRender() {
	
		const char* mandelbrotStr = "Mandelbrot Set";
		const char* juliaStr = "Filled Julia Set";
		const char* buttonName = (doJulia) ? juliaStr : mandelbrotStr;

		if (ImGui::Button(buttonName)) {
			doJulia = !doJulia;
			shader->setUniform1i("flag", (int)doJulia);
		}

		if (doJulia) {
			ImGui::DragFloat("Angle", &radians, rotSpeed, 0.0f, 2.0f * PI);
			ImGui::InputFloat("Rotate Speed", &rotSpeed, 0.001f, 0.01f);
			ImGui::InputFloat("Radius", &r, 0.001f, 0.01f);
			ImGui::Checkbox("Auto Rotate", &autoRotate);
		}

		ImGui::NewLine();
		ImGui::InputInt("Iteration Depth", &iterDepth);

		ImGui::Begin("Zoom Controls");
		ImGui::DragFloat2("Translate", movexy, 0.01f, -1000.0f, 1000.0f);
		ImGui::DragFloat("Zoom", &zoom, 0.1f, 1.0f, 1000.0f);
		ImGui::Checkbox("Auto Zoom", &autoZoom);
		ImGui::End();
	
	}

} }