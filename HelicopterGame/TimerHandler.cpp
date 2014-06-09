/*
	TimerHandler
		Handles the actions that need to be done on each frame
		Gets mouse coords and sends them to the force redirection function
		Calls updateGamePlay to calculate the physics and move the helicopter


			
		Credits:	Brayden Willenborg, David Crossman, Chris Carman
					Brian Schweitzer, Karlee Stein, Tylor Froese, 
					Trevor Douglas (used lab code)

*/

#include "TimerHandler.h"
#include "ScriptRunner.h"

bool TimerHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
	
	switch ( ea.getEventType()) {

	case osgGA::GUIEventAdapter::FRAME:

		gameRender->helicopter.setDirection();
		gameRender->updateGamePlay();
		_count++;
		break;
	}

	return false;
}
