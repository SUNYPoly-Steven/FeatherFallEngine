#pragma once
#include "glm/glm.hpp"                   //
#include "glm/vec3.hpp"                  // NOTE:
#include "glm/mat4x4.hpp"                //    not all of these need to be here,
#include "glm/matrix.hpp"                //    sort through them later!
#include "glm/trigonometric.hpp"         //    
#include "glm/gtc/matrix_transform.hpp"  //    also, move the ones you need but not
#include "glm/gtx/transform.hpp"         //    in the .h into Camera.cpp
#include "glm/gtc/type_ptr.hpp"          //

namespace core { namespace graphics {

	class Camera {
	private:

		glm::mat4 projMat;
		glm::mat4 viewMat;
		float viewWidth, viewHeight;
		float aspectRatio;
		float fov; //feild of view
		float nearPlane, farPlane;


	public:
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


	private:

		glm::mat4& computeProjMat();
		glm::mat4& computeViewMat();

	};

} }