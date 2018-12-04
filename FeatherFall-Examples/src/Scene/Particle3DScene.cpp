#include "Particle3DScene.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "math (depricated)/misc_math.h"
#include <ctime>

namespace Application { namespace Scene {

	Particle3DScene::Particle3DScene()
		: m_Renderer(new core::graphics::Shader("res/shaders/Renderer3DTest.shader"),
			new core::graphics::Camera(glm::vec3(4.0f, 2.0f, 5.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				core::math::toRads(100.0f),
				0.1f,
				100.0f,
				16.0f,
				9.0f))
	{

		srand((unsigned)time(NULL));

		auto spawnLambda = [](const glm::vec3& spawnPoint)->core::particles::Particle3D* {
			return new core::particles::Particle3D(
				spawnPoint,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f)
			);
		};
		auto updateLambda = [](core::particles::Particle3D* particle, float deltaTime) {
			particle->m_mlMatrix *= glm::rotate(
				deltaTime,
				glm::vec3(0.0f, 1.0f, 0.0f)
			);
		};

		auto FeatherRainEffectSpawnLambda3D = [](const glm::vec3& spawnPoint) -> core::particles::Particle3D* {
			return new core::particles::Particle3D(
				spawnPoint + glm::vec3(
					(((float)rand() / (float)RAND_MAX) * 32.0f) - 16.0f,
					0.0f,
					(((float)rand() / (float)RAND_MAX) * 32.0f) - 16.0f
				),                               // pos
				glm::vec3(0.0f, 0.0f, 0.0f),     // vel
				glm::vec3(0.0f, 0.0f, 0.0f)      // acc
												 // age = 0.0f
			);
		};

		auto FeatherRainEffectUpdateLambda3D = [](core::particles::Particle3D* particle, float deltaTime) {

			auto dampedSin = [](float t) {
				return sin(4 * t);
			};


			auto Cd = 1.0f; // coefficient of drag
			auto airDensity = 1.0f;
			auto vel = particle->velocity;
			auto area = 1.0f;

			auto drag = Cd * (airDensity * (vel * vel) / 2.0f) * area;
			glm::vec3 swing = glm::vec3(dampedSin(particle->age), 0.0f, 0.0f);
			auto newAcc = drag + swing;
			particle->acceleration = newAcc; //update acc
			auto angle = glm::angle(glm::normalize(newAcc), glm::vec3(0.0f, 1.0f, 0.0f));
			particle->m_mlMatrix *= glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f));
			particle->m_mlMatrix *= glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			particle->m_mlMatrix *= glm::rotate(particle->age * 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			particle->m_mlMatrix *= glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
		};


		system = new core::particles::ParticleSystem3D(
			glm::vec3(0.0f, 5.5f, 0.0f),
			glm::vec3(0.0f, -15.0f, 0.0f),
			10.0f,
			5.0f,
			//spawnLambda,
			FeatherRainEffectSpawnLambda3D,
			//updateLambda
			FeatherRainEffectUpdateLambda3D
		);

		m_Renderer.m_Shader->bind();
		m_Renderer.m_Shader->setUniformMat4("projMat", m_Renderer.m_Camera->getProjectionMatrix());
		m_Renderer.m_Shader->setUniformMat4("viewMat", m_Renderer.m_Camera->getViewMatrix());


		m_Renderer.m_Shader->setUniformVec3("light.pos", glm::vec3(2.0f, 2.0f, 2.0f));
		m_Renderer.m_Shader->setUniformVec3("light.color", glm::vec3(1.0f, 1.0f, 1.0f));

		m_Renderer.m_Shader->setUniformVec3("material.kd", glm::vec3(1.0f, 0.5f, 1.0f));
		m_Renderer.m_Shader->setUniformVec3("material.ks", glm::vec3(1.0f, 0.5f, 0.5f));
		m_Renderer.m_Shader->setUniform1f("material.shininess", 0.5f);

		//set background to Grey
		GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));
	}

	Particle3DScene::~Particle3DScene()
	{
		delete system;
	}

	void Particle3DScene::OnUpdate(float deltaTime)
	{
		system->Create(deltaTime);
		system->Update(deltaTime);
	}

	void Particle3DScene::OnRender()
	{
		m_Renderer.begin();

		system->Submit(m_Renderer);

		m_Renderer.end();
		m_Renderer.flush();
	}

	void Particle3DScene::OnImGuiRender()
	{
	}

} }