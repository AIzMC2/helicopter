/*
	KinecticModel
		Parent class for moving object that holds functions and attributes the affect the
			location and orientation of the object

			Notable Functions:
			update() calculates the physics of a moving object and updates the position
			
			Other functions that affect the physics and orientation of the object
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#ifndef KINETICMODEL_H
#define KINETICMODEL_H

#include <osg/PositionAttitudeTransform>
#include <cmath>
#include "Physics.h"

struct Orientation {

	Orientation(float x_theta=0, float y_theta=0, float z_theta=0) :
		x_theta(x_theta), y_theta(y_theta), z_theta(z_theta) {}

	float x_theta;
	float y_theta;
	float z_theta;
};

class KineticModel {

public:
	KineticModel();
	void update(float);
	void setEnabled(bool);
	void setThrust(osg::Vec3f);
	void setDirection();
	void setPosition(osg::Vec3f);
	void setVelocity(osg::Vec3f);
	void setAcceleration(osg::Vec3f);
	void setOrientation(osg::Vec3f);

	osg::PositionAttitudeTransform* getModelTransform();
	osg::ref_ptr<osg::Node> getModel();
	osg::Vec3f getThrust() const;
	osg::Vec3f getPosition() const;
	osg::Vec3f getVelocity() const;
	osg::Vec3f getAcceleration() const;
	osg::Vec3f getForce() const;

	osg::Vec3f getOrientation();
	bool getEnabled();

protected:
	bool isEnabled;
	float mass;
	float frictionConstant;
	float force;
	float maxAirspeed;
	osg::ref_ptr<osg::Node> model;
	osg::PositionAttitudeTransform * modelTransform;
	osg::Vec3f velocityVector;
	osg::Vec3f forceVector;
	osg::Vec3f accelerationVector;
	osg::Vec3f positionVector;
	osg::Vec3f thrustVector;
	osg::Vec2f direction;
	Orientation orientation;
	float xThetaOffset;
	float yThetaOffset;
	float zThetaOffset;
};

#endif