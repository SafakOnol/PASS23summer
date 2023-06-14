#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene1p.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"

Scene1p::Scene1p() : 
	sphere{nullptr},
	cube{nullptr},
	shader{nullptr},
	meshSphere{nullptr},
	meshCube{ nullptr },
	drawInWireMode{true} 
{
	Debug::Info("Created Scene1p: ", __FILE__, __LINE__);
}

Scene1p::~Scene1p() {
	Debug::Info("Deleted Scene1p: ", __FILE__, __LINE__);
}

bool Scene1p::OnCreate() {
	Debug::Info("Loading assets Scene1p: ", __FILE__, __LINE__);

	
	// Sphere
	sphere = new Body();
	sphere->OnCreate();
	sphere->radius = 0.8f;
	sphere->angularVel = Vec3(0.0f, 0.0f, 0.0f);
	sphere->pos = Vec3(-4.0f, 0.6f, 0.0f);
	sphere->force = gravitationalAccel * sphere->mass;
	//sphere->angularAccel = Vec3(0.0f, 0.0f, -1.5f);
	sphere->torqueAxis = Vec3(0.0f, 0.0f, -1.0f); // z-axis (right hand rule, rotates clockwise)
	sphere->torqueMag = sphere->force.y * sphere->radius * sin(-platformAngleDegrees * DEGREES_TO_RADIANS); // angles are in ccw, therefore negative
	sphere->ApplyTorque(sphere->torqueMag, sphere->torqueAxis);

	meshSphere = new Mesh("meshes/Sphere.obj");
	meshSphere->OnCreate();

	// Cube

	meshCube = new Mesh("meshes/Cube.obj");
	meshCube->OnCreate();

	cube = new Body();
	cube->OnCreate();

	shader = new Shader("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix.loadIdentity();


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

void Scene1p::OnDestroy() {
	Debug::Info("Deleting assets Scene1p: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	cube->OnDestroy();
	delete cube;

	meshSphere->OnDestroy();
	delete meshSphere;

	meshCube->OnDestroy();
	delete meshCube;

	shader->OnDestroy();
	delete shader;

	
}

void Scene1p::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene1p::Update(const float deltaTime) {

	// TODO for assignment 1 
	// generate the angular acceleration from a torque value

	// we need a radial vector
	// points perpendicular to surface with a length r
	// for a flat surface, radial vector points up
	// for an angle, we derive x = sin(angle), y = cos(angle)
	Vec3 radialVector;
	
	//= sphere->radius * Vec3(sin(platformAngleDegrees * DEGREES_TO_RADIANS),
	//											cos(platformAngleDegrees * DEGREES_TO_RADIANS),
	//											0.0f);

	std::cout << "SPHERE X: " << sphere->pos.x << std::endl;
	std::cout << "onP1: " << onP1 << std::endl;
	std::cout << "onP2: " << onP2 << std::endl;
	std::cout << "onP3: " << onP3 << std::endl;

	if (-5.0f < sphere->pos.x && sphere->pos.x < -2.0f)
	{
		onP1 = true;
		onP2 = false;
		onP3 = false;
		radialVector = sphere->radius * Vec3(	sin(platformAngleDegrees * DEGREES_TO_RADIANS),
												cos(platformAngleDegrees * DEGREES_TO_RADIANS),
												0.0f);
	}
	else if (-2.0f < sphere->pos.x && sphere->pos.x < 2.0f)
	{
		onP1 = false;
		onP2 = true;
		onP3 = false;
		radialVector = sphere->radius * Vec3(0.0f, 0.0f, -1.0f);
	}
	else if (2.0f < sphere->pos.x && sphere->pos.x < 5.0f)
	{
		onP1 = false;
		onP2 = false;
		onP3 = true;
		radialVector = sphere->radius * Vec3(	sin(-platformAngleDegrees * DEGREES_TO_RADIANS),
												cos(-platformAngleDegrees * DEGREES_TO_RADIANS),
												0.0f);
	}	

	sphere->vel = VMath::cross(sphere->angularVel, radialVector);
	sphere->Update(deltaTime);

	Matrix4 translation = MMath::translate(sphere->pos); // TODO - getter & setter this part
	Matrix4 scaling = MMath::scale(Vec3(sphere->radius * 0.6f, sphere->radius * 0.6f, sphere->radius * 0.6f));
	Matrix4 rotation = MMath::toMatrix4(sphere->orientation);
	modelMatrix = translation * rotation * scaling;
}

void Scene1p::Render() const {
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

	// ball
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	meshSphere->Render(GL_TRIANGLES);

	// platform 1
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixPlatform1);
	meshCube->Render(GL_TRIANGLES);

	// platform 2
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixPlatform2);
	meshCube->Render(GL_TRIANGLES);

	// platform 2
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixPlatform3);
	meshCube->Render(GL_TRIANGLES);
	
	// cube ends

	glUseProgram(0);
}



	
