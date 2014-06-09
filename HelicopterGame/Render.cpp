/*
	Render
		Holds the functions used for setting up the world and doing the physics and math calculations required to make the helicopter move
			Notable Functions:
			Game_Play() is the intro function required to set everything up
			updateGamePlay() does the physics calulations for the movement of the helicopter including calculating the forces of gravity, throttle, and friction
			setThrottle(int) takes a throttle value between 0-23 and updates the helicopter's throttle accordingly
			setJoystick(float, float) takes a value for theta and phi and updates the helicopter's direcion accordingly
			detectCollision(osg::BoundingSphere&, osg::BoundingSphere&) takes two bounding spheres (one for the helicopter and another for the obstacle) and
				determined if they intersect

			There are other functions that do the math and other functions
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
					Brian Schweitzer, Karlee Stein, Tylor Froese, 
					Trevor Douglas (used lab code)

*/

#include <osg/ShapeDrawable>
#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osg/FrameStamp>

#include "TimerHandler.h"
#include "ScriptRunner.h"
#include "Logger.h"
#include "ModelController.h"
#include "Render.h"

Render::Render(){

	last = 0;
    hud.initializeHUD();
	randomVelocity = ((((float) rand()) / (float) RAND_MAX) * 35.0) + 5.0;

    osg::Camera * hudCamera;
	ScriptRunner * sr = ScriptRunner::getInstance();
	sr->setRender(this);
	
	osg::ref_ptr<osg::Node> tent = osgDB::readNodeFile("models/tent/tent.3ds");
	osg::ref_ptr<osg::Node> factory = osgDB::readNodeFile("models/factory/factory.3DS");
	osg::ref_ptr<osg::Node> ground = osgDB::readNodeFile("lz.osg");

	osg::ref_ptr<ModelController> ctrler = new ModelController(helicopter.getModelTransform(),this);

	tent1Transform = new osg::PositionAttitudeTransform;
	tent1Transform->addChild(tent.get());
	tent1Transform->setPosition(osg::Vec3(-15.0f, -55.0f, 0.0f));
	tent1Transform->setScale(osg::Vec3(0.05f, 0.05f, 0.05f));

	tent2Transform = new osg::PositionAttitudeTransform;
	tent2Transform->addChild(tent.get());
	tent2Transform->setPosition(osg::Vec3(5.0f, -595.0f, 0.0f));
	tent2Transform->setScale(osg::Vec3(0.05f, 0.05f, 0.05f));

	tent3Transform = new osg::PositionAttitudeTransform;
	tent3Transform->addChild(tent.get());
	tent3Transform->setPosition(osg::Vec3(5.0f, -395.0f, 0.0f));
	tent3Transform->setScale(osg::Vec3(0.05f, 0.05f, 0.05f));
	
	factoryTransform = new osg::PositionAttitudeTransform;
	factoryTransform->addChild(factory.get());
	factoryTransform->setPosition(osg::Vec3(-15.0f, -225.0f, 0.0f));
	factoryTransform->setScale(osg::Vec3(0.25f, 0.25f, 0.25f));

	groundTransform = new osg::PositionAttitudeTransform;
	groundTransform->addChild(ground.get());
	groundTransform->setPosition(osg::Vec3(0.0f, 0.0f, -91.5f));
	groundTransform->setScale(osg::Vec3(20.0f, 20.0f, 1.0f));

	targets.push_back(Target(osg::Vec3f(0, -200, 80), 10));
	targets.push_back(Target(osg::Vec3f(10, -300, 70), 20));
	targets.push_back(Target(osg::Vec3f(20, -400, 60), 30));

	osg::ref_ptr<osg::Group> targetGroup = new osg::Group();
	targetGroup->addChild(targets.at(0).getBallTransform().get());
	targetGroup->addChild(targets.at(1).getBallTransform().get());
	targetGroup->addChild(targets.at(2).getBallTransform().get());

	//Retreive the hud camera.
    hudCamera = hud.getHudCamera();

	osg::ref_ptr<osg::Group> rootNode = new osg::Group;  //Create a group node
	rootNode->addChild(groundTransform.get());
	rootNode->addChild(helicopter.getModelTransform());
	rootNode->addChild(tent1Transform.get());
	rootNode->addChild(tent2Transform.get());
	rootNode->addChild(tent3Transform.get());
	rootNode->addChild(factoryTransform.get());
	rootNode->addChild(targetGroup.get());
	rootNode->addChild(hudCamera);

	for (int i = 0; i < helicopter.getMissiles(); i++) {
		missiles.push_back(Missile());
		rootNode->addChild(missiles.back().getModelTransform());
	}
	
	viewer.addEventHandler(ctrler.get());

	viewer.addEventHandler(new TimerHandler(this));	

	viewer.setUpViewInWindow(100,100,800,600);

	viewer.setSceneData(rootNode.get());

	//This bit of code will have the camera follow the model
    osg::ref_ptr<osgGA::NodeTrackerManipulator> nodeTracker = new osgGA::NodeTrackerManipulator;
    nodeTracker->setHomePosition( osg::Vec3(0, -50.0, 0), osg::Vec3(), osg::Z_AXIS );

    //This will track the center of the helicopter and rotate as well.
    nodeTracker->setTrackerMode( osgGA::NodeTrackerManipulator::NODE_CENTER_AND_ROTATION );
    nodeTracker->setRotationMode( osgGA::NodeTrackerManipulator::TRACKBALL );
    nodeTracker->setTrackNode(helicopter.getModel());
    viewer.setCameraManipulator( nodeTracker );

	viewer.run();
}

