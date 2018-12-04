#include "ParticleSystem3D.h"

namespace core { namespace particles {


	namespace SpawnDefaults3D {
		Particle3D* DoNothing(const glm::vec3& spawnPoint) // creates a particle at the exact emitter position with 0 vectors for pos, vel, and acc
		{
			return new Particle3D(spawnPoint,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f));
		}

		Particle3D* UpShower(const glm::vec3& spawnPoint)
			// creates a particle at the exact emitter position 
			// with a 0 vector for acc, and a initial vel of 
			// 10 in the positive Y axis with small bounded angle to either positive or negative X and Z
		{
			return new Particle3D(spawnPoint,
				glm::vec3((((float)rand() / (float)RAND_MAX) - 0.5f) * 2, 5.0f, 0.0f),
				glm::vec3(0.0f, -5.0f, 0.0f));
		}
	}

	ParticleSystem3D::ParticleSystem3D()
		: position(0.0f, 0.0f, 0.0f), spawnRate(10.0f), lifeSpan(5.0f), spawn(core::particles::SpawnDefaults3D::UpShower)
	{
	}


	ParticleSystem3D::ParticleSystem3D(const glm::vec3& ppos, const glm::vec3& pgravity, float pspawnRate, float plifeSpan, std::function<Particle3D*(const glm::vec3&)>&& spawnLambda, std::function<void(Particle3D*, float)> updateLambda)
		: position(ppos), gravity(pgravity), spawnRate(pspawnRate), lifeSpan(plifeSpan), spawn(spawnLambda), update(updateLambda)
	{
	}


	ParticleSystem3D::~ParticleSystem3D()
	{
	}

	void ParticleSystem3D::Create(float deltaTime)
	{
		static float spawnCnt = 0;
		spawnCnt += spawnRate * deltaTime; //add the particles that should have spawned since the last spawn tick
		while (spawnCnt >= 1.0f) {
			particles.push_back(spawn(position));
			spawnCnt -= 1.0f;
		}
	}

	void ParticleSystem3D::Update(float deltaTime)
	{
		for (int i = 0; i < particles.size(); ++i) {
			MotionIntegrators::ModifiedEuler(particles[i]->position,
				particles[i]->velocity,
				particles[i]->acceleration + gravity,
				deltaTime);

			// update modelMat
			particles[i]->m_mlMatrix = glm::translate(
				glm::mat4(1.0f),
				particles[i]->position
			);
			update(particles[i], deltaTime);

			particles[i]->age += deltaTime;
			if (particles[i]->age >= lifeSpan) {
				delete particles[i]; //delete the contents of the pointer
				particles.erase(particles.begin() + i); //remove this particle if its too old
				i--; //because you removed a particle, the next particle is now at this same location
			}
		}
	}

	void ParticleSystem3D::Submit(core::graphics::Renderer3D& renderer)
	{
		for (auto& particle : particles) {
			renderer.submit(particle);
		}
	}

} }
