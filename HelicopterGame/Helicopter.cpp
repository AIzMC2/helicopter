/*
	Helicopter
		Holds the functions used for setting up the helicopter and doing the physics and math
			calculations required to make the helicopter move

			Notable Functions:
			reset() places the helicopter to its original position and reloads missiles
			updateGamePlay() does the physics calulations for the movement of the helicopter and display info including position, velocity, acceleration, and missile info
			setThrottle(int) takes a throttle value between 0-23 and updates the helicopter's throttle accordingly
			setJoystick(float, float) takes a value for theta and phi and updates the helicopter's direcion accordingly
			
			Other functions that affect the physics and orientation of the helicopter
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#include "Helicopter.h"
#include "ScriptRunner.h"

Helicopter::Helicopter() : KineticModel() {

	model = osgDB::readNodeFile("models/uh60/uh60.3ds");
	modelTransform = new osg::PositionAttitudeTransform;
	modelTransform->addChild(model.get());
	modelTransform->setPosition(osg::Vec3(0.0f, 0.0f, 1.0f));
	zThetaOffset = 180;
	setOrientation(osg::Vec3f(0.0, 0.0, 0.0));
	modelTransform->setAttitude(osg::Quat(
		osg::DegreesToRadians(orientation.x_theta), osg::Vec3f(1,0,0),
        osg::DegreesToRadians(orientation.y_theta), osg::Vec3f(0,1,0),
        osg::DegreesToRadians(orientation.z_theta), osg::Vec3f(0,0,1)));
	missileOrientation = 0;
	mass = 9000;
	maxAirspeed = 66.6667;
	maxTakeoffWeight = 21000;
	baseThrottle = mass * Physics::getInstance()->getGravity() / 10;
	maxThrottle = 23;
	maxMissiles = 10;
	missiles = maxMissiles;
	thrustVector = osg::Vec3f(0.0, 0.0, 0.0);
	velocityVector = osg::Vec3f(0,0,0);
	positionVector = modelTransform->getPosition();
	force = 0;
	isCrashed = false;
	maxTheta = 15;
	frictionConstant = mass 
		* Physics::getInstance()->getGravity() 
		* tan(osg::DegreesToRadians(maxTheta)) 
		/ pow(maxAirspeed, 2);
}

void Helicopter::reset() {

	force = 0;
	direction = osg::Vec2f(0.0, 0.0);
	missileOrientation = 0;
	isCrashed = false;
	isEnabled= false;
	missiles = maxMissiles;
	setPosition(osg::Vec3f(0.0, 0.0, 1.0));
	setVelocity(osg::Vec3f(0.0, 0.0, 0.0));
	setAcceleration(osg::Vec3f(0.0, 0.0, 0.0));
	setOrientation(osg::Vec3f(0.0, 0.0, 0.0));
	modelTransform->setAttitude(osg::Quat(
		osg::DegreesToRadians(orientation.x_theta), osg::Vec3f(1,0,0),
        osg::DegreesToRadians(orientation.y_theta), osg::Vec3f(0,1,0),
        osg::DegreesToRadians(orientation.z_theta), osg::Vec3f(0,0,1)));
}

void Helicopter::increaseRotor() {

	if (force < baseThrottle * maxThrottle) {
		force += baseThrottle; // 0.2;
	}
	else {
		force = baseThrottle * maxThrottle;
	}
}

void Helicopter::decreaseRotor() {

	if(force > 0) {
		force -= baseThrottle; //0.2;
	} 
	else {
		force = 0;
	}
}

void Helicopter::neutralRotor() {

	force = Physics::getInstance()->getGravity() * mass;
}

void Helicopter::stopRotor() {

	force = 0;
}

void Helicopter::pitchLeft() {

	if (direction.x() > -15) {
		orientation.y_theta -= 0.1;
		direction = osg::Vec2f(direction.x() - 0.2, direction.y());
	}
}

void Helicopter::pitchRight() {

	if (direction.x() < 15) {
		orientation.y_theta += 0.1;
		direction = osg::Vec2f(direction.x() + 0.2, direction.y());
	}
}

void Helicopter::pitchForward() {

	if (direction.y() < 15) {
		orientation.x_theta -= 0.2;
		direction = osg::Vec2f(direction.x(), direction.y() + 0.2);
	}
}

void Helicopter::pitchBackward() {

	if (direction.y() > -15) {
		orientation.x_theta += 0.2;
		direction = osg::Vec2f(direction.x(), direction.y() - 0.2);
	}
}

void Helicopter::yawnLeft() {

	orientation.z_theta += 0.5;
}

void Helicopter::yawnRight() {

	orientation.z_theta -= 0.5;
}

void Helicopter::increaseMissileOrientation() {

	if(missileOrientation < 85.0) {
		missileOrientation += 5.0;
	} 
}

void Helicopter::decreaseMissileOrientation() {

	if(missileOrientation > -85.0) {
		missileOrientation -= 5.0;
	} 
}

void Helicopter::setThrottle(int position) {

	if (position > 0)
	{
		if (position < maxThrottle)
			force = baseThrottle*position;
		else
			force = baseThrottle*maxThrottle;
	}
	else {
		force = 0;
	}
}

void Helicopter::update(float delta) {

	KineticModel::update(delta);

	if(positionVector.z() < 1.0) {

		if(velocityVector.z() < -4.0) {
			isCrashed = true;
			isEnabled = false;
		}

		positionVector.z() = 1.0;
		velocityVector.z() *= 0.8;
		velocityVector.z() = -velocityVector.z();
	}

}

bool Helicopter::fireMissile() {

	if (missiles > 0) {
		missiles--;
		return true;
	}

	return false;
}

void Helicopter::setJoystick(float theta, float phi) {

	if (theta < 0) {
		theta = 0;
	}
	else if (theta > 15) {
		theta = 15;
	}
	
	if (phi > 360 || phi < -360) {
		phi = fmod(phi, 360);
	}
	if (phi < 0) {
		phi += 360;
	}

	thrustVector = osg::Vec3f(-(force*sin(theta)*cos(phi)), -(force*sin(theta)*sin(phi)),(force*cos(theta)));
}

void Helicopter::setCrashed(bool crashed) {

	isCrashed = crashed;
}

float Helicopter::getThrottlePosition() const {

	return force / baseThrottle;
}

int Helicopter::getMissiles() const {

	return missiles;
}

float Helicopter::getMissileOrientation() const {

	return missileOrientation;
}

bool Helicopter::getCrashed() const {

	return isCrashed;
}