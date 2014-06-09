/*
	Physics
		Holds static functions and constants the are specific to the environment

			Notable Functions:
			calculateForceDirections() using the angle of the force calculates the direction of force
			detectCollision() detects if there is a collision between spheres

			Other functions simply set the value of constants
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#include <osg/PositionAttitudeTransform>
#include "Physics.h"
#include <iostream>

Physics::Physics() {

	gravity = (float)9.81;
	frictionMultiplier = 1;
}

Physics* Physics::getInstance() {

	static Physics *instance = NULL;
	if(instance == NULL){
		instance = new Physics();
	}

	return instance;
}

osg::Vec3f Physics::calculateForceDirections(float force, osg::Vec2f direction, float z_theta) {

	z_theta = osg::DegreesToRadians(z_theta);

	// Calculate theta and phi for the force
	float theta = osg::DegreesToRadians(direction.length());
	float phi = atan2(direction.y(), direction.x());

	Logger* logger = Logger::getInstance();
	logger->log("Theta: " + logger->f2s(theta) + " Phi: " + logger->f2s(phi));
	return osg::Vec3f(-(force*sin(theta)*cos(phi + z_theta)), -(force*sin(theta)*sin(phi + z_theta)),(force*cos(theta)));
}

bool Physics::detectCollision(const osg::BoundingSphere& bs1, const osg::BoundingSphere& bs2) {

	if (bs1.intersects(bs2)) {
		return true;
	}
	
	return false;
}

osg::Vec2f Physics::xyToMagnitudeBearing(float x, float y) {

	return (osg::Vec2f(sqrt(x * x + y * y),
		osg::RadiansToDegrees(atan(osg::DegreesToRadians(y/x)))));
}

osg::Vec2f Physics::MagnitudeBearingToXY(float magnitude, float bearing) {

	return (osg::Vec2f(magnitude * cos(osg::DegreesToRadians(bearing)),
		magnitude * sin(osg::DegreesToRadians(bearing))));
	
}

float Physics::getGravity() const {

	return gravity;
}

int Physics::getFrictionMultiplier() const {

	return frictionMultiplier;
}

void Physics::setGravity(float inputGravity) {

	gravity = inputGravity;
}

void Physics::setFrictionMultiplier(int inputFriction) {

	frictionMultiplier = inputFriction;
}