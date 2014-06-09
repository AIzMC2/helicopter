CPP_LIST=Logger.cpp mainApp.cpp ModelController.cpp Physics.cpp Render.cpp ScriptRunner.cpp SleepThread.cpp TimerHandler.cpp
LIB_FOLDER=-L /cygdrive/c/OSG/lib
LIBS=-l curllib -l libjpegD -l OpenThreads -l osgDBd -l osgManipulatord -l osgShadow -l osgTextd -l osgVolumed -l freetype237 -l libpng13 -l osg -l osgFX -l osgParticle -l osgSim -l osgUtil -l giflib -l libpng13d -l osgAnimation -l osgFXd -l osgParticled -l osgSimd -l osgUtild -l osgWidget -l osgWidgetd -l glut32 -l libtiff -l osgAnimationd -l osgGA -l osgPresentation -l osgTerraind -l osgViewer -l glut32D -l libtiffD -l osgd -l osgGAd -l osgPresentationd -l osgTerrain -l osgViewerd -l zlib1 -l libjpeg -l OpenThreadsd -l osgDB -l osgManipulator -l osgShadowd -l osgText -l osgVolume -l zlib1d
INCLUDE_OSG=-I /cygdrive/c/OSG/include

all: Logger.cpp mainApp.cpp ModelController.cpp Physics.cpp Render.cpp ScriptRunner.cpp SleepThread.cpp TimerHandler.cpp
	g++ -Wall -std=c++11 -w ${INCLUDE_OSG} ${LIB_FOLDER} ${LIBS} ${CPP_LIST} -o helicopter
