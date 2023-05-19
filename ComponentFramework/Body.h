#ifndef BODY_H
#define BODY_H
#include <Vector.h> /// This is mine in GameDev
#include <MMath.h>
#include <QMath.h>

using namespace MATH; /// therefore...


/// Just forward declair these classes so I can define a pointer to them
/// Used later in the course
class Mesh;
class Texture;

class Body {
public:
    Body();
    ~Body();
//private: /// Physics stuff
	
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	Vec3 force;

	// angular motion variables
	float angle;
	Vec3 angularVel;
	Vec3 angularAccel;

	float torqueMag;
	Vec3 torque;
	Vec3 torqueAxis;
	
	
	Quaternion orientation;
	Quaternion rotationQuaternion;
	
	Matrix3 rotationalInetria;
	float rotationalInertiaConstant;
	float radius; // assuming the body is a sphere
	float mass;
private: /// Graphics stuff 
	Mesh *mesh;
	Texture *texture;
	
public:
	bool OnCreate();
	void OnDestroy();
	void Update(float deltaTime);
	void Render() const;

	// Physics
	void ApplyForce(Vec3 force);
	void setAccel(const Vec3& accel_) { accel = accel_; }
	// Update Methods
	void UpdateOrientation(float deltaTime);
	void UpdateAngularVel(float deltaTime);
	void UpdateAngularAccel(float deltaTime);
	void ApplyTorque(float torqueMag, Vec3 torqueAxis); // torque Magnitude = r F sin(θ)
	// Utility
	//Matrix3 SetBasicRotationalInertia(float rotationalInertiaConstant);
	void GetBasicRotationalInertia();
	
	
};



#endif
