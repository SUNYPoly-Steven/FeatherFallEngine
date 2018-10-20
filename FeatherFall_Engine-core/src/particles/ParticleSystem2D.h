#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include <functional>
#include "../FeatherFall-graphics.h"

namespace core { namespace particles {

	struct Particle2D : public core::graphics::Renderable2D {
		//glm::vec3 position;  //taken care of by base class
		glm::vec3 velocity;
		glm::vec3 acceleration; 
		float age; //age of the particle (calculated through delta time)

		Particle2D(const glm::vec3& ppos, const glm::vec3& pvel, const glm::vec3& pacc, float page = 0.0f)
			: Renderable2D(glm::vec4(ppos, 1.0f), glm::vec2(0.5f, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), velocity(pvel), acceleration(pacc), age(page)
		{
		}
	};

	namespace MotionIntegrators {
		void ForestRuth(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, float delta);
		void ModifiedEuler(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, float delta);
	}

	namespace SpawnDefaults {
		// creates a particle at the exact emitter position
		// with 0 vectors for pos, vel, and acc
		Particle2D* DoNothing(const glm::vec3& spawnPoint);


		// creates a particle at the exact emitter position 
		// with a 0 vector for acc, and a initial vel of 
		// 10 in the positive Y axis with small bounded angle to either positive or negative X and Z
		Particle2D* UpShower(const glm::vec3& spawnPoint);
	}


	/*
	 * NOTE: 
	 *	Each particle system instance will be its own emitter
	 *	and as such will have its own position in 3D space 
	 */
	class ParticleSystem2D {
	private:

		glm::vec3 position; // position of emitter
		float lifeSpan; // the lifespan of the particles this system produces
		float spawnRate; // the amount of particles per second to spawn
		std::function<Particle2D*(const glm::vec3&)> spawn; //function to dictate how particles are spawned from the emitter


		std::vector<Particle2D*> particles; // the particles currently alive in the system

	public:

		ParticleSystem2D();
		ParticleSystem2D(const glm::vec3& ppos, float pspawnRate, float plifeSpan, std::function<Particle2D*(const glm::vec3&)>&& lambda);

		~ParticleSystem2D();

		void Create(float deltaTime);
		void Update(float deltaTime);

		void Submit(core::graphics::Renderer2D& renderer);


	private:



	};

} }