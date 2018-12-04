#pragma once

#include "Scene.h"

#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/IBO.h"
#include "buffers/BufferLayout.h"

#include "graphics/Shader.h"

namespace Application { namespace Scene {

	class BuffersTestScene : public Scene {
	private:

		core::buffers::VAO* vao;
		core::buffers::VBO* vbo;
		core::buffers::IBO* ibo;
		core::buffers::BufferLayout* layout;
		core::graphics::Shader* shader;

	public:

		BuffersTestScene();
		~BuffersTestScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private:



	};

} }