void Render::updateGamePlay()
{
	osg::Vec3f helicopterPosition;
	osg::Vec3f helicopterVelocity;
	osg::Vec3f helicopterAcceleration;
	osg::Vec3f helicopterForce;
	std::vector<osg::BoundingSphere> firedMissileBounds;

	// Find the Delta Time since the previous frame
	float delta = viewer.getFrameStamp()->getReferenceTime() - last;
	last = viewer.getFrameStamp()->getReferenceTime();

	helicopter.update(delta);

	for (std::vector<Missile>::iterator i = missiles.begin(); i != missiles.end(); i++) {
		if (i->getEnabled()) {
			i->update(delta);
			firedMissileBounds.push_back(osg::BoundingSphere(i->getModelTransform()->getBound()));
		}
	}

	for (std::vector<Target>::iterator i = targets.begin(); i != targets.end(); i++) {

		i->update(&firedMissileBounds);
	}

	helicopterPosition = helicopter.getPosition();
	helicopterVelocity = helicopter.getVelocity();
	helicopterAcceleration = helicopter.getAcceleration();
	helicopterForce = helicopter.getForce();

	// Collision with the ground
	if(helicopter.getCrashed()) {
		hud.setWarning("CRASHED");
	}

	// Logging the Information
	Logger* logger = Logger::getInstance();
	string something = logger->f2s(helicopterPosition.x());
	logger->log("X Pos: " + logger->f2s(helicopterPosition.x()) + " Y Pos: " + logger->f2s(helicopterPosition.y()) + " Z Pos: " + logger->f2s(helicopterPosition.z())); 
	logger->log("X Vel: " + logger->f2s(helicopterVelocity.x()) + " Y Vel: " + logger->f2s(helicopterVelocity.y()) + " Z Vel: " + logger->f2s(helicopterVelocity.z()));
	logger->log("X Acc: " + logger->f2s(helicopterAcceleration.x()) + " Y Acc: " + logger->f2s(helicopterAcceleration.y()) + " Z Acc: " + logger->f2s(helicopterAcceleration.z()));
	logger->log("Throttle position: " + logger->f2s(helicopter.getThrottlePosition()));

	if(ScriptRunner::getInstance()->getStatus()){ ScriptRunner::getInstance()->doCommand(); }
	
	// Update the HUD
	hud.setPosition(helicopter.getModelTransform()->getPosition());
	hud.setVelocity(helicopterVelocity);
	hud.setAcceleration(helicopterAcceleration);
	hud.setMissiles(helicopter.getMissiles(), randomVelocity, helicopter.getMissileOrientation());

}

void Render::startMoving() {

    viewer.addEventHandler(new TimerHandler(this));
}

void Render::fireMissile() {

	if (helicopter.fireMissile()) {
		missiles.at(helicopter.getMissiles()).fire(helicopter.getPosition(), 
			helicopter.getVelocity(),
			helicopter.getOrientation().z() + 180,
			randomVelocity,
			helicopter.getMissileOrientation());
	}

	randomVelocity = ((((float) rand()) / (float) RAND_MAX) * 35.0) + 5.0;
}

osg::Viewport* Render::getViewport() {

	return viewer.getCamera()->getViewport();
}