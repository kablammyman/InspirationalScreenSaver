#include "mainApp.h"

#include "CFGReaderDll.h"
#include <Windows.h>
#include "myFileDirDll.h"
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

	if (!CFG::CFGReaderDLL::readCfgFile(ignoreFilePath, '|'))
	{
		printf("Error opening %s\n", ignoreFilePath.c_str());
		//alert("errorz", ignoreFilePath.c_str(), "Using defaults.","&Continue", NULL, 'c', 0);
		return false;
	}

	mainWorkingPath = CFG::CFGReaderDLL::getCfgStringValue("mainWorkingPath");
	dirSelectionForDisplay = CFG::CFGReaderDLL::getCfgIntValue("dirSelectionForDisplay");
	displayDirs = CFG::CFGReaderDLL::getCfgListValue("displayDirs");

	vector<string> stopWatch = CFG::CFGReaderDLL::getCfgListValue("stopWatch");
	if (!stopWatch.empty())
	{
		min = CFG::CFGReaderDLL::getFloatValueFromList("stopWatch", "min");
		sec = CFG::CFGReaderDLL::getFloatValueFromList("stopWatch", "sec");
		mil = CFG::CFGReaderDLL::getFloatValueFromList("stopWatch", "mil");
	}


	numFoldersInBase = FileDir::MyFileDirDll::getNumFoldersinDir(mainWorkingPath);

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
			displayDirs = FileDir::MyFileDirDll::getAllFolderNamesInDir(mainWorkingPath);
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