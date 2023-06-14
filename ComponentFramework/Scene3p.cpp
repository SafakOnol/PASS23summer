#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene3p.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Collision.h"

Scene3p::Scene3p() : 
	shader{nullptr},
	meshSphere{nullptr},
	meshCube{nullptr},
	drawInWireMode{true} 
{
	Debug::Info("Created Scene3p: ", __FILE__, __LINE__);
}

Scene3p::~Scene3p() {
	Debug::Info("Deleted Scene3p: ", __FILE__, __LINE__);
}

bool Scene3p::OnCreate() {
	Debug::Info("Loading assets Scene3p: ", __FILE__, __LINE__);
	// Sphere
	spheres.push_back(new Body());
	spheres[0]->OnCreate();
	spheres[0]->radius = 0.8f;
	spheres[0]->angularVel = Vec3(0.0f, 0.0f, 0.0f);
	spheres[0]->pos = Vec3(-4.0f, 0.6f, 0.0f);
	spheres[0]->force = gravitationalAccel * spheres[0]->mass;
	spheres[0]->torqueAxis = Vec3(0.0f, 0.0f, -1.0f); // z-axis (right hand rule, rotates clockwise)
	spheres[0]->torqueMag = spheres[0]->force.y * spheres[0]->radius * sin(-platformAngleDegrees * DEGREES_TO_RADIANS); // angles are in ccw, therefore negative
	spheres[0]->ApplyTorque(spheres[0]->torqueMag, spheres[0]->torqueAxis);
	spheres[0]->modelMatrix.loadIdentity();

	spheres.push_back(new Body());
	spheres[1] = new Body();
	spheres[1]->OnCreate();
	spheres[1]->radius = 0.8f;
	spheres[1]->angularVel = Vec3(0.0f, 0.0f, 0.0f);
	//spheres[1]->force = gravitationalAccel * spheres[1]->mass;
	spheres[1]->pos = Vec3(0.0f, -2.0f, 0.0f);
	spheres[1]->torqueAxis = Vec3(0.0f, 0.0f, -1.0f); // z-axis (right hand rule, rotates clockwise)
	spheres[1]->torqueMag = spheres[1]->force.y * spheres[1]->radius * sin(-platformAngleDegrees * DEGREES_TO_RADIANS); // angles are in ccw, therefore negative
	spheres[1]->ApplyTorque(spheres[1]->torqueMag, spheres[1]->torqueAxis);
	spheres[1]->modelMatrix.loadIdentity();

	// TODO: (05/31/2023) -- ADD PLANES FOR PLATFORMS...

	meshSphere = new Mesh("meshes/Sphere.obj");
	meshSphere->OnCreate();

	meshCube = new Mesh("meshes/Cube.obj");
	meshCube->OnCreate();

	shader = new Shader("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	Vec3 scalingFactorPlatforms(2.0f, 0.05f, 0.05f);
	// Platform1
	Matrix4 translationPlatform1 = MMath::translate(Vec3(-3.5f, -0.2f, 0.0f));	
	Matrix4 scalingPlatform1 = MMath::scale(scalingFactorPlatforms);
	Matrix4 rotationPlatform1 = MMath::rotate(-platformAngleDegrees, Vec3(0.0f, 0.0f, 1.0f));
	modelMatrixPlatform1 = translationPlatform1 * rotationPlatform1 * scalingPlatform1;

	// Platform2
	Matrix4 translationPlatform2 = MMath::translate(Vec3(0.0f, -1.0f, 0.0f));
	Matrix4 scalingPlatform2 = MMath::scale(scalingFactorPlatforms);
	Matrix4 rotationPlatform2 = MMath::toMatrix4(Quaternion());
	modelMatrixPlatform2 = translationPlatform2 * rotationPlatform2 * scalingPlatform2 ;

	// Platform3
	Matrix4 translationPlatform3 = MMath::translate(Vec3(3.5f, -0.2f, 0.0f));
	Matrix4 scalingPlatform3 = MMath::scale(scalingFactorPlatforms);
	Matrix4 rotationPlatform3 = MMath::rotate(platformAngleDegrees, Vec3(0.0f, 0.0f, 1.0f));
	modelMatrixPlatform3 = translationPlatform3 * rotationPlatform3 * scalingPlatform3;


	return true;
}

void Scene3p::OnDestroy() {
	Debug::Info("Deleting assets Scene3p: ", __FILE__, __LINE__);
	
	for (Body* sphere : spheres)
	{
		sphere->OnDestroy();
		delete sphere;
	}

	meshSphere->OnDestroy();
	delete meshSphere;

	shader->OnDestroy();
	delete shader;

	
}

void Scene3p::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene3p::Update(const float deltaTime) {
	
	for (Body* sphere : spheres)
	{
		Vec3 radialVector = sphere->radius * 
							Vec3(sin(platformAngleDegrees * DEGREES_TO_RADIANS), cos(platformAngleDegrees * DEGREES_TO_RADIANS), 0.0f);
							sphere->vel = VMath::cross(sphere->angularVel, radialVector);
		sphere->Update(deltaTime);

		Matrix4 translation = MMath::translate(sphere->pos); // TODO - getter & setter this part
		Matrix4 scaling = MMath::scale(Vec3(sphere->radius * 0.6f, sphere->radius * 0.6f, sphere->radius * 0.6f));
		Matrix4 rotation = MMath::toMatrix4(sphere->orientation);
		sphere->modelMatrix = translation * rotation * scaling;
	}

	// COLLISION
	if (COLLISION::SphereSphereCollisionDetected(spheres[0], spheres[1]))
	{
		std::cout << "Collides!" << std::endl;
	}

	//if (COLLISION::SpherePlaneCollisionDetected(spheres[0], ))

}

void Scene3p::Render() const {
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

	for (Body* sphere : spheres)
	{
		glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->modelMatrix);
		meshSphere->Render(GL_TRIANGLES);
	}

	//// platform 1
	//glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixPlatform1);
	//meshCube->Render(GL_TRIANGLES);

	// platform 2
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixPlatform2);
	meshCube->Render(GL_TRIANGLES);

	//// platform 2
	//glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixPlatform3);
	//meshCube->Render(GL_TRIANGLES);
	
	// cube ends

	glUseProgram(0);
}



	
