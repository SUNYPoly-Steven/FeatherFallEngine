#pragma once

#include "Scene.h"

#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/IBO.h"
#include "buffers/BufferLayout.h"

#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace Application { namespace Scene {

	class TextureTestScene : public Scene {
	private:

		core::buffers::VAO* vao;
		core::buffers::VBO* vbo;
		core::buffers::IBO* ibo;
		core::buffers::BufferLayout* layout;
		core::graphics::Shader* shader;

		core::graphics::Texture* texture;

	public:

		TextureTestScene();
		~TextureTestScene();

		void OnUpdate(float deltaTime) override ;
		void OnRender() override ;
		void OnImGuiRender() override ;

	private: 



	};

} }