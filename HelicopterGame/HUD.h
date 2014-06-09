/*
	HUD
		Heads Up Display to show values such as: xy-position, altitude, ground speed and bearing,
			 vertical speed, lift (in g's), thrust (in g's) and bearing, helicopter orientation (bearing),
			 missile inclination (degrees), and missile initial speed (5 - 40m/s)

			Notable Functions:
			initializeHudText() creates an instance of all the text objects for the HUD
			
			Other functions simply set the text of the object to a new string
			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
					Karim Naqvi (used lab code)
*/

#ifndef HUD_H
#define HUD_H

#include <osg/Camera>
#include <osgText/Text>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <iostream>
#include "Logger.h"
#include "Physics.h"

class HUD{

private:
    osg::ref_ptr<osg::Camera> camera;
    osg::ref_ptr<osg::Geode> hudGeode;

    osgText::Text * title;
	osgText::Text * position;
	osgText::Text * velocity;
	osgText::Text * acceleration;
	osgText::Text * missiles;
	osgText::Text * crash; 
	osgText::Text * help;

	bool helpVisible;

public:
    HUD();
	void initializeHUD();
    osgText::Text * initializeText(std::string, osg::Vec3);
	void toggleHelpText();

    osg::Camera * getHudCamera();
    osg::Geode * getHudGeode();

    void setText(const std::string& hudTest);
    void setWarning(const std::string& hudTest);
	void setOrientation(osg::Vec3f value);
    void setPosition(osg::Vec3f value);
    void setVelocity(osg::Vec3f value);
    void setAcceleration(osg::Vec3f value);
	void setMissiles(unsigned int, float, float);
};

#endif

