/*
	Command
		Creates a thread that will sleep for a given amount of time

		Credits: Brian Schwietzer

*/

#ifdef WIN32
	#define WINDOWS
#elif WIN64
	#define WINDOWS
#else
	#define LINUX
#endif

#ifdef WINDOWS
	#include <windows.h>
#endif

#ifdef LINUX
	#include <unistd.h>
	#define Sleep(x) usleep((x)*1000)
#endif

#include "SleepThread.h"
#include <OpenThreads/Thread>

SleepThread::SleepThread(int time) {

	sleepTime = time;
}

void SleepThread::run() {

	Sleep(sleepTime * 1000);
}