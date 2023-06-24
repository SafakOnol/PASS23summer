#include "Skybox.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Mesh.h"
#include <MMath.h>
#include "Debug.h"
#include "Shader.h"


Skybox::Skybox(const char* posXfilename_, const char* posYfilename_, const char* posZfilename_,
	const char* negXfilename_, const char* negYfilename_, const char* negZfilename_)
{
	posXfilename = posXfilename_;
	posYfilename = posYfilename_;
	posZfilename = posZfilename_;
	negXfilename = negXfilename_;
	negYfilename = negYfilename_;
	negZfilename = negZfilename_;
}

Skybox::~Skybox() {}

bool Skybox::OnCreate()
{
	
	glGenTextures(1, &skyboxTextureID); //generate Texture, 1, array[]
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	SDL_Surface* textureSurface = nullptr;
	int mode = 0;

	// ********** Positive X ********** // 
	textureSurface = IMG_Load(posXfilename);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	// Dont forget to de-allocate the memory!
	SDL_FreeSurface(textureSurface);
	// ********** Positive X ********** // 

	// ********** Positive Y ********** // 
	textureSurface = IMG_Load(posYfilename);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	// Dont forget to de-allocate the memory!
	SDL_FreeSurface(textureSurface);
	// ********** Positive Y ********** //


	// ********** Positive Z ********** //
	textureSurface = IMG_Load(posZfilename);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	// Dont forget to de-allocate the memory!
	SDL_FreeSurface(textureSurface);
	// ********** Positive Z ********** //


	// ********** Negative X ********** //
	textureSurface = IMG_Load(negXfilename);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	// Dont forget to de-allocate the memory!
	SDL_FreeSurface(textureSurface);
	// ********** Negative X ********** //


	// ********** Negative Y ********** //
	textureSurface = IMG_Load(negYfilename);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	// Dont forget to de-allocate the memory!
	SDL_FreeSurface(textureSurface);
	// ********** Negative Y ********** //


	// ********** Negative Z ********** //
	textureSurface = IMG_Load(negZfilename);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	// Dont forget to de-allocate the memory!
	SDL_FreeSurface(textureSurface);
	// ********** Negative Z ********** //


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	skyboxMesh = new Mesh("meshes/Cube.obj");
	if (skyboxMesh->OnCreate() == false)
	{
		Debug::Error("Can't load skyboxMesh", __FILE__, __LINE__);
	}

	skyboxShader = new Shader("shaders/skyboxVert.glsl", "shaders/skyboxFrag.glsl");
	if (skyboxShader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}

	return true;
}

void Skybox::OnDestroy()
{
	glDeleteTextures(1, &skyboxTextureID);
	
	skyboxMesh->OnDestroy();
	delete skyboxMesh;

	skyboxShader->OnDestroy();
	delete skyboxMesh;
}

void Skybox::Update(const float deltaTime_) {}

void Skybox::Render() const
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glBindTexture(GL_TEXTURE_2D, skyboxTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	skyboxMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}