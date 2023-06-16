#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene4g.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"

Scene4g::Scene4g() :
	/*sphereShader{nullptr},
	sphereMesh{nullptr},*/
	drawInWireMode{false}
{
	Debug::Info("Created Scene4g: ", __FILE__, __LINE__);
}

Scene4g::~Scene4g() {
	Debug::Info("Deleted Scene4g: ", __FILE__, __LINE__);
}

bool Scene4g::OnCreate() {
	Debug::Info("Loading assets Scene4g: ", __FILE__, __LINE__);

	cameraSkybox = new CameraSkybox;
	cameraSkybox->OnCreate();

	/*sphere = new Body();
	sphere->OnCreate();
	
	sphereMesh = new Mesh("meshes/Sphere.obj");
	sphereMesh->OnCreate();

	sphereShader = new Shader("shaders/phongTextureVert.glsl", "shaders/phongTextureFrag.glsl");
	if (sphereShader->OnCreate() == false) {
		std::cout << "Sphere Shader failed ... we have a problem\n";
	}*/

	//projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print("View");

	cameraSkybox->SetProjectionMatrix(45.0f, 0.5f, 100.0f);
	cameraSkybox->LookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	//sphereModelMatrix = MMath::translate(Vec3(0.0f, 0.0f, 0.0f));

	//lightPos = Vec3(0.0f, 4.0f, 3.0f);
	return true;
}

void Scene4g::OnDestroy() {
	Debug::Info("Deleting assets Scene4g: ", __FILE__, __LINE__);
	/*sphere->OnDestroy();
	delete sphere;

	sphereMesh->OnDestroy();
	delete sphereMesh;

	sphereShader->OnDestroy();
	delete sphereShader;*/
	
}

void Scene4g::HandleEvents(const SDL_Event &sdlEvent) {
	
	cameraSkybox->HandleEvents(sdlEvent);

	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_W:
				drawInWireMode = !drawInWireMode;
				break;
		}
		break;

	case SDL_MOUSEMOTION:          
		break;

	case SDL_MOUSEBUTTONDOWN:              
		break; 

	case SDL_MOUSEBUTTONUP:            
	break;

	default:
		break;
    }
}

void Scene4g::Update(const float deltaTime) {

}

void Scene4g::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.694f, 0.251f, 1.0f);glClearColor(0.0f, 0.694f, 0.251f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(drawInWireMode){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	cameraSkybox->Render();

	// Global Render Data
	/*glUseProgram(sphereShader->GetProgram());
	glUniformMatrix4fv(sphereShader->GetUniformID("projectionMatrix"), 1, GL_FALSE, cameraSkybox->GetProjectionMatrix());
	glUniformMatrix4fv(sphereShader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);*/
	//glUniform3fv(sphereShader->GetUniformID("lightPos"), 1, lightPos);

	// Sphere Render Data
	//glBindTexture(GL_TEXTURE_2D, sphereTexture->getTextureID());
	/*glUniformMatrix4fv(sphereShader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphereModelMatrix);
	sphereMesh->Render(GL_TRIANGLES);*/
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glUseProgram(0);
}



	
