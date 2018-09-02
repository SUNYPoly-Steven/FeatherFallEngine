#pragma once
#include "Renderer3D.h"
#include <deque>
#include "../buffers/VAO.h"
#include "Shader.h"


namespace core { namespace graphics {

	class SimpleRenderer3D : public Renderer3D {
	private:

		//buffers::VAO m_VAO;

		std::deque<const Renderable3D*> m_RenderQueue;

	public:
		Shader* m_Shader;

		SimpleRenderer3D(Shader* pshader);
		~SimpleRenderer3D();

		void begin() override;
		void submit(const Renderable3D* renderable) override;
		void end() override;
		void flush() override;

	private:



	};

} }