#include "stdafx.h"
#include "Graphics.h"
#include "Camera.h"

namespace Merlin {
	int Graphics::DEFAULT_WINDOW_WIDTH  = 1280;
	int Graphics::DEFAULT_WINDOW_HEIGHT = 720;
	
	glm::mat4 Graphics::projectionMatrix;
	Camera* Graphics::mainCamera = 0;
	Light* Graphics::mainLight = 0;

	void Graphics::SetMainCamera(Camera* camera){
		//Set main camera
		Graphics::mainCamera = camera;
		//Get aspect ratio
		float aspectRatio = Graphics::DEFAULT_WINDOW_WIDTH / (float) Graphics::DEFAULT_WINDOW_HEIGHT;

		//Set projection matrix with cliping planes & aspect ratio
		projectionMatrix = (
			glm::frustum(
				-aspectRatio * camera->GetNearPlane(),
				aspectRatio * camera->GetNearPlane(),
				-camera->GetNearPlane(),
				camera->GetNearPlane(), 
				camera->GetNearPlane(),
				camera->GetFarPlane()
			)
		);

		//OpenGL requires knowledge of the viewing volume for clipping
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//left, right, bottom, top, near, far
		glFrustum(-aspectRatio * camera->GetNearPlane(), aspectRatio * camera->GetNearPlane(), -camera->GetNearPlane(), camera->GetNearPlane(), camera->GetNearPlane(), camera->GetFarPlane());
	}

}

