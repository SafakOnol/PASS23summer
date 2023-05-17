#ifndef SCENE2g_H
#define SCENE2g_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;
class Texture;

class Scene2g : public Scene {
private:
	Body* sphere;
	Shader* shader;
	Mesh* mesh;
	Texture* texture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	bool drawInWireMode;
	Vec3 lightPos;

public:
	explicit Scene2g();
	virtual ~Scene2g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE2g_H