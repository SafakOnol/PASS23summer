#ifndef SCENE3g_H
#define SCENE3g_H
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

class Scene3g : public Scene {
private:
	
	Body* skull;
	Body* eyeL;
	Body* eyeR;
	Shader* shader;
	Mesh* meshSkull;
	Mesh* meshEye;

	Texture* textureSkull;
	Texture* textureEye;
	Matrix4 modelMatrixSkull;
	Matrix4 modelMatrixEyeL;
	Matrix4 modelMatrixEyeR;

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 cameraMatrix;
	bool drawInWireMode;
	Vec3 lightPos;
	Trackball trackball;
	Camera* camera;

public:
	explicit Scene3g();
	virtual ~Scene3g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE3g_H