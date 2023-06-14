#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene2ga.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"

Scene2ga::Scene2ga() :
	sphere{nullptr}, 
	shader{nullptr},
	meshSkull{nullptr},
	textureSkull{nullptr},
	drawInWireMode{false} 
{
	Debug::Info("Created Scene2ga: ", __FILE__, __LINE__);
}

Scene2ga::~Scene2ga() {
	Debug::Info("Deleted Scene2ga: ", __FILE__, __LINE__);
}

bool Scene2ga::OnCreate() {
	Debug::Info("Loading assets Scene2ga: ", __FILE__, __LINE__);
	skull = new Body();
	skull->OnCreate();
	
	meshSkull = new Mesh("meshes/Skull.obj");
	meshSkull->OnCreate();

	eyeL = new Body();
	eyeL->OnCreate();

	eyeR = new Body();
	eyeR->OnCreate();

	meshEye = new Mesh("meshes/Sphere.obj");
	meshEye->OnCreate();

	shader = new Shader("shaders/phongTextureVert.glsl", "shaders/phongTextureFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	textureSkull = new Texture();
	textureSkull->LoadImage("textures/skull_texture.jpg");

	textureEye = new Texture();
	textureEye->LoadImage("textures/evilEye.jpg");

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print("View");
	modelMatrixSkull = MMath::translate(Vec3(0.0f, 0.0f, 0.0f));
	modelMatrixEyeL = modelMatrixSkull *	MMath::translate(Vec3(0.6f, 0.3f, 0.6f)) * 										
											MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) *
											MMath::scale(Vec3(0.35f, 0.35f, 0.35f));

	modelMatrixEyeR = modelMatrixSkull *	MMath::translate(Vec3(-0.6f, 0.3f, 0.6f)) *
											MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) *
											MMath::scale(Vec3(0.35f, 0.35f, 0.35f));

	lightPos = Vec3(0.0f, 4.0f, 3.0f);
	return true;
}

void Scene2ga::OnDestroy() {
	Debug::Info("Deleting assets Scene2ga: ", __FILE__, __LINE__);
	skull->OnDestroy();
	delete skull;

	eyeL->OnDestroy();
	delete eyeL;

	eyeR->OnDestroy();
	delete eyeR;

	meshSkull->OnDestroy();
	delete meshSkull;

	meshEye->OnDestroy();
	delete meshEye;

	shader->OnDestroy();
	delete shader;

	delete textureSkull;
	delete textureEye;
	
}

void Scene2ga::HandleEvents(const SDL_Event &sdlEvent) {
	
	trackball.HandleEvents(sdlEvent);
	modelMatrixSkull = trackball.getMatrix4();

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

void Scene2ga::Update(const float deltaTime) {

}

void Scene2ga::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.694f, 0.251f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(drawInWireMode){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	// Global Render Data
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	// Skull Render Data
	glBindTexture(GL_TEXTURE_2D, textureSkull->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixSkull);
	meshSkull->Render(GL_TRIANGLES);	

	// Left Eye Render Data
	glBindTexture(GL_TEXTURE_2D, textureEye->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixSkull * modelMatrixEyeL);
	meshEye->Render(GL_TRIANGLES);

	// Right Eye Render Data
	glBindTexture(GL_TEXTURE_2D, textureEye->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixSkull * modelMatrixEyeR);
	meshEye->Render(GL_TRIANGLES);

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}



	
