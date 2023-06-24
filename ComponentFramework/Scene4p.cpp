#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene4p.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Collision.h"

Scene4p::Scene4p() : 
	jellyfishShader{nullptr},
	jellyfishMesh{nullptr},

	drawInWireMode{true} 
{
	Debug::Info("Created Scene3p: ", __FILE__, __LINE__);
}

Scene4p::~Scene4p() {
	Debug::Info("Deleted Scene3p: ", __FILE__, __LINE__);
}

bool Scene4p::OnCreate() {
	Debug::Info("Loading assets Scene3p: ", __FILE__, __LINE__);

	// HEAD
	jellyfishMesh = new Mesh("meshes/Sphere.obj");
	jellyfishMesh->OnCreate();

	jellyfishShader = new Shader("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (jellyfishShader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}
	
	jellyfishHead = new Body();
	jellyfishHead->OnCreate();
	jellyfishHead->pos = Vec3(0, 3, -25.0f);
	jellyfishHead->radius = 6.0f;


	// ANCHORS
	anchors.push_back(new Body());
	
	/*for (Body* anchor : anchors)
	{
		anchor->OnCreate();
	}*/

	anchors[0]->pos = Vec3(-6.0f, 0.0f, -25.0);
	anchors[0]->radius = 0.5f;

	// TENTACLES
	for (int i = 0; i < SPHERES_PER_ANCHOR; ++i)
	{
		tentacleSpheres.push_back(new Body());
		tentacleSpheres[i]->radius = 0.1f;
		// oth anchor + spacing
		tentacleSpheres[i]->pos = (anchors[0]->pos - Vec3(0, ANCHOR_SPACING + anchors[0]->radius, 0)) - Vec3(0, ANCHOR_SPACING * i, 0);
	}


	// SCREEN VALUES	
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	return true;
}

void Scene4p::OnDestroy() {
	Debug::Info("Deleting assets Scene3p: ", __FILE__, __LINE__);
	

	// HEAD
	jellyfishHead->OnDestroy();
	delete jellyfishHead;

	// ANCHORS
	for (Body* anchor : anchors)
	{
		anchor->OnDestroy();
		delete anchor;
	}

	// TENTACLES
	for (Body* tentacleSphere : tentacleSpheres)
	{
		tentacleSphere->OnDestroy();
		delete tentacleSphere;
	}
}

void Scene4p::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_W:
				// tentacleSpheres[i]->pos += Vec3 (0, 0, -translationUnit); // move inwards
				break;
			case SDL_SCANCODE_S:
				// tentacleSpheres[i]->pos += Vec3 (0, 0, translationUnit); // move outwards
				break;
			case SDL_SCANCODE_D:
				// tentacleSpheres[i]->pos += Vec3 (0, translationUnit, 0); // move left
				break;
			case SDL_SCANCODE_A:
				// tentacleSpheres[i]->pos += Vec3 (0, translationUnit, 0); // move right
				break;
			case SDL_SCANCODE_Q:
				// tentacleSpheres[i]->pos += Vec3 (0, translationUnit, 0); // move up
				break;
			case SDL_SCANCODE_E:
				// tentacleSpheres[i]->pos += Vec3 (0, translationUnit, 0); // move down
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

void Scene4p::Update(const float deltaTime) {
	
	//Vec3 dragForce = -0.5 * tentacleSpheres->vel;


	for (Body* tentacleSphere : tentacleSpheres)
	{
		tentacleSphere->ApplyForce(gravitationalAccel * tentacleSphere->mass);
		tentacleSphere->Update(deltaTime);
	}

	Matrix4 jellyfishHeadScale		= MMath::scale(jellyfishHead->radius, jellyfishHead->radius, jellyfishHead->radius);
	Matrix4 jellyfishHeadTranslate	= MMath::translate(jellyfishHead->pos);
	jellyfishHead->modelMatrix = jellyfishHeadTranslate * jellyfishHeadScale;

	for (Body* anchor : anchors)
	{
		Matrix4 anchorScale		= MMath::scale(anchor->radius, anchor->radius, anchor->radius);
		Matrix4 anchorTranslate	= MMath::translate(anchor->pos);
		anchor->modelMatrix = anchorTranslate * anchorScale;
	}

	for (Body* tentacleSphere : tentacleSpheres)
	{
		Matrix4 tentacleScale = MMath::scale(tentacleSphere->radius, tentacleSphere->radius, tentacleSphere->radius);
		Matrix4 tentacleTranslate = MMath::translate(tentacleSphere->pos);
		tentacleSphere->modelMatrix = tentacleTranslate * tentacleScale;
	}

}

void Scene4p::Render() const {
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.2f, 0.251f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(drawInWireMode){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glUseProgram(jellyfishShader->GetProgram());
	glUniformMatrix4fv(jellyfishShader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(jellyfishShader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(jellyfishShader->GetUniformID("modelMatrix"), 1, GL_FALSE, jellyfishHead->modelMatrix);
	jellyfishMesh->Render();

	for (Body* anchor : anchors)
	{
		glUniformMatrix4fv(jellyfishShader->GetUniformID("modelMatrix"), 1, GL_FALSE, anchor->modelMatrix);
		jellyfishMesh->Render();
	}

	for (Body* tentacleSphere : tentacleSpheres)
	{
		glUniformMatrix4fv(jellyfishShader->GetUniformID("modelMatrix"), 1, GL_FALSE, tentacleSphere->modelMatrix);
		jellyfishMesh->Render();
	}

	glUseProgram(0);
}



	
