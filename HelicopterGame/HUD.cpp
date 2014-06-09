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

#include "HUD.h"

HUD::HUD() {
	
	helpVisible = false;
    camera = new osg::Camera;
    hudGeode = new osg::Geode;
    camera->setClearMask( GL_DEPTH_BUFFER_BIT);
    camera->setProjectionMatrixAsOrtho2D(0,1280,0,1024);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setRenderOrder( osg::Camera::POST_RENDER );
    camera->setReferenceFrame( osg::Camera::ABSOLUTE_RF );
}

void HUD::initializeHUD() {

	//initialize our crash pointer;
    crash  = initializeText("", osg::Vec3(20,170,0));

    //initialize our title pointer;
    title  = initializeText("HEADS UP DISPLAY", osg::Vec3(20,140,0));
	
    //initialize our position pointer;
    position  = initializeText("Position:", osg::Vec3(25,110,0));
	
	//initialize our speed pointer;
    velocity  = initializeText("Speed:", osg::Vec3(25,80,0));
	
	//initialize our thrust pointer;
    acceleration  = initializeText("Thrust:", osg::Vec3(25,50,0));

	//initialize our missile orientation pointer;
    missiles  = initializeText("Missiles:", osg::Vec3(25,20,0));
	
	//initialize out help screen
	std::string instructions = "W     - Pitch Forward\n";
	instructions += "A     - Pitch Left\n";
	instructions += "S     - Pitch Back\n";
	instructions += "D     - Pitch Right\n";
	instructions += "N     - Set Rotor to Hover\n";
	instructions += "X     - Stop Rotor\n";
	instructions += "F     - Fire Missile\n";
	instructions += "PgUp  - Missile Incline ++\n";
	instructions += "PgDn  - Missile Incline --\n";
	instructions += "Up    - Throttle ++\n";
	instructions += "Down  - Throttle --\n";
	instructions += "Left  - Rotate Left\n";
	instructions += "Right - Rotate Right\n";
	instructions += "H     - Toggle Help Menu\n";
	instructions += "Z     - Toggle Friction\n";
	instructions += "R     - Reset if Crashed\n";
	instructions += "L     - Run Logger\n";
	instructions += "T     - Runs Test\n";
	help = initializeText(instructions, osg::Vec3(900,1000,0));
	help->setColor(osg::Vec4(0, 0, 0, 0));

    hudGeode->addDrawable(title);
    hudGeode->addDrawable(help);
    hudGeode->addDrawable(position);
    hudGeode->addDrawable(velocity);
    hudGeode->addDrawable(acceleration);
	hudGeode->addDrawable(missiles);
    hudGeode->addDrawable(crash);

    camera->addChild(hudGeode);
}


osgText::Text * HUD::initializeText(std::string word, osg::Vec3 position) {
	osgText::Text * text = new osgText::Text;
    text->setFont(osgText::readFontFile("fonts/arial.ttf"));
	text->setDataVariance(osg::Object::DYNAMIC );
    text->setColor(osg::Vec4(199, 77, 15, 1));
    text->setCharacterSize(24.0f);
    text->setLayout( osgText::Text::LEFT_TO_RIGHT );
    text->setText(word);
    text->setPosition(position);
	return text;
}

void HUD::toggleHelpText() {
	if (helpVisible == false) {
		help->setColor(osg::Vec4(199, 77, 15, 1));
		helpVisible = true;
	}
	else {
		help->setColor(osg::Vec4(0, 0, 0, 0));
		helpVisible = false;
	}
}

osg::Camera * HUD::getHudCamera() {

    return camera;
}

osg::Geode * HUD::getHudGeode() {

    return hudGeode;
}


void HUD::setText(const std::string& hudText) {

    title->setText(hudText);
}

void HUD::setPosition(osg::Vec3f value) {

	std::string text =   "X: " + Logger::getInstance()->f2s(value.x()) + "m" +
		" Y: " + Logger::getInstance()->f2s(value.y()) + " m" + 
		" Altitiude: " + Logger::getInstance()->f2s(value.z()) + "m";

	position->setText(text);
}

void HUD::setVelocity(osg::Vec3f value) {

	osg::Vec2f magBearing = Physics::getInstance()->xyToMagnitudeBearing(value.x(), value.y());
	std::string text = "Speed: " + Logger::getInstance()->f2s(magBearing.x()) + "m/s" + 
		" Bearing: " + Logger::getInstance()->f2s(magBearing.y()) + " degrees" + 
		" Climb: " + Logger::getInstance()->f2s(value.z()) + "m/s";

	velocity->setText(text);
}

void HUD::setAcceleration(osg::Vec3f value) {

	osg::Vec2f magBearing = Physics::getInstance()->xyToMagnitudeBearing(value.x(), value.y());
	float gravity = Physics::getInstance()->getGravity();

	std::string text = "Thrust: " + Logger::getInstance()->f2s(magBearing.x() / gravity) + "g" +
		" Bearing: " + Logger::getInstance()->f2s(magBearing.y()) + " degrees" +
		" Lift: " + Logger::getInstance()->f2s(value.z() / gravity) + "g";

	acceleration->setText(text);
}

void HUD::setMissiles(unsigned int remaining, float speed, float orientation) {

	std::string text = "Missiles: Orientation: " + Logger::getInstance()->f2s(orientation) +
		" Remaining: " + Logger::getInstance()->f2s(remaining) + " Speed: " +
		Logger::getInstance()->f2s(speed);

	missiles->setText(text);
}

void HUD::setWarning(const std::string& hudText)
{
    crash->setText(hudText);
}