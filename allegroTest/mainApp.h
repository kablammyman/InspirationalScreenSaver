#pragma once
#include <string>
#include <vector>


using namespace std;
class MainApp
{
	MainApp() {};
	MainApp(MainApp const&) {};             // copy constructor is private
	MainApp& operator=(MainApp const&) {};  // assignment operator is private
	static MainApp* m_pInstance;
	

	FILE *logFile;

	time_t rawtime;
	struct tm* timeinfo;

	long ltime;
	int stime;

public:
	MainApp::~MainApp();
	static MainApp* Instance();
	
	void initVars(string path);
	bool readCFG();

	void writeToLogFile(string line);
	void updateTime();
	string getTimeString();
	float min, sec, mil;
	int numFoldersInBase; 
	string mainWorkingPath;//main path to work from
	string sndFile;
	string filePathBase;
	string ignoreFilePath;
	string deletedFilesPath;
	int dirSelectionForDisplay;
	vector<string> displayDirs;

	/*
	bool openDataBase(std::string name);
	void closeDataBase();
	*/
};