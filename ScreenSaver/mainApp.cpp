#include "mainApp.h"

#include "CFGUtils.h"
#include <Windows.h>
#include "FileUtils.h"
#include <ctime> 

MainApp* MainApp::m_pInstance = 0;

MainApp* MainApp::Instance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
	{
		m_pInstance = new MainApp;
	}
	return m_pInstance;
}

void MainApp::initVars(string path)
{
	mainWorkingPath = "C:\\";//main path to work from
	timeinfo = NULL;

	min = 2, sec = 5, mil = 0;
	imageDisplayTimeLength = 5;
	imageMemAmt = 10;
	viewPathInfo = true;
	viewClock = true;
	viewWorkoutTimer = true;
	useImageMemory = true;

	filePathBase = path;
	sndFile = filePathBase + "\\snd.wav";
	
	srand((unsigned)time(0));
	ltime = time(NULL);
	stime = (unsigned)ltime / 2;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	logFile = fopen("myfile.txt", "w");
	fprintf(logFile, "\nCurrent local time and date: %s \n", asctime(timeinfo));
}
//---------------------------------------------------------------------------------------
bool MainApp::readCFG()
{
	
	//sndFile.replace( sndFile.begin(), sndFile.end(), '\\', '/' );

	ignoreFilePath = filePathBase + "\\morningGloryCfg.txt";
	deletedFilesPath = filePathBase + "\\deletedFiles.txt";

	if (!CFGUtils::ReadCfgFile(ignoreFilePath, '|'))
	{
		printf("Error opening %s\n", ignoreFilePath.c_str());
		//alert("errorz", ignoreFilePath.c_str(), "Using defaults.","&Continue", NULL, 'c', 0);
		return false;
	}

	mainWorkingPath = CFGUtils::GetCfgStringValue("mainWorkingPath");
	dirSelectionForDisplay = CFGUtils::GetCfgIntValue("dirSelectionForDisplay");
	displayDirs = CFGUtils::GetCfgListValue("displayDirs");

	vector<string> stopWatch = CFGUtils::GetCfgListValue("stopWatch");
	if (!stopWatch.empty())
	{
		min = CFGUtils::GetFloatValueFromList("stopWatch", "min");
		sec = CFGUtils::GetFloatValueFromList("stopWatch", "sec");
		mil = CFGUtils::GetFloatValueFromList("stopWatch", "mil");
	}


	numFoldersInBase = FileUtils::GetNumFoldersinDir(mainWorkingPath);

	if (numFoldersInBase < 1)
	{
		//alert("errorz", "invalid mainWorkingPaqth in cfg filw", "Using defaults.", "&Continue", NULL, 'c', 0);
		return false;
	}
	for (size_t i = 0; i < displayDirs.size(); i++)
		if (displayDirs[i] == "all")
		{
			//gotta dewlete other folders first
			displayDirs.clear();
			displayDirs = CFGUtils::GetFloatValueFromList(mainWorkingPath);
			break;
		}

	if (displayDirs.size() == 0)
	{
		if (mainWorkingPath[mainWorkingPath.size() - 1] != '\\')
			mainWorkingPath.append("\\");
		displayDirs.push_back(mainWorkingPath);
	}

	return true;
}
//---------------------------------------------------------------------------------------
void MainApp::writeToLogFile(string line)
{
	if (!logFile)
		return;
	fprintf(logFile, "%s\n",line.c_str());
}

void  MainApp::updateTime()
{
	time(&rawtime);
	timeinfo = localtime(&rawtime);
}

string MainApp::getTimeString()
{
	return asctime(timeinfo);
}

//---------------------------------------------------------------------------------------
MainApp::~MainApp()
{
	if (logFile)
		fclose(logFile);
}