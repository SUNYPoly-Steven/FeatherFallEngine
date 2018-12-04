#pragma once
#include "Scene.h"
#include "FeatherFall-graphics.h"
#include "mesh/Mesh.h"

namespace Application { namespace Scene {

	class Renderer3DScene : public Scene {
	private:

		core::graphics::SimpleRenderer3D m_Renderer;
		core::graphics::Renderable3D* m_Cube;
		core::graphics::Renderable3D* m_Floor;
		//core::graphics::Camera m_Camera;

		core::graphics::Renderable3D* m_Feather;
		core::graphics::Renderable3D* m_DebugIco;

		glm::mat4 mlMatrix;

	public:

		Renderer3DScene();
		~Renderer3DScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private:



	};

} }