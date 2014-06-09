/*
	Logger
		Singleton Logger that allows a string to be logged to a file with a timestamp

		Credits: Tylor Froese, Brian Schwietzer

*/

#include "Logger.h"

using namespace std;


void Logger::log(string data){
	if(loggingOn){
		time_t rawtime;
		struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		fprintf(logFile,"%04d-%02d-%02d %02d:%02d:%02d: %s \n",
			timeinfo->tm_year,
			timeinfo->tm_mon,
			timeinfo->tm_mday,
			timeinfo->tm_hour,
			timeinfo->tm_min,
			timeinfo->tm_sec,
			data.c_str());
	}
}

void Logger::openLog() {

	char * charLog;
	charLog = new char[logFileName.size()+1];
	strcpy(charLog, logFileName.c_str());
	logFile = fopen(charLog,"a");
}

void Logger::closeLog() {

	fclose(logFile);
}
void Logger::setFileName(string name) {

	logFileName = name;
}

void Logger::toggleLogging() {

	if(loggingOn) {
		closeLog();
		loggingOn = false;
	}
	else {
		openLog();
		loggingOn = true;
	}
}

// Float to String converter (for the Logger)
std::string Logger::f2s(float num) {

	return to_string((long double)num);
}

Logger::Logger(){

	loggingOn = false;
}
