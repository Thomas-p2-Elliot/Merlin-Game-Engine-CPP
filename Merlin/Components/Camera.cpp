#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"

namespace Merlin {

	//Constructor, sets gameobject, nearplane, and farplane through param values
	Camera::Camera(GameObject * gameObject, float nearPlane, float farPlane):Component(gameObject) {
		//Set near & far plane
		this->nearPlane = nearPlane; this->farPlane = farPlane;
		GLint viewport[4];
		// Get viewport dimensions
		glGetIntegerv(GL_VIEWPORT, viewport);
		int screenWidth = viewport[2];
		int screenHeight = viewport[3];
		float aspectRatio = screenWidth / (float)screenHeight;
		//Need to review this in future versions
		this->viewDirection = glm::vec3(0.0, 0.0, 0.0);
		//Up is fixed for camera
		this->up = glm::vec3(0, 1, 0);
	}

	//Destructor, does nothing
	Camera::~Camera(void){ }

	//Runs each frame
	void Camera::Update() {
		//Get position from transform
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		// Convert the position to a vector with 4 components for matrix multiplication
		glm::vec4 cameraPosition(position, 0.0);
		// Apply rotations to determine actual camera position
		cameraPosition = rotationMatrix * rollMatrix * cameraPosition;
	}

	void Camera::Yaw(float value) {
		cameraYaw -= value;
		if (cameraYaw < 0) cameraYaw += 360;
		if (cameraYaw >= 360) cameraYaw -= 360;
		float yaw = glm::radians(cameraYaw);
		rotationMatrix = glm::rotate(glm::mat4x4(), yaw, up);
	}

	void Camera::Pitch(float value) {
		cameraPitch -= value;
		if (cameraPitch < 0) cameraPitch += 360;
		if (cameraPitch >= 360) cameraPitch -= 360;
		float pitch = glm::radians(cameraPitch);
		// Get camera's poition through the transform component
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		glm::vec3 forward = position;
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		rollMatrix = glm::rotate(glm::mat4x4(), -pitch, right);
	}

	void Camera::Zoom(float value) {
		// Get camera's poition through the transform component
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		position.z += value;
		// Update transform
		gameObject->GetTransform()->SetPosition(position);
	}

	glm::mat4x4 Camera::GetViewMatrix(){
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		// Convert the position to a vector with 4 components for matrix multiplication
		glm::vec4 cameraPosition(position, 0.0);
		// Apply rotations to determine actual camera position
		cameraPosition = rotationMatrix * rollMatrix * cameraPosition;
		return glm::lookAt(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z), viewDirection, up);
	}
	
	//Far/Near plane getters
	float Camera::GetNearPlane(){ return nearPlane;	}
	float Camera::GetFarPlane() { return farPlane; }
}
			