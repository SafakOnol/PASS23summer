#ifndef SCENE1ga_H
#define SCENE1ga_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;

class Scene1ga : public Scene {
private:
	Body* sphere;
	Shader* shader;
	Mesh* mesh;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	bool drawInWireMode;
	Vec3 lightPos[2];

public:
	explicit Scene1ga();
	virtual ~Scene1ga();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE1ga_H