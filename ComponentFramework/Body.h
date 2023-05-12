#ifndef BODY_H
#define BODY_H
#include <Vector.h> /// This is mine in GameDev
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
	Vec3 angularVel;
	Vec3 angularAccel;
	Quaternion orientation;
	Quaternion rotationQuaternion;
	float mass;
private: /// Graphics stuff 
	Mesh *mesh;
	Texture *texture;
	
public:
	bool OnCreate();
	void OnDestroy();
	void Update(float deltaTime);
	void Render() const;
	void ApplyForce(Vec3 force);
	void setAccel(const Vec3 &accel_) { accel = accel_;}
	void UpdateOrientation(float deltaTime);
};



#endif
