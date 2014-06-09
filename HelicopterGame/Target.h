/*
	Target
		Three balls that are effected by the missile passing through them

			Notable Functions:
			update() detects collision with the missile, changes the balls' colors, and logs
				the collision
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
*/

#ifndef TARGET_H
#define TARGET_H

#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <vector>
#include "Physics.h"
#include "Logger.h"

class Target {

public:
	Target(osg::Vec3f, float);
	osg::ref_ptr<osg::PositionAttitudeTransform> getBallTransform();
	~Target();

	void update(vector<osg::BoundingSphere> *);

private:
	osg::ref_ptr<osg::ShapeDrawable> ball;
	osg::ref_ptr<osg::Geode> ballNode;
	osg::ref_ptr<osg::PositionAttitudeTransform> ballTransform;
	osg::Vec3f center;
	float radius;
};

#endif