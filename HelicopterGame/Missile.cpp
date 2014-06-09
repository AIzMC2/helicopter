/*
	Missile
		Holds the main characteristics of the missile

			Notable Functions:
			fire() calculates and sets the physics of the missile when launching
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#include "Missile.h"
#include "ScriptRunner.h"

Missile::Missile() {

	model = osgDB::readNodeFile("models/missile/missile.3ds");
	modelTransform = new osg::PositionAttitudeTransform;
	modelTransform->addChild(model.get());
	modelTransform->setScale(osg::Vec3(0.0f, 0.0f, 0.0f));
	modelTransform->setPosition(osg::Vec3d(0, 0, 0));
	zThetaOffset = -90;
	mass = 2000;
	maxAirspeed = 300.00015;
	thrustVector = osg::Vec3f(0.0, 0.0, 0.0);
	velocityVector = osg::Vec3f(0.0, 0.0, 0.0);
	positionVector = modelTransform->getPosition();
	force = 0;
	frictionConstant = mass 
		* Physics::getInstance()->getGravity() 
		* tan(osg::DegreesToRadians(15.0)) 
		/ pow(maxAirspeed, 2);
}

void Missile::fire(osg::Vec3d helicopterPosition, osg::Vec3f helicopterVelocity, float helicopterBearing, float initialVelocity, float missileBearing) {

	//find components of missile velocity
	osg::Vec2f zPlane = Physics::getInstance()->MagnitudeBearingToXY(initialVelocity, missileBearing);
	float missileVelocityZ = zPlane.y();
	osg::Vec2f xPlane = Physics::getInstance()->MagnitudeBearingToXY(zPlane.x(), helicopterBearing);

	//set position of missile
	modelTransform->setPosition(osg::Vec3f(helicopterPosition.x(), helicopterPosition.y(), helicopterPosition.z() - 1.0));
	positionVector = osg::Vec3f(helicopterPosition.x(), helicopterPosition.y(), helicopterPosition.z() - 1.0);

	//set the velocity of the missile based on input parameters (helicopter velocity and missile velocity)
	velocityVector = osg::Vec3f(helicopterVelocity.x() + xPlane.y(),
		helicopterVelocity.y() - xPlane.x(),
		helicopterVelocity.z() + missileVelocityZ);

	//scale the missile to visibile state
	modelTransform->setScale(osg::Vec3(0.25f, 0.25f, 0.25f));

	//set the missile direction to the helicopter bearing and missile bearing
	setOrientation(osg::Vec3f(0.0, missileBearing, helicopterBearing));
	modelTransform->setAttitude(osg::Quat(
	osg::DegreesToRadians(orientation.x_theta), osg::Vec3f(1,0,0),
    osg::DegreesToRadians(orientation.y_theta), osg::Vec3f(0,1,0),
    osg::DegreesToRadians(orientation.z_theta), osg::Vec3f(0,0,1)));

	isEnabled = true;
}