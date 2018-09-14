#include "Boid.h"
#include <glm/vec2.hpp>
#include <stdlib.h>
#include "../Scene/BoidScene.h"

namespace Application { namespace Boid {
	
	Boid::Boid(float px, float py, const glm::vec4& pcolor) 
		: Renderable2D(
			glm::vec4(px, py, 0.0f, 1.0f),
			glm::vec2(0.1f, 0.1f), 
			pcolor
		  ), direction(glm::vec2(0.01f, 0.0f))

	{
	}

	Boid::~Boid() {

	}

	void Boid::updatePos() {

		//find the new direction to move in
		//glm::vec2 acc = glm::vec2(((rand() % 1000) / 10000.0f) - 0.05f, ((rand() % 1000) / 10000.0f) - 0.05f);
		//direction += acc;
		//direction /= glm::length(direction) * 10;

		//add that move vector to the current position
		position.x += direction.x;
		position.y += direction.y;

		//check for out of bounds collitions
		if (position.x > 8.0f) position.x = -8.0f;
		if (position.x < -8.0f) position.x = 8.0f;
		if (position.y > 4.5f) position.y = -4.5f;
		if (position.y < -4.5f) position.y = 4.5f;
	}

	void Boid::updateFlockMates(const std::vector<Boid*>& boids) {

		flockMates.clear();

		for (int i = 0; i < boids.size(); ++i) {
			if (boids[i] == this) {
				continue; //dont add yourself to flockmates
			}
			if (inRadius(boids[i])) {
				//if the boid is in the radius, that boid is a flockmate
				flockMates.push_back(boids[i]);
			}

		}

	}

	void Boid::updateSteer() {

		glm::vec3 output = glm::vec3(0.0f, 0.0f, 0.0f);

		//RULE Separation
		glm::vec3 sep = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < flockMates.size(); ++i) {
			float dist = glm::length(flockMates[i]->position - position);
				if (dist < CROWD_DIST) {
					glm::vec3 diff = flockMates[i]->position - position;
					diff /= glm::length(diff);
					diff /= dist; //weight
					sep += diff;
				}
		}
		//sep /= glm::length(sep) * 10; //do i want this normalized??
		sep *= -1;

		//RULE Alignment
		glm::vec3 ali = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < flockMates.size(); ++i) {
			ali += glm::vec3(flockMates[i]->direction.x, flockMates[i]->direction.y, 0.0f);
			ali /= glm::length(ali);
		}
		//ali /= glm::length(ali) * 10;

		//RULE Cohesion
		glm::vec4 coh = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		for (int i = 0; i < flockMates.size(); ++i) {
			coh += flockMates[i]->position;
		}
		coh /= flockMates.size();
		coh = coh - position;
		coh /= glm::length(coh) * 10;

		//RULE Mouse Tracking
		glm::vec3 mtk = glm::vec3(0.0f, 0.0f, 0.0f);
		mtk = glm::vec4(Scene::BoidScene::trackPos.x, Scene::BoidScene::trackPos.y, 0.0f, 1.0f) - position;
		mtk /= glm::length(mtk) * 0.1f;

		//RULE Obstacle Avoidance
		//NOTE: for now, the obstacles are just going to be the walls
		glm::vec3 avo = glm::vec3(0.0f, 0.0f, 0.0f);
		avo.x = (-4.5f - position.x) + (4.5f - position.x);
		avo.y = (-8.0f - position.y) + (8.0f - position.y);
		avo /= glm::length(avo) * 10;




		if (Scene::BoidScene::doSeparation)    direction += glm::vec2(sep.x, sep.y);
		if (Scene::BoidScene::doAlignment)     direction += glm::vec2(ali.x, ali.y);
		if (Scene::BoidScene::doCohesion)      direction += glm::vec2(coh.x, coh.y);

		//add Noise
		if (Scene::BoidScene::doNoise)         direction += glm::vec2((rand() % 1000 / 1000.0f) - 0.5f, (rand() % 1000 / 1000.0f) - 0.5f);

		//add Mouse Tracking
		if (Scene::BoidScene::doMouseTracking) direction += glm::vec2(mtk.x, mtk.y);
		if (Scene::BoidScene::doAvoid)         direction += glm::vec2(avo.x, avo.y);

		direction /= glm::length(direction) * 10;

	}

	bool Boid::inRadius(const Boid* boid) const {
		float xcheck = (boid->position.x - this->position.x) * (boid->position.x - this->position.x);
		float ycheck = (boid->position.y - this->position.y) * (boid->position.y - this->position.y);
		float radius = FLOCK_RADIUS * FLOCK_RADIUS;

		//euclidian dist x^2 + y^2 = z^2 to check for point in circle
		return (xcheck + ycheck < radius);
	}

} }