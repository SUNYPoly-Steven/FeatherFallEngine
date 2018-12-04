#include "TSPScene.h"
#include "debuging.h"
#include "logging/Logging.h"
#include "Auto.h"
#include <ImGui/imgui.h>

#include <fstream>   // for file reading
#include <cmath>     // for sqrt and exp
#include <algorithm> // for std::reverse
#include <ctime>     // for time(NULL)

#define OpenGUIWindow(WindowTitle) \
			ImGui::Begin(WindowTitle);\
			Auto(ImGui::End())

void gen_path(std::vector<unsigned int>& output, unsigned int mapSize);
float fitness(const std::vector<std::pair<float, float>>& map, const std::vector<unsigned int>& path);
float dist(const std::pair<float, float>* from, const std::pair<float, float>* to);
void step(const std::vector<unsigned int>& src, std::vector<unsigned int>& dest);
float temp1(float currTime);
float temp2(float currTime);
float temp3(float currTime);
float P(float s, float snew, float t);

unsigned int F4toU32(float rgba[4]);

namespace Application { namespace Scene {

	TSPScene::TSPScene()
			: m_projMat(glm::ortho(-10.0f, 30.0f, -1.25f, 21.25f, -1.0f, 1.0f)),
			m_Shader("res/shaders/ParticleSystem2DTest.shader"),
			m_CityTex("res/textures/city-icon.png")
		{
			//make all ImGui settings their defaults
			RestoreDefaults();

			//set up for FF rendering
			m_Shader.bind();
			m_Shader.setUniformMat4("prMatrix", m_projMat);

			m_CityTex.bind();
			m_Shader.setUniform1i("tex", 0);
			m_Shader.setUniform1i("useTexture", m_UseTextures);

			GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));


			//set up for TSP
			//read in the contents of the tsp file
			ReadFile("res/TSP/test100.tsp");
			//init random
			srand((unsigned)time(NULL));

