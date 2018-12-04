#pragma once
#include "Scene.h"
#include <vector>
#include <functional>
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/IBO.h"
#include "buffers/BufferLayout.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Application { namespace Scene {

	class MainMenuScene : public Scene {
	public:
		std::vector<std::pair<const char*, std::function<Scene*()>>> scenes;
	private:

		Scene*& currentScene;

		core::buffers::VAO* vao;
		core::buffers::VBO* vbo;
		core::buffers::IBO* ibo;
		core::buffers::BufferLayout* layout;

		core::graphics::Texture* ffTex;
		core::graphics::Texture* iconTex;
		core::graphics::Shader* shader;

		glm::mat4* ortho;

		float texMix = 0.0f;
		double direction = 0.01;
		float frames = 0.0f;
		int stage = 0;
		double framed = 0.0;


	public:

		MainMenuScene(Scene*& pcurrentScene);
		~MainMenuScene();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void OnReloadScene();

		template<typename T>
		void RegisterScene(const char* name) {
			scenes.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:



	};

} }