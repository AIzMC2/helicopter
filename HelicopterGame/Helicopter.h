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

#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <cmath>
#include "KineticModel.h"
#include "Physics.h"

class Helicopter : public KineticModel {

public:
	Helicopter();
	void reset();
	void increaseRotor();
	void decreaseRotor();
	void neutralRotor();
	void stopRotor();	
	void pitchLeft();
	void pitchRight();
	void pitchForward();
	void pitchBackward();
	void yawnLeft();
	void yawnRight();
	void increaseMissileOrientation();
	void decreaseMissileOrientation();
	void setThrottle(int);
	void setJoystick(float, float);
	void setCrashed(bool);
	virtual void update(float);
	bool fireMissile();
	float getThrottlePosition() const;
	int getMissiles() const;
	float getMissileOrientation() const;
	bool getCrashed() const;

private:
	float maxTakeoffWeight;
	float baseThrottle;
	float maxThrottle;
	float maxTheta;
	float missileOrientation;
	unsigned int maxMissiles;
	unsigned int missiles;
	bool isCrashed;

};

#endif