			//generates initial path
			gen_path(m_Path, static_cast<unsigned int>(m_Map.size()));
		
		}

	TSPScene::~TSPScene() {   } 

	void TSPScene::OnUpdate(float deltaTime) {

		m_TempPoints.push_back((tempFunc) ? tempFunc(m_Time) : 0.0f);
		if (m_TempPoints.size() > m_MaxPoints) {
			m_TempPoints.erase(m_TempPoints.begin());
		}

		m_FitPoints.push_back(fitness(m_Map, m_Path));

		m_Time += deltaTime;
		Anneal();
		
	}

	void TSPScene::OnRender() {

		float lineOffsetX = m_CitySize[0] / 2.0f;
		float lineOffsetY = m_CitySize[1] / 2.0f;

		//float[4](RGBA) -> unsigned int(ABGR)
		unsigned int CityColorU = F4toU32(m_CityColor);
		unsigned int PathColorU = F4toU32(m_PathColor);


		
		m_Renderer.begin();

		
		for (const auto& e : m_Map) {
			m_Renderer.fillRect(e.first, e.second, m_CitySize[0], m_CitySize[1], CityColorU);
		}

		for (int i = 1; i < m_Path.size(); ++i) {
			m_Renderer.line(m_Map[m_Path[i-1]].first + lineOffsetX, 
							m_Map[m_Path[i-1]].second + lineOffsetY, 
							m_Map[m_Path[i]].first + lineOffsetX,
							m_Map[m_Path[i]].second + lineOffsetY,
							PathColorU,
							m_PathThickness
			);
		}
		m_Renderer.line(m_Map[m_Path[m_Path.size() - 1]].first + lineOffsetX,
			m_Map[m_Path[m_Path.size()-1]].second + lineOffsetY,
			m_Map[m_Path[0]].first + lineOffsetX,
			m_Map[m_Path[0]].second + lineOffsetY,
			PathColorU,
			m_PathThickness
		);



		m_Renderer.end();

		m_Renderer.flush();


	}

	void TSPScene::OnImGuiRender() {

		static unsigned int tempIndex = 0;
		static const char* tempString[] = { 
			"sin( time / 2 ) + 1",
			"sin( time / 5 ) + 1",
			"sin( time / 5 ) * 100 + 100"
		};


		
		ImGui::Text("Elapsed Time: %f", m_Time);
		ImGui::Text("Current Temp: %f", (tempFunc) ? tempFunc(m_Time) : 0.0f);

		ImGui::NewLine();

		//ImGui::InputFloat2("City Size", m_CitySize);
		ImGui::DragFloat2("City Size", m_CitySize, 0.01f, 0.01f, 5.0f);
		ImGui::ColorEdit4("City Color", m_CityColor);

		ImGui::NewLine();

		ImGui::DragFloat("Path Thickness", &m_PathThickness, 0.01f, 0.01f, 3.0f);
		ImGui::ColorEdit4("Path Color", m_PathColor);
			
		ImGui::NewLine();

		if (ImGui::ColorEdit4("Clear Color", m_ClearColor)) {
			GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		}

		//ImGui::NewLine();

		//if (ImGui::Button("Restart")) Restart();

		//ImGui::SameLine();
		
		//if (ImGui::Checkbox("Use Textures", &m_UseTextures)) 
		//	m_Shader.setUniform1i("useTexture", m_UseTextures);

		//if (ImGui::Button("Restore Defaults")) RestoreDefaults();


		{   // Start Temp Graphing Window
			OpenGUIWindow("Temperature Graph");

			ImGui::PlotLines(
				"",                                    // Name of Graph
				m_TempPoints.data(),                   // points to plot
				static_cast<int>(m_TempPoints.size()), // amount of points in array
				0,                                     // values offset
				tempString[tempIndex],          // overlay text

													   // scale MIN
				//m_TempPoints.at((std::min_element(m_TempPoints.begin(),
				//	m_TempPoints.end()) - m_TempPoints.begin())),
				-0.1f,
				                                       // scale MAX
				m_TempPoints.at((std::max_element(m_TempPoints.begin(),
					m_TempPoints.end()) - m_TempPoints.begin())),
				//2.1f,

				ImVec2(250.0f, 150.0f),                // graph size in pixels
				4                                      // stride
			);

			if (ImGui::Button(tempString[0])) {
				tempIndex = 0;
				m_TempPoints.clear();
				tempFunc = temp1;
			}
			if (ImGui::Button(tempString[1])) {
				tempIndex = 1;
				m_TempPoints.clear();
				tempFunc = temp2;
			}
			if (ImGui::Button(tempString[2])) {
				tempIndex = 2;
				m_TempPoints.clear();
				tempFunc = temp3;
			}
			
				
		}  // End Temp Graphing window

		{  // Start Fitness Graphing Window
			OpenGUIWindow("Fitness Graph");

			ImGui::PlotLines(
				"",                                   // Name of Graph
				m_FitPoints.data(),                   // points to plot
				static_cast<int>(m_FitPoints.size()), // amount of points to plot
				0,                                    // values offset
				"Fitness / Time",                     // overlay text

				0.0f,                                 // scale min

				m_FitPoints.at(
					(std::max_element(m_FitPoints.begin(), m_FitPoints.end()) - m_FitPoints.begin())
				),                                    //scale max

				ImVec2(250.0f, 250.0f),               //graph size in pixels
				4                                     // stride
			);

		}  // End Fitness Graphing Window
			
	}

	void TSPScene::ReadFile(const char* filepath)
	{
		auto file = std::ifstream(filepath);
		if (!file.is_open()) {
			core::Log::printError("Unable to open TSP File!");
			FF_ASSERT(false);
			exit(EXIT_FAILURE);
		}

		float _1st = -1.0f;
		float _2nd = -1.0f;

		while (!file.eof()) {
			file >> _1st;
			file >> _2nd;
			m_Map.emplace_back(_1st, _2nd);
		}

	}

	void TSPScene::Anneal() {
		
		/*
		Simulated Annealing on TSP:
			Givens:
				- Graph Layout

			Step 1:
				- stocastically pick a path to take (*DONE*)
			Step 2:
				- get the fitness of that path (*DONE*)
			Step 3:
				- for i < MAX_ITERS (*DONE*)
					- Move to a neighboring state. (*DONE*)
					- get the new states fitness (*DONE*)
					- determine wether to move to the new state with some tempurature function (*DONE*)

		*/
		step(m_Path, m_NewPath);
		if (
			P(
				fitness(m_Map, m_Path), 
				fitness(m_Map, m_NewPath), 
				(tempFunc) ? tempFunc(m_Time) : 0.0f
			) >= ((float)rand() / (float)RAND_MAX)) 
		{
			/* Swap to avoid copies */
			m_Path.swap(m_NewPath);
		}
	}

	void TSPScene::RestoreDefaults()
	{
		m_CitySize[0] = 0.5f;
		m_CitySize[1] = 0.5f;

		m_PathThickness = 0.05f;

		m_CityColor[0] = 0.67f;
		m_CityColor[1] = 0.67f;
		m_CityColor[2] = 0.67f;
		m_CityColor[3] = 1.0f;

		m_PathColor[0] = 0.35f;
		m_PathColor[1] = 0.85f;
		m_PathColor[2] = 0.5f;
		m_PathColor[3] = 1.0f;

		m_ClearColor[0] = 0.0f;
		m_ClearColor[1] = 0.0f;
		m_ClearColor[2] = 0.0f;
		m_ClearColor[3] = 1.0f;

		m_MaxPoints = 8192;

		m_UseTextures = false;

		m_TempPoints.clear();
	}

	void TSPScene::Restart()
	{
		m_Time = 0.0f;
		m_Path.clear();
		m_NewPath.clear();
		m_TempPoints.clear();
		m_FitPoints.clear();
		gen_path(m_Path, static_cast<unsigned int>(m_Map.size()));
	}

} }

