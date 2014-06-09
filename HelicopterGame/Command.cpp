/*
	Command
		Executes the command with the given parameters

		Credits:	Brayden Willenborg, David Crossman, Chris Carman,
					Original code by Brian Schweitzer, Karlee Stein, Tylor Froese, 
					Trevor Douglas (used lab code)

*/

#include "Command.h"
#include "Render.h"
#include <vector>
#include <iostream>
#include "SleepThread.h"

Command::Command(COMMAND_TYPE command, vector<float> parameters)
{
	commandName = command;
	params = parameters;
	timeStamp = 0;
	sleepThread = NULL;
}

bool Command::executeCommand(Render * render)
{
	bool done = false;

	switch(commandName) {
	case set_friction:
		cout << printf("setting friction constant to %f\n", params[0]);
		Physics::getInstance()->setFrictionMultiplier(params[0]);
		return true;
	case set_joystick:
		cout << printf("setting joystick to %f degrees, %f degrees\n", params[0],params[1]);
		render->helicopter.setJoystick(params[0],params[1]);
		return true;
	case throttle:
		cout << "setting the throttle to " << params[0] << endl;
		render->helicopter.setThrottle(params[0]);
		return true;
	case error:
		return true;
	case delay:
		if(sleepThread == NULL) {
			sleepThread = new SleepThread(params[0]);
			sleepThread->start();
		}
		done = wait(sleepThread);
		return done;
	default:
		return false;
	}
}

bool Command::wait(SleepThread * sleepThread) {

	if(sleepThread->isRunning()) {
		return false;
	}

	delete sleepThread;
	return true;
}
