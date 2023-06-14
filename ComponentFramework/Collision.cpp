#include "Collision.h"
#include <iostream>

bool COLLISION::SphereSphereCollisionDetected(const Body* body1, const Body* body2)
{
	float collisionTreshold = body1->radius + body2->radius;
	float dist = sqrt((body1->pos.x - body2->pos.x) * (body1->pos.x - body2->pos.x) + (body1->pos.y - body2->pos.y) * (body1->pos.y - body2->pos.y));
	
	if (dist < collisionTreshold)
	{
		return true;
	}
	
	else return false;
}

void COLLISION::SphereSphereCollisionResponse(Body* body1, Body* body2)
{
	/*if (SphereSphereCollisionDetected(body1, body2))
	{
		std::cout << "Collision!" << std::endl;
	}*/

	
}

bool COLLISION::SpherePlaneCollisionDetected(const Body* body1, const MATH::Plane& plane)
{
	float dist = PMath::distance(body1->pos, plane);
	if (dist - body1->radius < 0.0f)
	{
		return true;
		std::cout << "Collide!!!" << std::endl;
	}
	return false;
}