void gen_path(std::vector<unsigned int>& output, unsigned int mapSize)
{
	auto indecies = std::vector<unsigned int>();
	for (unsigned int i = 0; i < mapSize; ++i) {
		indecies.push_back(i);
	}

	int random = -1;
	while (!indecies.empty()) {
		random = rand() % indecies.size();
		output.push_back(indecies[random]);
		indecies.erase(indecies.begin() + random);
	}
}

float fitness(const std::vector<std::pair<float, float>>& map, const std::vector<unsigned int>& path)
{
	const std::pair<float, float>* lastPoint = &map[path[0]];
	float sum = 0.0f;

	for (unsigned int i = 1; i < path.size(); ++i) {
		sum += dist(lastPoint, &map[path[i]]);
		lastPoint = &map[path[i]];
	}

	sum += dist(lastPoint, &map[path[0]]); //don't forget to go back to the start

	return sum;
}

float dist(const std::pair<float, float>* from, const std::pair<float, float>* to)
{
	return sqrt(((to->first - from->first) * (to->first - from->first)) + 
		((to->second - from->second) * (to->second - from->second)));
}

void step(const std::vector<unsigned int>& src, std::vector<unsigned int>& dest)
{
	dest = src; //copy src to dest

	int _1st = rand() % src.size();
	int _2nd = rand() % (src.size() - _1st);

	if (_1st < _2nd)
		std::reverse(dest.begin() + _1st, dest.begin() + _2nd); //reverse the subsection of the dest vector to take the "step" 
	else 
		std::reverse(dest.begin() + _2nd, dest.begin() + _1st); 
}

float temp1(float currTime) {
	/* outputs a range of [0.0f, 2.0f] */
	return sin(currTime / 2.0f) + 1.0f;
}

float temp2(float currTime) {
	/* outputs a range of [0.0f, 2.0f] */
	return sin(currTime / 5.0f) + 1.0f;
}

float temp3(float currTime) {
	/* outputs a range of [0.0f, 200.0f] */
	return sin(currTime / 5.0f) * 100.0f + 100.0f;
}

float P(float s, float snew, float t)
{
	return (snew < s) ? 1.0f : exp(-(snew - s) / t);
}

unsigned int F4toU32(float rgba[4]) {

	unsigned int result = 0U;

	unsigned int r = static_cast<unsigned int>(rgba[0] * 255.0f);
	unsigned int g = static_cast<unsigned int>(rgba[1] * 255.0f);
	unsigned int b = static_cast<unsigned int>(rgba[2] * 255.0f);
	unsigned int a = static_cast<unsigned int>(rgba[3] * 255.0f);

	result = a << 24 | b << 16 | g << 8 | r << 0;

	return result;

}