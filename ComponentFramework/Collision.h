#pragma once
#include "Body.h"
#include "Plane.h"
#include <PMath.h>

namespace COLLISION
{
	bool SphereSphereCollisionDetected(const Body* body1, const Body* body2);

	void SphereSphereCollisionResponse(Body* body1, Body* body2);

	bool SpherePlaneCollisionDetected(const Body* body1, const Plane& plane);


}

