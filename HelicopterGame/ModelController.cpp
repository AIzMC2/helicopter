/*
    ModelController
		Sets up key events for the helicopter to increase and decrease rotation.
		Uses modified lab code to call our functions

		Credits:	Brayden Willenborg, David Crossman, Chris Carman
					Brian Schweitzer, Karlee Stein, Tylor Froese, 
					Trevor Douglas (used lab code)

*/

#include "ModelController.h"
#include "ScriptRunner.h"
#include "Logger.h"

//Override
bool ModelController::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa ) 
{
	ScriptRunner * sr = ScriptRunner::getInstance();
	
	if ( !_model ) {

		//Make sure model is initialized
		return false;
	}

	switch ( ea.getEventType()) {

		case osgGA::GUIEventAdapter::KEYDOWN:

			if (!gameRender->helicopter.getEnabled() && !gameRender->helicopter.getCrashed()) {
				gameRender->helicopter.setEnabled(true);
			}

			switch( ea.getKey() )
			{
				// If user presses 'c' or 'C', set rotor to 0 position
				case 'c': case 'C':
					gameRender->helicopter.setJoystick(0, 0);
					break;

				// If user presses '3', set throttle to gravity force
				case 'n': case 'N':
					gameRender->helicopter.neutralRotor();
					break;

				// If user presses up arrow, increase throttle
					case osgGA::GUIEventAdapter::KEY_Up:
					gameRender->helicopter.increaseRotor();
					break;

				// If user presses down arrow, decrease throttle
				case osgGA::GUIEventAdapter::KEY_Down:
					gameRender->helicopter.decreaseRotor();
					break;

				// If user presses left arrow, yawn left
				case osgGA::GUIEventAdapter::KEY_Left:
					gameRender->helicopter.yawnLeft();
					break;

				// If user presses right arrow, yawn right
				case osgGA::GUIEventAdapter::KEY_Right:
					gameRender->helicopter.yawnRight();
					break;

				// If user presses 'w', pitch forward
				case 'w': case 'W':
					gameRender->helicopter.pitchForward();
					break;

				// If user presses 's', pitch backward
				case 's': case 'S':
					gameRender->helicopter.pitchBackward();
					break;

				// If user presses 'a', pitch left
				case 'a': case 'A':
					gameRender->helicopter.pitchLeft();
					break;

				// If user presses 'd', pitch right
				case 'd': case 'D':
					gameRender->helicopter.pitchRight();
					break;

				// If user presses 'x', set rotor to 0
				case 'x': case 'X':
					gameRender->helicopter.stopRotor();
					break;

				// If user presses 'f', fire missile
				case 'f': case 'F':
					gameRender->fireMissile();
					break;

				// If user presses 'page up', increase missile orientation
				case osgGA::GUIEventAdapter::KEY_Page_Up:
					gameRender->helicopter.increaseMissileOrientation();
					break;

				// If user presses 'page down', decrease missile orientation
				case osgGA::GUIEventAdapter::KEY_Page_Down:
					gameRender->helicopter.decreaseMissileOrientation();
					break;

				// If user presses 'z', toggle friction (on/off)
				case 'z': case 'Z':
					if (Physics::getInstance()->getFrictionMultiplier() == 0) {
						Physics::getInstance()->setFrictionMultiplier(1);
					}
					else {
						Physics::getInstance()->setFrictionMultiplier(0);
					}
					break;

				// If user presses 'r', reset crash
				case 'r': case 'R':
					if (gameRender->helicopter.getCrashed()) {
						gameRender->hud.setWarning("");
						gameRender->helicopter.reset();
						
					}
					break;

				// If user presses 'p' or 'P', run script runner
				case 't': case 'T':
					if (!sr->getStatus()) {
						sr->runScripts();
					}
					break;

				//If user presses 'h' or 'H', for help menu
				case 'h': case 'H':
					gameRender->hud.toggleHelpText();
					break;

				// If user presses 'l' or 'L', toggle logging
				case 'l': case 'L':
					Logger::getInstance()->toggleLogging();
					break;
			}
			break;
	}
	return false;

}