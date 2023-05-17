#include "Body.h"
Body::Body(): pos{}, vel{}, accel{}, mass{1.0f}, mesh{nullptr},texture{nullptr} {
}

Body::~Body() {}

void Body::Update(float deltaTime) {
	/// From 1st semester physics class
	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
	vel += accel * deltaTime;
}

void Body::ApplyForce(Vec3 force) {
	accel = force / mass;
}

void Body::UpdateOrientation(float deltaTime)
{
	float angleRadians = VMath::mag(angularVel) * deltaTime;
	float angleDegrees = angleRadians * RADIANS_TO_DEGREES;
	if (angleRadians < VERY_SMALL) return;
	Vec3 axisOfRotation = VMath::normalize(angularVel);

	Quaternion rotationQuaternion = QMath::angleAxisRotation(angleDegrees, axisOfRotation);
	orientation = rotationQuaternion * orientation; // TODO: figure out the order of multiplication
}

bool Body::OnCreate(){
	return true;
}

void Body::OnDestroy(){
}

void Body::Render() const {
}

