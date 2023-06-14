#include "Camera.h"
#include <SDL.h>
#include <iostream>

Camera::Camera()
{
	projectionMatrix = Matrix4();
	viewMatrix = Matrix4();
	/*std::cout << "Camera is On!" << std::endl;
	trackball = new Trackball();
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	rotationMatrix = MMath::rotate(0.0f, (const Vec3(0.0f, 1.0f, 0.0f)));
	translationMatrix = MMath::translate((const Vec3(0.0f, 0.0f, -10.0f)));
	viewMatrix = rotationMatrix * translationMatrix;
	translationMatrix.print("Translation");
	rotationMatrix.print("Rotation");*/
}

Camera::~Camera()
{
}

void Camera::HandleEvents(const SDL_Event& sdlEvent)
{

}


bool Camera::OnCreate()
{	
	return true;
}

void Camera::OnDestroy()
{

}


void Camera::SetProjectionMatrix(float fovy, float near, float far)
{
	// float width, height, aspectRatio,
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float width = static_cast<float>(viewport[2]);
	float height = static_cast<float>(viewport[3]);
	float aspectRatio = width / height;
	projectionMatrix = MMath::perspective(fovy, aspectRatio, near, far);
}

void Camera::LookAt(const Vec3& eye, const Vec3& at, const Vec3& up)
{
	viewMatrix = MMath::lookAt(eye, at, up);
}




void Camera::Render() const
{
	/*if (!skybox) return;
	glUseProgram(skybox->GetShader()->GetProgram());
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("rotationMatrix"), 1, GL_FALSE, Matrix4());
	skybox->Render();
	glUseProgram(0);*/
}

