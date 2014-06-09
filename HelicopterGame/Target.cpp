/*
	Target
		Three balls that are effected by the missile passing through them

			Notable Functions:
			update() detects collision with the missile, changes the balls' colors, and logs
				the collision
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#include "Target.h"

Target::Target(osg::Vec3f inputCenter, float inputRadius) {

	radius = inputRadius;
	center = inputCenter;

	ball  = new osg::ShapeDrawable;
	ball->setShape( new osg::Sphere(osg::Vec3f(0.0, 0.0,0.0), radius));
	ball->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
	ballNode = new osg::Geode;
	ballNode->addDrawable(ball.get());
	ballTransform = new osg::PositionAttitudeTransform;
	ballTransform->addChild(ballNode.get());
	ballTransform->setPosition(center);
}

osg::ref_ptr<osg::PositionAttitudeTransform> Target::getBallTransform() {

	return ballTransform;
}

void Target::update(vector<osg::BoundingSphere> *missileBounds) {

	for(vector<osg::BoundingSphere>::iterator i = missileBounds->begin(); i != missileBounds->end(); i++) {
		if (Physics::getInstance()->detectCollision(*i, osg::BoundingSphere(center, radius))) {
			ball->setColor(osg::Vec4(1.0f,0.0f,0.0f,0.0f));
			Logger::getInstance()->log("Target hit with missile.");
		}
	}
}

Target::~Target() {

}