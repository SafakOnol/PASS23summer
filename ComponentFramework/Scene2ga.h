#ifndef SCENE2ga_H
#define SCENE2ga_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
#include "Trackball.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;
class Texture;

class Scene2ga : public Scene {
private:
	Body* sphere;
	Body* skull;
	Body* eyeL;
	Body* eyeR;
	Shader* shader;
	Mesh* meshSkull;
	Mesh* meshEye;
	Texture* textureSkull;
	Texture* textureEye;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrixSkull;
	Matrix4 modelMatrixEyeL;
	Matrix4 modelMatrixEyeR;
	bool drawInWireMode;
	Vec3 lightPos;
	Trackball trackball;

public:
	explicit Scene2ga();
	virtual ~Scene2ga();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE2ga_H