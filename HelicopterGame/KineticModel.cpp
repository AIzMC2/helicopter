/*
	KinecticModel
		Parent class for moving object that holds functions and attributes the affect the
			location and orientation of the object

			Notable Functions:
			update() calculates the physics of a moving object and updates the position
			
			Other functions that affect the physics and orientation of the object
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#include "KineticModel.h"
#include "ScriptRunner.h"

KineticModel::KineticModel() {

	isEnabled = false;
	xThetaOffset = 0;
	yThetaOffset = 0;
	zThetaOffset = 0;
}

void KineticModel::update(float delta) {

	if(!isEnabled) {
		return;
	}

	float frictionScalar = Physics::getInstance()->getFrictionMultiplier() * (frictionConstant * 
		sqrt(pow(velocityVector.x(),2) + pow(velocityVector.y(),2)+pow(velocityVector.z(),2)));

	forceVector = osg::Vec3f(thrustVector.x() - frictionScalar*velocityVector.x(),
					   thrustVector.y() - frictionScalar*velocityVector.y(),
					   (-1 * Physics::getInstance()->getGravity()) * mass + thrustVector.z() - 
					   frictionScalar  *velocityVector.z());
	
	accelerationVector = osg::Vec3f(forceVector.x()/mass, forceVector.y()/mass, forceVector.z()/mass);

	positionVector = osg::Vec3f(positionVector.x() + (-velocityVector.x()*delta) + (0.5)*accelerationVector.x()*(pow(delta,2)),
					 positionVector.y() + (-velocityVector.y()*delta) + (0.5)*accelerationVector.y()*(pow(delta,2)),
					 positionVector.z() + (velocityVector.z()*delta) + (0.5)*accelerationVector.z()*(pow(delta,2)));

	velocityVector = osg::Vec3f((velocityVector.x() + accelerationVector.x()*delta)*0.99999999999,
					 (velocityVector.y() + accelerationVector.y()*delta)*0.99999999999,
					 (velocityVector.z() + accelerationVector.z()*delta)*0.99999999999);

	modelTransform->setAttitude(osg::Quat(
		osg::DegreesToRadians(orientation.x_theta), osg::Vec3f(1,0,0),
        osg::DegreesToRadians(orientation.y_theta), osg::Vec3f(0,1,0),
        osg::DegreesToRadians(orientation.z_theta), osg::Vec3f(0,0,1)));
	modelTransform->setPosition(positionVector); 
}

void KineticModel::setEnabled(bool inputEnabled) {

	isEnabled = inputEnabled;
}

void KineticModel::setThrust(osg::Vec3f inputThrust) {

		thrustVector = inputThrust;
}

void KineticModel::setDirection() {

	thrustVector = Physics::getInstance()->calculateForceDirections(force, direction, orientation.z_theta);
}

void KineticModel::setPosition(osg::Vec3f position) {

	positionVector = position;
	modelTransform->setPosition(position);
}

void KineticModel::setVelocity(osg::Vec3f velocity) {

	velocityVector = velocity;
}

void KineticModel::setAcceleration(osg::Vec3f acceleration) {

	accelerationVector = acceleration;
}

void KineticModel::setOrientation(osg::Vec3f inputOrientation) {

	orientation.x_theta = inputOrientation.x() + xThetaOffset;
	orientation.y_theta = inputOrientation.y() + yThetaOffset;
	orientation.z_theta = inputOrientation.z() + zThetaOffset;
}

osg::Vec3f KineticModel::getPosition() const {

	return positionVector;
}

osg::Vec3f KineticModel::getVelocity() const {

	return velocityVector;
}

osg::Vec3f KineticModel::getAcceleration() const {

	return accelerationVector;
}

osg::Vec3f KineticModel::getForce() const {

	return forceVector;
}

osg::PositionAttitudeTransform* KineticModel::getModelTransform() {

	return modelTransform;
}

osg::ref_ptr<osg::Node> KineticModel::getModel() {

	return model;
}

bool KineticModel::getEnabled() {

	return isEnabled;
}

osg::Vec3f KineticModel::getOrientation() {

	return (osg::Vec3f(orientation.x_theta - xThetaOffset,
		orientation.y_theta - yThetaOffset,
		orientation.z_theta - zThetaOffset));
}