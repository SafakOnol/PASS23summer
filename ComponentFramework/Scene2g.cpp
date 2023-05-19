#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene2g.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"

Scene2g::Scene2g() :
	sphere{nullptr}, 
	shader{nullptr},
	mesh{nullptr},
	textureEarth{nullptr},
	textureMoon{nullptr},
	drawInWireMode{false} 
{
	Debug::Info("Created Scene2g: ", __FILE__, __LINE__);
}

Scene2g::~Scene2g() {
	Debug::Info("Deleted Scene2g: ", __FILE__, __LINE__);
}

bool Scene2g::OnCreate() {
	Debug::Info("Loading assets Scene2g: ", __FILE__, __LINE__);
	sphere = new Body();
	sphere->OnCreate();
	sphere->angularVel = Vec3(0.0f, 0.0f, -1.0f);

	//earth = new Body();
	//earth->OnCreate();
	//earth->angularVel = Vec3(0.0f, 0.0f, -1.0f);

	//moon = new Body();
	//moon->OnCreate();
	////moon->angularVel = Vec3(0.0f, 0.0f, -1.0f);
	
	mesh = new Mesh("meshes/Sphere.obj");
	mesh->OnCreate();

	shader = new Shader("shaders/phongTextureVert.glsl", "shaders/phongTextureFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	textureEarth = new Texture();
	textureEarth->LoadImage("textures/evilEye.jpg");

	textureMoon = new Texture();
	textureMoon->LoadImage("textures/moon.jpg");

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 7.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print("View");
	//modelMatrix.loadIdentity();
	modelMatrixEarth = MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f));
	modelMatrixMoon = MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f));

	lightPos = Vec3(8.0f, 4.0f, 0.0f);
	return true;
}

void Scene2g::OnDestroy() {
	Debug::Info("Deleting assets Scene2g: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	delete textureEarth;
	delete textureMoon;

	
}

void Scene2g::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene2g::Update(const float deltaTime) {
	//sphere->Update(deltaTime);
	//sphere->UpdateOrientation(deltaTime);
	/*Matrix4 translation = MMath::translate(sphere->pos);
	float radius = 1.0f;
	Matrix4 scaling = MMath::scale(Vec3(radius, radius, radius));
	Matrix4 rotation = MMath::toMatrix4(sphere->orientation);
	modelMatrix = translation * rotation * scaling;*/

	static float totalTime = 0.0f;
	totalTime += deltaTime * 50;
	modelMatrixEarth =	MMath::rotate(totalTime, Vec3(0.0f, 1.0f, 0.0f))
					* MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

	modelMatrixMoon = MMath::rotate(totalTime, Vec3(0.0f, 1.0f, 0.0f))
		* MMath::translate(Vec3(3.0f, 0.0f, 0.0f))
		* MMath::scale(0.25f, 0.25f, 0.25f)
		* MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

}

void Scene2g::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	// Earth Render Data
	glBindTexture(GL_TEXTURE_2D, textureEarth->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixEarth);
	mesh->Render(GL_TRIANGLES);
	//glBindTexture(GL_TEXTURE_2D, 0); -- No need to unbind since we're binding to another mesh right after
	
	
	// Moon Render Data
	glBindTexture(GL_TEXTURE_2D, textureMoon->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrixMoon);
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}



	
