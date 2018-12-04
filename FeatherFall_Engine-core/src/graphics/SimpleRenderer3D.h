#pragma once
#include "Renderer3D.h"
#include <deque>
#include "../buffers/VAO.h"
#include "Shader.h"
#include "Camera.h"


namespace core { namespace graphics {

	class SimpleRenderer3D : public Renderer3D {
	private:

		//buffers::VAO m_VAO;

		std::deque<const Renderable3D*> m_RenderQueue;

	public:
		Shader* m_Shader;
		core::graphics::Camera* m_Camera;

		SimpleRenderer3D(Shader* pshader, Camera* cam);
		~SimpleRenderer3D();

		void begin() override;
		void submit(const Renderable3D* renderable) override;
		void end() override;
		void flush() override;

	private:



	};

} }