#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene0p.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"

Scene0p::Scene0p() :sphere{nullptr}, shader{nullptr}, mesh{nullptr},
drawInWireMode{false}, texture(nullptr) {
	Debug::Info("Created Scene0p: ", __FILE__, __LINE__);
}

Scene0p::~Scene0p() {
	Debug::Info("Deleted Scene0p: ", __FILE__, __LINE__);
}

bool Scene0p::OnCreate() {
	Debug::Info("Loading assets Scene0p: ", __FILE__, __LINE__);
	sphere = new Body();
	sphere->OnCreate();
	
	mesh = new Mesh("meshes/Sphere.obj");
	mesh->OnCreate();

	shader = new Shader("shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}
	texture = new Texture();
	if (texture->LoadImage("textures/earthclouds.jpg") == false) {
		return false;
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix.loadIdentity();


	//change the position of the reflection
	lightPos[0] = Vec3(0.0f, -8.0f, 0.0f);
	lightPos[1] = Vec3(0.0f, 8.0f, 0.0f);
	

	
	return true;
}

void Scene0p::OnDestroy() {
	Debug::Info("Deleting assets Scene0p: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	
}

void Scene0p::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene0p::Update(const float deltaTime) {
	
}

void Scene0p::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(drawInWireMode){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glUseProgram(shader->GetProgram());
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());//bind the texture
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);

	glUniform3fv(shader->GetUniformID("lightPos[0]"), 2, lightPos[0]);

	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}



	
