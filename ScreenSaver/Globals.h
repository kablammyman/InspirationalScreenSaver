#pragma once
#include "LogRouter.h"
#include "CFGUtils.h"

class Globals
{
public:
	static int dirSelectionForDisplay;
	static bool useImageMemory;
	static bool viewWorkoutTimer;
	static bool viewClock;
	static bool viewPathInfo;
	static int imageDisplayTimeLength;
	static int imageMemAmt;
	static float min, sec, mil;
	static char SLASH;
	static LogRouter logRouter;
	static void InitLogger()
	{
		//check smart catolog project GetLoggingInfoFromCFG() in DataBaseManager.cpp
		vector<string> loggerList = CFGUtils::GetCfgListValue("LOGGERS");

		for (size_t i = 0; i < loggerList.size(); i++)
		{
			string listName = loggerList[i];
			vector<string> curLogger = CFGUtils::GetCfgListValue(listName);

			string loggingType = CFGUtils::GetStringValueFromList(listName, "TYPE");//consle, logfile syslog etc
			string severityLevelString = CFGUtils::GetStringValueFromList(listName, "SEVERITY"); //should have all the logging level values this appender wants
			string loggerDetails = CFGUtils::GetStringValueFromList(listName, "PATH");

			LogOutput * newLogger = logRouter.LogOutputFactory(loggingType, loggerDetails); //optional, so far, only textfiles have this data
		
			LogEntity * temp = logRouter.AddLogger(newLogger, severityLevelString);
			if (CFGUtils::GetCfgBoolValue("ADD_TIMESTAMP"))
				temp->logOut->useTimeStamp = true;
			if (CFGUtils::GetCfgBoolValue("ADD_SEVERITY"))
				temp->logOut->useSeverityString = true;
		}
	}
	static void Log(string msg)
	{
		logRouter.Log(LOG_LEVEL_INFORMATIONAL, msg);
	}

};