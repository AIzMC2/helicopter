/*
	Render
		Holds the functions used for setting up the world, creating the helicopter and how it reacts with its enviroment
			Notable Functions:
			updateGamePlay() does the physics calulations for the movement of the helicopter and display info including position, velocity, acceleration, and missile info
			startMoving() adds a new event handler
			fireMissile() shoots a missile from the helicopter if there exists any on the helicopter
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
					Brian Schweitzer, Karlee Stein, Tylor Froese, 
					Trevor Douglas (used lab code)

*/


#ifndef RENDER_H
#define RENDER_H

#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include "HUD.h"
#include "Helicopter.h"
#include "Missile.h"
#include "Target.h"

class Render {

  private:
	  osg::ref_ptr<osg::PositionAttitudeTransform> tent1Transform;
	  osg::ref_ptr<osg::PositionAttitudeTransform> tent2Transform;
	  osg::ref_ptr<osg::PositionAttitudeTransform> tent3Transform;
	  osg::ref_ptr<osg::PositionAttitudeTransform> factoryTransform;
	  osg::ref_ptr<osg::PositionAttitudeTransform> groundTransform;
	  osgViewer::Viewer viewer;
	
	  float last;
	  float randomVelocity;

  public:
	  Render();
  	  void updateGamePlay();
	  void startMoving();
	  void fireMissile();
	  osg::Viewport* getViewport();
	  
	  HUD hud;
	  Helicopter helicopter;
	  std::vector<Missile> missiles;
	  std::vector<Target> targets;
};

#endif