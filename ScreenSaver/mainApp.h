#pragma once
#include <string>
#include <vector>

#include "SDL_ScreenStruct.h"
#include "ScreenSaver.h"
//#include "OptionsScreen.h"
//#include "StopWatchScreen.h"

using namespace std;

class MainApp
{
	

	time_t rawtime;
	struct tm* timeinfo;

	long ltime;
	int stime;

public:
	vector<Scene*> allScenes;
	Scene *curScreen;
	size_t sceneIndex;

	ScreenSaver *screenSaver;
	//OptionsScreen *optionScreen;
	//StopWatch *stopwatchScren;


	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_ScreenStruct screenStruct;

	int largeFontSize;
	int fontSize;

	MainApp();
	

	void InitWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullScreen = true);
	void InitScreens();
	void LogicUpdate();
	void GraphicsUpdate();

	bool ReadCFG();

	
	void updateTime();
	string getTimeString();
	
	int numFoldersInBase; 
	string mainWorkingPath;//main path to work from
	string sndFile;
	string filePathBase;
	string ignoreFilePath;
	string deletedFilesPath;
	

};