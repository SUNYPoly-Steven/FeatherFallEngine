#pragma once
#include "glm/gtx/transform.hpp"


namespace core { namespace graphics {

	class Camera {
	private:

		glm::mat4 projMat;
		glm::mat4 viewMat;
		float viewWidth, viewHeight;
		float aspectRatio;
		float nearPlane, farPlane;


	public:
		float fov; //feild of view
		glm::vec3 eye; //the point in space the camera is
		glm::vec3 lookAt; // the point vector the camera is looking in
		glm::vec3 up; //the point vector above the camera

		Camera(const glm::vec3& peye, const glm::vec3& plookAt, 
			const glm::vec3& pup, const float& pfov, const float& pnearPlane,
			const float& pfarPlane, const float& pveiwWidth, const float& pviewHeight);
		~Camera();

		void updateBufferSize(float width, float height);
		const glm::mat4& getViewMatrix() const ;
		const glm::mat4& getProjectionMatrix() const ;
		void rotateRight(float angle);
		void rotateUp(float angle);
		void forward(float dist);
		void strafeRight(float dist);

		glm::mat4& computeProjMat();
		glm::mat4& computeViewMat();

	private:


	};

} }