#pragma once
#include "Scene.h"
#include "FeatherFall-graphics.h"
#include <vector>

float temp1(float);

namespace Application { namespace Scene {

	class TSPScene : public Scene {
	private:

		// for Sim Anneal
		std::vector<std::pair<float, float>> m_Map;
		std::vector<unsigned int> m_Path;
		std::vector<unsigned int> m_NewPath;
		float m_Time = 0.0f;

		//for FF Rendering
		core::graphics::BatchRenderer2D m_Renderer;
		glm::mat4 m_projMat;
		core::graphics::Shader m_Shader;
		core::graphics::Texture m_CityTex;

		//for ImGui
		float m_CitySize[2];
		float m_CityColor[4];

		float m_PathColor[4];
		float m_PathThickness;

		std::vector<float> m_TempPoints;
		int m_MaxPoints;

		std::vector<float> m_FitPoints;

		bool m_UseTextures;
		float m_ClearColor[4]; 

		float(*tempFunc)(float) = temp1;


		
	public:

		TSPScene();
		~TSPScene();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

		void ReadFile(const char* filepath);
		void Anneal();

		void Restart();
		void RestoreDefaults();

	};

} }