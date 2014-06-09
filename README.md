# ENSE 470 Helicopter Game Project

## Group Members
* Brayden Willenborg
* David Crossman
* Chris Carman

## Repository Location
* https://bitbucket.org/bwillenborg/ense470helicoptergame/

## Description
A basic helicopter game built using the Open Scene Graph Library.

Tested and working with the following compilers: 
* Visual Studio 2010 on 64-bit Windows 8.1 
* G++ 4.8.2 on 64-bit Linux CentOS 6.4

## Tasks Completed
* Warm-up
* Milstone 1
* Milestone 2 (minus testing)

## Instructions
No makefile included, must use a compiler and build by self.

## Adding or Changing User Controls

The code that pertains to user controls is in ModelController.cpp.  Specifically, in the following lines:

    switch ( ea.getEventType())
	{

		case osgGA::GUIEventAdapter::KEYDOWN:
			switch( ea.getKey() )
			{
			case 'w': case 'W':
				gameRender->increaseRotor();
				break;
    		case 's': case 'S':
				gameRender->decreaseRotor();
				break;
			case 'p': case 'P':
				if(!sr->getStatus()){sr->runScripts();}
				break;
			case 'l': case 'L':
				Logger::getInstance()->toggleLogging();
				break;
			}
			break;
	}
	return false;

Changing the key to use for a command is as easy as switcing...

     case 'x': case 'X': <command>

...to...

    case 'y': case 'Y': <command>

To add an additional command, simply add the template code below before the end of the switch statement:

    case '<lower-case key>': case: '<upper-case key>' <code to execute when key is pressed>;
    	break;