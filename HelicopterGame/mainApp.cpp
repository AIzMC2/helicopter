/*
	mainApp
		Lab code runner with our function in it

		Credits:	Brayden Willenborg, David Crossman, Chris Carman,
					Original code by Brian Schweitzer, Karlee Stein, Tylor Froese, 
					Trevor Douglas (used lab code)

*/

#include "HUD.h"
#include "Render.h"
#include <osg/ArgumentParser>
#include <iostream>
#include <fstream>
#include <OpenThreads/Thread>
#include "ScriptRunner.h"
#include "Logger.h"

int main(int argc, char** argv)
{
	Logger * logger = Logger::getInstance();
	ScriptRunner * sr = ScriptRunner::getInstance();
	osg::ArgumentParser parser = osg::ArgumentParser(&argc, argv);

	if(parser.containsOptions()) {

		int sLoc = parser.find("-s");
		int lLoc = parser.find("-l");
		if(sLoc > 0) {

			if(parser.isString(sLoc+1)) {

				std::ifstream infile;
				infile.open(parser[sLoc+1]);
				sr->setActions(sr->parseScript(infile));
				std::cout << parser[sLoc+1] << std::endl;
			 }
		}

		if(lLoc > 0) {

			if(parser.isString(lLoc+1)) {

				logger->setFileName(parser[lLoc+1]);
			}
		}
		else {

			logger->setFileName("helicopterLog.txt");
		}
	}
	
	Render render;

	return 0;
}