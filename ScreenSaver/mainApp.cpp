#include "mainApp.h"
#include "Globals.h"

#include "CFGUtils.h"
#include <Windows.h>
#include "FileUtils.h"
#include <ctime> 

float Globals::min, Globals::sec, Globals::mil;
int Globals::imageDisplayTimeLength;
int Globals::imageMemAmt;
bool Globals::viewPathInfo;
bool Globals::viewClock;
bool Globals::viewWorkoutTimer;
bool Globals::useImageMemory;

MainApp::MainApp()
{
	mainWorkingPath = "C:\\";//main path to work from
	timeinfo = 0;

	Globals::min = 2, Globals::sec = 5, Globals::mil = 0;
	Globals::imageDisplayTimeLength = 5;
	Globals::imageMemAmt = 10;
	Globals::viewPathInfo = true;
	Globals::viewClock = true;
	Globals::viewWorkoutTimer = true;
	Globals::useImageMemory = true;

	filePathBase = "D:\\source\\InspirationalScreenSaver\\build_vs2015\\ScreenSaver\\Debug";
	sndFile = filePathBase + "\\snd.wav";

	srand((unsigned)time(0));
	ltime = time(0);
	stime = (unsigned)ltime / 2;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	screenSaver = new ScreenSaver(&screenStruct);
	
}
//---------------------------------------------------------------------------------------
bool MainApp::ReadCFG()
{
	
	//sndFile.replace( sndFile.begin(), sndFile.end(), '\\', '/' );

	ignoreFilePath = filePathBase + "\\morningGloryCfg.txt";
	deletedFilesPath = filePathBase + "\\deletedFiles.txt";

	if (!CFGUtils::ReadCfgFile(ignoreFilePath, '|'))
	{
		printf("Error opening %s\n", ignoreFilePath.c_str());
		//alert("errorz", ignoreFilePath.c_str(), "Using defaults.","&Continue", 0, 'c', 0);
		return false;
	}

	mainWorkingPath = CFGUtils::GetCfgStringValue("mainWorkingPath");
	screenSaver->dirSelectionForDisplay = CFGUtils::GetCfgIntValue("dirSelectionForDisplay");
	screenSaver->displayDirs = CFGUtils::GetCfgListValue("displayDirs");

	vector<string> stopWatch = CFGUtils::GetCfgListValue("stopWatch");
	if (!stopWatch.empty())
	{
		Globals::min = CFGUtils::GetFloatValueFromList("stopWatch", "min");
		Globals::sec = CFGUtils::GetFloatValueFromList("stopWatch", "sec");
		Globals::mil = CFGUtils::GetFloatValueFromList("stopWatch", "mil");
	}


	numFoldersInBase = FileUtils::GetNumFoldersinDir(mainWorkingPath);

	if (numFoldersInBase < 1)
	{
		//alert("errorz", "invalid mainWorkingPaqth in cfg filw", "Using defaults.", "&Continue", 0, 'c', 0);
		return false;
	}
	for (size_t i = 0; i < screenSaver->displayDirs.size(); i++)
		if (screenSaver->displayDirs[i] == "all")
		{
			//gotta dewlete other folders first
			screenSaver->displayDirs.clear();
			screenSaver->displayDirs = FileUtils::GetAllFolderNamesInDir(mainWorkingPath);
			break;
		}

	if (screenSaver->displayDirs.size() == 0)
	{
		if (mainWorkingPath[mainWorkingPath.size() - 1] != '\\')
			mainWorkingPath.append("\\");
		screenSaver->displayDirs.push_back(mainWorkingPath);
	}

	return true;
}
//---------------------------------------------------------------------------------------
void  MainApp::updateTime()
{
	time(&rawtime);
	timeinfo = localtime(&rawtime);
}
//---------------------------------------------------------------------------------------
string MainApp::getTimeString()
{
	return asctime(timeinfo);
}
//---------------------------------------------------------------------------------------
void MainApp::LogicUpdate()
{
	curScreen->Update();
}
//---------------------------------------------------------------------------------------
void MainApp::GraphicsUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	curScreen->Draw();
	SDL_RenderPresent(renderer);
}
//---------------------------------------------------------------------------------------
void MainApp::InitWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullScreen)
{
	screenStruct.screenW = SCREEN_WIDTH;
	screenStruct.screenH = SCREEN_HEIGHT;

	// Create an application window with the following settings:
	if (!fullScreen)
		window = SDL_CreateWindow(
			"Arcade Frontend",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			screenStruct.screenW,                               // width, in pixels
			screenStruct.screenH,                               // height, in pixels
			SDL_WINDOW_RESIZABLE
		);
	else
		window = SDL_CreateWindow(
			"Arcade Frontend",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			screenStruct.screenW,                               // width, in pixels
			screenStruct.screenH,                               // height, in pixels
			SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE
		);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		exit(1);
	}

	//get current screen res...if this app is a window, it wont get window size!
	unsigned int windowCheck = SDL_GetWindowFlags(window);
	if (windowCheck & SDL_WINDOW_FULLSCREEN)
	{
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		screenStruct.screenW = DM.w;
		screenStruct.screenH = DM.h;
		fontSize = 24;
	}

}
//---------------------------------------------------------------------------------------
void MainApp::InitScreens()
{
	string menuFontPath = "";
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font* font = TTF_OpenFont(menuFontPath.c_str(), largeFontSize);

	sceneIndex = 0;
	screenStruct.font = font;
	screenStruct.renderer = renderer;
	screenStruct.fontSize = fontSize;
	screenStruct.fontPath = menuFontPath;

	allScenes.push_back(screenSaver);
	//allScenes.push_back(loading);
	//allScenes.push_back(options);

	curScreen = allScenes[sceneIndex];

}