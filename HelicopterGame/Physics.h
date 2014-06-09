/*
	Physics
		Holds static functions and constants the are specific to the environment

			Notable Functions:
			calculateForceDirections() using the angle of the force calculates the direction of force
			detectCollision() detects if there is a collision between spheres

			Other functions simply set the value of constants
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#ifndef PHYSICS_H
#define PHYSICS_H

#include "Logger.h"

class Physics {

public:
	Physics();
	static Physics* getInstance();
	osg::Vec3f calculateForceDirections(float, osg::Vec2f, float);
	bool detectCollision(const osg::BoundingSphere&, const osg::BoundingSphere&);
	osg::Vec2f xyToMagnitudeBearing(float, float);
	osg::Vec2f MagnitudeBearingToXY(float, float);
	float getGravity() const;
	int getFrictionMultiplier() const;
	void setGravity(const float);
	void setFrictionMultiplier(int);

private:
	static Physics* instance;
	float gravity;
	int frictionMultiplier;

};

#endif