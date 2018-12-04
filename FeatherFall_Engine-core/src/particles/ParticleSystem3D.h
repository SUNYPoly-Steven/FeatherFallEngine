#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include <functional>
#include "../FeatherFall-graphics.h"
#include "../mesh/Mesh.h"
#include "ParticleSystem2D.h"


namespace core { namespace particles {

	struct Particle3D : public core::graphics::Renderable3D {
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float age; //age of the particle (calculated through delta time)

		Particle3D(const glm::vec3& ppos, const glm::vec3& pvel, const glm::vec3& pacc, float page = 0.0f)
			: Renderable3D("res/models/custom-feather.fbx"),
			position(ppos),
			velocity(pvel),
			acceleration(pacc),
			age(page)
		{
			m_mlMatrix = glm::translate(glm::mat4(1.0f), position);
		}
	};

	namespace SpawnDefaults3D {
		// creates a particle at the exact emitter position
		// with 0 vectors for pos, vel, and acc
		Particle3D* DoNothing(const glm::vec3& spawnPoint);


		// creates a particle at the exact emitter position 
		// with a 0 vector for acc, and a initial vel of 
		// 10 in the positive Y axis with small bounded angle to either positive or negative X and Z
		Particle3D* UpShower(const glm::vec3& spawnPoint);
	}

	class ParticleSystem3D
	{
	private:


		glm::vec3 position; // position of emitter
		glm::vec3 gravity;  // the gravity effecting the particles of this emitter
		float lifeSpan;     // the lifespan of the particles this system produces
		float spawnRate;    // the amount of particles per second to spawn
		std::function<Particle3D*(const glm::vec3&)> spawn; // function to dictate how particles are spawned from the emitter
		std::function<void(Particle3D*, float)> update;     // function to update the particles over their lifetime (this is called every frame and is give the deltaTime between each call)


		std::vector<Particle3D*> particles; // the particles currently alive in the system

	public:

		ParticleSystem3D();
		ParticleSystem3D(const glm::vec3& ppos, const glm::vec3& pgravity, float pspawnRate, float plifeSpan, std::function<Particle3D*(const glm::vec3&)>&& spawnLambda, std::function<void(Particle3D*, float)> updateLambda);

		~ParticleSystem3D();

		void Create(float deltaTime);
		void Update(float deltaTime);

		void Submit(core::graphics::Renderer3D& renderer);


	private:



	};

} }