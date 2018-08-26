#include "Camera.h"

namespace core { namespace graphics {

	Camera::Camera(const glm::vec3& peye, const glm::vec3& plookAt,
		const glm::vec3& pup, const float& pfov, const float& pnearPlane,
		const float& pfarPlane, const float& pviewWidth, const float& pviewHeight)
		: eye(peye), lookAt(plookAt), up(pup), fov(pfov), nearPlane(pnearPlane),
		farPlane(pfarPlane), viewWidth(pviewWidth), viewHeight(pviewHeight)
	{
		aspectRatio = viewWidth / viewHeight;
		computeProjMat();
		computeViewMat();
	}

	Camera::~Camera() 
	{

	}

	void Camera::updateBufferSize(float width, float height)
	{
		viewWidth = width;
		viewHeight = height;
		computeProjMat();
	}

	const glm::mat4& Camera::getViewMatrix() const 
	{
		return viewMat;
	}

	const glm::mat4& Camera::getProjectionMatrix() const
	{
		return projMat;
	}

	void Camera::rotateRight(float angle) 
	{
		glm::vec4 temp = glm::vec4(lookAt, 1.0f);
		glm::mat4 T = glm::translate(eye);
		glm::mat4 R = glm::rotate(angle, up);


		lookAt = glm::vec3(T * R * glm::inverse(T) * temp);
		computeViewMat();
	}

	void Camera::rotateUp(float angle) 
	{
		glm::vec4 temp = glm::vec4(lookAt, 1.0f);
		glm::vec3 forward = lookAt - eye;
		glm::vec3 right = glm::normalize(glm::cross(forward, up));
		glm::mat4 R = glm::rotate(angle, right);
		glm::mat4 T = glm::translate(eye);


		lookAt = glm::vec3(T * R * glm::inverse(T) * temp);
		computeViewMat();
	}

	void Camera::forward(float dist) 
	{
		glm::vec3 forward = dist * glm::normalize(lookAt - eye);
		eye = eye + forward;
		lookAt = lookAt + forward;
		computeViewMat();
	}

	void Camera::strafeRight(float dist)
	{
		glm::vec3 forward = lookAt - eye;
		glm::vec3 right = dist * glm::normalize(glm::cross(forward, up));

		eye = eye + right;
		lookAt = lookAt + right;
		computeViewMat();
	}


	glm::mat4& Camera::computeProjMat() 
	{
		projMat = glm::perspective(fov, (viewWidth / viewHeight), nearPlane, farPlane);
		return projMat;
	}

	glm::mat4& Camera::computeViewMat() 
	{
		viewMat = glm::lookAt(eye, lookAt, up);
		return viewMat;
	}

} }