#include "CameraSkybox.h"
#include <SDL.h>
#include <iostream>

CameraSkybox::CameraSkybox()
{
	projectionMatrix = Matrix4();
	viewMatrix = Matrix4();
	camTrackball = new Trackball();
}

CameraSkybox::~CameraSkybox()
{
	if (camTrackball) delete camTrackball;
}


bool CameraSkybox::OnCreate()
{	
	skybox = new Skybox("textures/CN_Tower/posx.jpg", "textures/CN_Tower/posy.jpg", "textures/CN_Tower/posz.jpg",
		"textures/CN_Tower/negx.jpg", "textures/CN_Tower/negy.jpg", "textures/CN_Tower/negz.jpg");
	return skybox->OnCreate();
}

void CameraSkybox::OnDestroy()
{
	skybox->OnDestroy();
	delete skybox;
}


void CameraSkybox::SetProjectionMatrix(float fovy, float near, float far)
{
	// float width, height, aspectRatio,
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float width = static_cast<float>(viewport[2]);
	float height = static_cast<float>(viewport[3]);
	float aspectRatio = width / height;
	projectionMatrix = MMath::perspective(fovy, aspectRatio, near, far);
}


void CameraSkybox::LookAt(const Vec3& eye, const Vec3& at, const Vec3& up)
{
	viewMatrix = MMath::lookAt(eye, at, up);
}


void CameraSkybox::HandleEvents(const SDL_Event& sdlEvent)
{
	camTrackball->HandleEvents(sdlEvent);
	skyboxViewMatrix = camTrackball->getMatrix4();
	//viewMatrix *= rotationMatrix;
}


void CameraSkybox::Render() const
{
	if (!skybox) return;

	glUseProgram(skybox->GetShader()->GetProgram());
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("skyboxViewMatrix"), 1, GL_FALSE, skyboxViewMatrix); // viewmatrix changed to rotation matrix for 

	skybox->Render();

	glUseProgram(0);
}

