#ifndef SCENE4p_H
#define SCENE4p_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
#include <vector>
#include <Plane.h>
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;

class Scene4p : public Scene {
private:

	Shader* jellyfishShader;
	Mesh* jellyfishMesh;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	bool drawInWireMode;
	Vec3 gravitationalAccel = Vec3(0.0f, -9.81f, 0.0f);

	// jellyfish stuff
	Body* jellyfishHead = nullptr;
	std::vector<Body*> anchors;
	std::vector<Body*> tentacleSpheres;
	const int ANCHOR_COUNT = 8;
	const int SPHERES_PER_ANCHOR = 10;
	const float ANCHOR_SPACING = 1.0f;

public:
	explicit Scene4p();
	virtual ~Scene4p();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE4p_H