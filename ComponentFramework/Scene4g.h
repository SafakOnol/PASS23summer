#ifndef SCENE4g_H
#define SCENE4g_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
#include "Trackball.h"
#include "Camera.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;
class Texture;

class Scene4g : public Scene {
private:
	
	Body* sphere;
	Shader* sphereShader;
	Mesh* sphereMesh;
	Texture* sphereTexture;
	Matrix4 sphereModelMatrix;

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 cameraMatrix;
	bool drawInWireMode;
	Vec3 lightPos;
	Trackball trackball;
	Camera* camera;

public:
	explicit Scene4g();
	virtual ~Scene4g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE4g_H