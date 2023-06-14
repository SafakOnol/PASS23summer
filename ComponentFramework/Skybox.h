#pragma once
#include <glew.h>
#include "Matrix.h"

// FORWARD DECLERATIONS
class Shader;
class Mesh;

class Skybox
{
private:
	GLuint skyboxTextureID;
	Mesh* skyboxMesh;
	Shader* skyboxShader;
	//Matrix4 skyboxModelMatrix;
	const char* posXfilename, * posYfilename, * posZfilename, * negXfilename, * negYfilename, * negZfilename;
public:
	Skybox(const char* posXfilename_, const char* posYfilename_, const char* posZfilename_, const char* negXfilename_, const char* negYfilename_, const char* negZfilename_);
	~Skybox();

	Shader* GetShader() { return skyboxShader; }
	GLuint GetSkyboxTextureID() { return skyboxTextureID; }
	//Matrix4 GetSkyboxModelMatrix() { return skyboxModelMatrix; }

	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render() const;
};



