#pragma once
#include <Matrix.h>
#include <MMath.h>
#include "Trackball.h"
#include "Shader.h"
#include "Mesh.h"

using namespace MATH;

class Camera
{
private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;
	Trackball* trackball;

public:
	Camera();
	~Camera();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool OnCreate();
	void OnDestroy();
	void Render() const ;

	void SetProjectionMatrix(float fovy, float near, float far);
	void LookAt(const Vec3 &eye, const Vec3 &at, const Vec3 &up); // TODO: Write a set viewmatrix function instead

	const Matrix4 GetProjectionMatrix() const { return projectionMatrix; }
	const Matrix4 GetViewMatrix() const { return viewMatrix; }
};

