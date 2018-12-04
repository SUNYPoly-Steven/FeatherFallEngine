#pragma once
#include "Scene.h"
#include "FeatherFall-graphics.h"
#include "particles/ParticleSystem3D.h"

namespace Application { namespace Scene {

	class Particle3DScene : public Scene
	{

		core::graphics::SimpleRenderer3D m_Renderer;
		core::particles::ParticleSystem3D* system;

	public:
		Particle3DScene();
		~Particle3DScene();

		void OnUpdate(float deltaTime);
		void OnRender();
		void OnImGuiRender();

	};

} }

