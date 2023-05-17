#ifndef SCENE2p_H
#define SCENE2p_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;

class Scene2p : public Scene {
private:
	Body* sphere;
	Body* cube;
	Shader* shader;
	Mesh* meshSphere;
	Mesh* meshCube;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	Matrix4 modelMatrixPlatform1;
	Matrix4 modelMatrixPlatform2;
	Matrix4 modelMatrixPlatform3;
	bool drawInWireMode;
	float platformAngleDegrees = 25.0f;

public:
	explicit Scene2p();
	virtual ~Scene2p();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE2p_H