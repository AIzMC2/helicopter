/*
	Missile
		Holds the main characteristics of the missile

			Notable Functions:
			fire() calculates and sets the physics of the missile when launching
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#ifndef MISSILE_H
#define MISSILE_H

#include <osg/PositionAttitudeTransform>
#include <cmath>
#include "KineticModel.h"
#include "Physics.h"

class Missile : public KineticModel {

public:
	Missile();
	void fire(osg::Vec3d, osg::Vec3f, float, float, float);
	osg::Vec3f velocity;
	osg::Vec3f acceleration;
	osg::Vec3f position;

private:

};

#endif