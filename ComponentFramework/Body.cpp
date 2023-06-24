#include "Body.h"
Body::Body(): 
	pos		{},
	vel		{},
	accel	{},
	mass	{1.0f},
	torque	{0.0f, 0.0f, 0.0f},
	mesh	{nullptr},
	texture	{nullptr} 
{
	// Assume the body is a solid sphere
	// radius = 0.5;
	
	// using identity matrix for rotational inertia
	rotationalInetria[0] = 1;
	rotationalInetria[1] = 0;
	rotationalInetria[2] = 0;
	rotationalInetria[3] = 0;
	rotationalInetria[4] = 1;
	rotationalInetria[5] = 0;
	rotationalInetria[6] = 0;
	rotationalInetria[7] = 0;
	rotationalInetria[8] = 1;
}

Body::~Body() {}

void Body::Update(float deltaTime) 
{
	UpdateAngularVel	(deltaTime);
	UpdatePos			(deltaTime);
	UpdateVel			(deltaTime);
	UpdateOrientation	(deltaTime);
	//ApplyTorque(torqueMag, torqueAxis);
	
}

void Body::UpdatePos(float deltaTime)
{
	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
}

void Body::UpdateVel(float deltaTime)
{
	vel += accel * deltaTime;
}

void Body::ApplyForce(Vec3 force) {
	accel = force / mass;
}

void Body::StraightlineConstraint(float deltaTime, float slope, float yIntercept)
{
	float positionConstraint = -slope * pos.x + pos.y - yIntercept;

	float JV = -slope * vel.x + vel.y; // calculate the Jacobian by taking a derivative of the pos constraint

	// Tune JV to stabilize the simulation
	float bamgarteStabilization = 0.1f;
	float bias = bamgarteStabilization * positionConstraint / deltaTime;

	// effective mass is the JM^-1JT 
	float effectiveMass = slope * slope / mass + 1.0f / mass;

	float langrangianMultiplier = (-JV - bias) / effectiveMass;

	Vec3 JT (-slope, 1, 0); // JT = Transpose of the Jabcobian

	vel += (JT / mass) * langrangianMultiplier;
}

void Body::CircleConstraint(float deltaTime, Vec3 circleCentre, float constraintRadius)
{
	float positionConstraint =
			(pos.x - circleCentre.x)	*	(pos.x - circleCentre.x)
		+	(pos.y - circleCentre.y)	*	(pos.y - circleCentre.y)
		-	constraintRadius			*	constraintRadius;

	//

	Vec3 JT	(	2.0f * pos.x - 2.0f * circleCentre.x,
				2.0f * pos.y - 2.0f * circleCentre.y,
				0.0f);

	//vel += (JT / mass) * langrangianMultiplier;

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

void Body::UpdateAngularVel(float deltaTime)
{
	angularVel += angularAccel * deltaTime;
}

void Body::UpdateAngularAccel(float deltaTime)
{
	//angularAccel = MMath::inverse(rotationalInetria) * torque;
}

void Body::ApplyTorque(float torqueMag, Vec3 torqueAxis)
{
	// τ = r × F
	// mag τ = r F sin(θ)
	float torqueMagModifier = torqueMag / 9.81; // FIGURE OUT WHY???
	torque = torqueMagModifier * torqueAxis;
	std::cout << "torque: (" << torque.x << " ," << torque.y << " ," << torque.z << ")" << std::endl;

	float value = (2.0f / 5.0f) * mass * radius * radius;
	//SetBasicRotationalInertia(value);
	//UpdateAngularAccel(deltaTime);
	rotationalInetria *= MMath::scale(value, value, value);
	angularAccel = MMath::inverse(rotationalInetria) * torque;
	//torque = rotationalInetria * angularAccel;
}

//Matrix3 Body::SetBasicRotationalInertia(float rotationalInertiaConstant)
//{
//	rotationalInetria[0] = rotationalInertiaConstant;
//	rotationalInetria[4] = rotationalInertiaConstant;
//	rotationalInetria[8] = rotationalInertiaConstant;
//	//return Matrix3 rotationalInetria; TODO-> FIX
//}

void Body::GetBasicRotationalInertia()
{
	//return Matrix3 rotationalInetria;
}

bool Body::OnCreate(){
	return true;
}

void Body::OnDestroy(){
}

void Body::Render() const {
}

