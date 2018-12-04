#include "ParticleSystem2D.h"
#include <cstdlib>

namespace core { namespace particles {

	namespace SpawnDefaults {
		Particle2D* DoNothing(const glm::vec3& spawnPoint) // creates a particle at the exact emitter position with 0 vectors for pos, vel, and acc
		{
			return new Particle2D(spawnPoint,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f));
		}

		Particle2D* UpShower(const glm::vec3& spawnPoint)
			// creates a particle at the exact emitter position 
			// with a 0 vector for acc, and a initial vel of 
			// 10 in the positive Y axis with small bounded angle to either positive or negative X and Z
		{
			return new Particle2D(spawnPoint,
				glm::vec3((((float)rand() / (float)RAND_MAX) - 0.5f) * 2, 5.0f, 0.0f),
				glm::vec3(0.0f, -5.0f, 0.0f));
		}
	}

	namespace MotionIntegrators {
		
		// cheapest compute cost, least accurate integrator
		void ModifiedEuler(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, float delta)
		{
			vel += acc * delta;
			pos += vel * delta;
		}

		// less expensive than ForestRuth but not as accurate
		void Verlet(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, float delta)
		{
			float halfDelta = delta * 0.5;
			pos += vel * halfDelta;
			vel += acc * delta;
			pos += vel * halfDelta;
		}

		// expensive to compute, but very accurate
		void ForestRuth(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, float delta)
		{
			static const float frCoef = 1.0 / (2.0 - pow(2.0, 1.0 / 3.0));
			static const float frComp = 1.0 - 2.0 * frCoef;

			Verlet(pos, vel, acc, delta * frCoef);
			Verlet(pos, vel, acc, delta * frComp);
			Verlet(pos, vel, acc, delta * frCoef);

		}

	}

	ParticleSystem2D::ParticleSystem2D()
		: position(0.0f, 0.0f, 0.0f), spawnRate(10.0f), lifeSpan(5.0f), spawn(core::particles::SpawnDefaults::UpShower)
	{
	}

	ParticleSystem2D::ParticleSystem2D(const glm::vec3& ppos, const glm::vec3& pgravity, float pspawnRate, float plifeSpan, std::function<Particle2D*(const glm::vec3&)>&& spawnLambda, std::function<void(Particle2D*, float)> updateLambda)
		: position(ppos), gravity(pgravity), spawnRate(pspawnRate), lifeSpan(plifeSpan), spawn(spawnLambda), update(updateLambda)
	{
	}

	ParticleSystem2D::~ParticleSystem2D()
	{
	}

	void ParticleSystem2D::Create(float deltaTime)
	{
		static float spawnCnt = 0;
		spawnCnt += spawnRate * deltaTime; //add the particles that should have spawned since the last spawn tick
		while (spawnCnt >= 1.0f) {
			particles.push_back(spawn(position));
			spawnCnt -= 1.0f;
		}

	}

	void ParticleSystem2D::Update(float deltaTime)
	{
		for (int i = 0; i < particles.size(); ++i) {
			update(particles[i], deltaTime);
			MotionIntegrators::ModifiedEuler(particles[i]->position,
											 particles[i]->velocity, 
											 particles[i]->acceleration + gravity, 
											 deltaTime);
			particles[i]->age += deltaTime;
			if (particles[i]->age >= lifeSpan) {
				delete particles[i]; //delete the contents of the pointer
				particles.erase(particles.begin() + i); //remove this particle if its too old
				i--; //because you removed a particle, the next particle is now at this same location
			}
		}
	}

	void ParticleSystem2D::Submit(core::graphics::Renderer2D& renderer)
	{
		for (auto& particle : particles) {
			renderer.submit(particle);
		}
	}

} }