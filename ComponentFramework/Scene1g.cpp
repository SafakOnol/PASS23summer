#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene1g.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"

Scene1g::Scene1g() :sphere{nullptr}, shader{nullptr}, mesh{nullptr},
drawInWireMode{false} {
	Debug::Info("Created Scene1g: ", __FILE__, __LINE__);
}

Scene1g::~Scene1g() {
	Debug::Info("Deleted Scene1g: ", __FILE__, __LINE__);
}

bool Scene1g::OnCreate() {
	Debug::Info("Loading assets Scene1g: ", __FILE__, __LINE__);
	sphere = new Body();
	sphere->OnCreate();
	sphere->angularVel = Vec3(0.0f, 0.0f, -1.0f);
	
	mesh = new Mesh("meshes/Sphere.obj");
	mesh->OnCreate();

	shader = new Shader("shaders/multiLightPhongVert.glsl", "shaders/multiLightPhongFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix.loadIdentity();
	lightPos0 = Vec3(8.0f, 4.0f, 0.0f);
	lightPos1 = Vec3(-8.0f, 4.0f, 0.0f);
	return true;
}

void Scene1g::OnDestroy() {
	Debug::Info("Deleting assets Scene1g: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	
}

void Scene1g::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene1g::Update(const float deltaTime) {
	sphere->Update(deltaTime);
	//sphere->UpdateOrientation(deltaTime);
	Matrix4 translation = MMath::translate(sphere->pos);
	float radius = 1.0f;
	Matrix4 scaling = MMath::scale(Vec3(radius, radius, radius));
	Matrix4 rotation = MMath::toMatrix4(sphere->orientation);
	modelMatrix = translation * rotation * scaling;

}

void Scene1g::Render() const {
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
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);

	glUniform3fv(shader->GetUniformID("lightPos0"), 1, lightPos0);
	glUniform3fv(shader->GetUniformID("lightPos1"), 1, lightPos1);
	mesh->Render(GL_TRIANGLES);
	glUseProgram(0);
}



	
