/*
	HelicopterTests
		Cxxtests for the HelicopterGame

		Credits:	Brayden Willenborg, David Crossman, Chris Carman

*/

#include "Render.h"
#include <osg/ArgumentParser>
#include <iostream>
#include <fstream>
#include <OpenThreads/Thread>
#include "ScriptRunner.h"
#include "cxxtest/TestSuite.h"

class HelicopterTests : public CxxTest::TestSuite 
{
public:

	void testIsScriptRunning ( void )
	{
		ScriptRunner * sr;// = ScriptRunner::getInstance();
		//TS_ASSERT(sr->isRunning);
	}

	void testVerticalTravel ( void )
	{
		ScriptRunner * sr;// = ScriptRunner::getInstance();
		Render * render;// = new Render();
		//osg::Vec3f startPos = render->pos;
		//osg::Vec3f startVel = render->vel;
		//osg::Vec3f startAcc = render->acc;

		//if (!sr->getStatus()) {
		//	sr->runScripts();
		//}
		//
		//TS_ASSERT_EQUALS(startPos.x(), render->pos.x());
		//TS_ASSERT_EQUALS(startPos.y(), render->pos.y());
		//TS_ASSERT_LESS_THAN(startPos.z(), render->pos.z());
		//
		//TS_ASSERT_EQUALS(startVel.x(), render->vel.x());
		//TS_ASSERT_EQUALS(startVel.y(), render->vel.y());
		//TS_ASSERT_LESS_THAN(startVel.z(), render->vel.z());

		//TS_ASSERT_EQUALS(startAcc.x(), render->acc.x());
		//TS_ASSERT_EQUALS(startAcc.y(), render->acc.y());
		//TS_ASSERT_LESS_THAN(startAcc.z(), render->acc.z());
	}

	void testHorizontalTravel (void)
	{
		ScriptRunner * sr;// = ScriptRunner::getInstance();
		Render * render;// = new Render();
		//osg::Vec3f startPos = render->pos;
		//osg::Vec3f startVel = render->vel;
		//osg::Vec3f startAcc = render->acc;

		//if (!sr->getStatus()) {
		//	sr->runScripts();
		//}
		//
		//TS_ASSERT_LESS_THAN(startPos.x(), render->pos.x());
		//TS_ASSERT_LESS_THAN(startPos.y(), render->pos.y());
		//TS_ASSERT_LESS_THAN(startPos.z(), render->pos.z());
		//
		//TS_ASSERT_LESS_THAN(startVel.x(), render->vel.x());
		//TS_ASSERT_LESS_THAN(startVel.y(), render->vel.y());
		//TS_ASSERT_LESS_THAN(startVel.z(), render->vel.z());

		//TS_ASSERT_LESS_THAN(startAcc.x(), render->acc.x());
		//TS_ASSERT_LESS_THAN(startAcc.y(), render->acc.y());
		//TS_ASSERT_LESS_THAN(startAcc.z(), render->acc.z());
	}
};