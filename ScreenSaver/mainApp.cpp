#include "mainApp.h"
#include "Globals.h"

#include "CFGUtils.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include "FileUtils.h"


float Globals::min, Globals::sec, Globals::mil;
int Globals::imageDisplayTimeLength;
int Globals::imageMemAmt;
bool Globals::viewPathInfo;
bool Globals::viewClock;
bool Globals::viewWorkoutTimer;
bool Globals::useImageMemory;
char Globals::SLASH;
MainApp::MainApp()
{
#ifdef _WIN32
	Globals::SLASH = '\\';
	mainWorkingPath = "C:\\";//main path to work from
#else
	Globals::SLASH = '/';
	mainWorkingPath = "/media/";//main path to work from
#endif
	
	

	Globals::min = 2, Globals::sec = 5, Globals::mil = 0;
	Globals::imageDisplayTimeLength = 5;
	Globals::imageMemAmt = 10;
	Globals::viewPathInfo = true;
	Globals::viewClock = true;
	Globals::viewWorkoutTimer = true;
	Globals::useImageMemory = true;

	filePathBase = "";
	sndFile = filePathBase + Globals::SLASH +"snd.wav";

}
//---------------------------------------------------------------------------------------
bool MainApp::ReadCFG(string path)
{
	
	//sndFile.replace( sndFile.begin(), sndFile.end(), '\\', '/' );
	if(path != "")
		filePathBase = path;
	string cfgFile = filePathBase + Globals::SLASH + "morningGloryCfg.txt";

	if (!CFGUtils::ReadCfgFile(cfgFile, '|'))
	{
		printf("Error opening %s\n", cfgFile.c_str());
		screenSaver->WriteToLogFile("Error opening "+ cfgFile);
		return false;
	}

	mainWorkingPath = CFGUtils::GetCfgStringValue("mainWorkingPath");
	int numFoldersInBase = FileUtils::GetNumFoldersinDir(mainWorkingPath);
	if (numFoldersInBase < 1)
	{
		screenSaver->WriteToLogFile("invalid mainWorkingPath in cfg file: " + mainWorkingPath);
		return false;
	}

	screenSaver->dirSelectionForDisplay = CFGUtils::GetCfgIntValue("dirSelectionForDisplay");
	
	vector<string> dirs = CFGUtils::GetCfgListValue("displayDirs");
	for (size_t i = 0; i < dirs.size(); i++)
		if (dirs[i] == "all")
		{
			//gotta dewlete other folders first
			dirs.clear();
			dirs = FileUtils::GetAllFolderNamesInDir(mainWorkingPath);
			break;
		}

	if (dirs.size() == 0)
	{
		if (mainWorkingPath[mainWorkingPath.size() - 1] != Globals::SLASH)
			mainWorkingPath += Globals::SLASH;
		dirs.push_back(mainWorkingPath);
	}

	screenSaver->SetDisplayDirs(dirs);

	vector<string> stopWatch = CFGUtils::GetCfgListValue("stopWatch");
	if (!stopWatch.empty())
	{
		Globals::min = CFGUtils::GetFloatValueFromList("stopWatch", "min");
		Globals::sec = CFGUtils::GetFloatValueFromList("stopWatch", "sec");
		Globals::mil = CFGUtils::GetFloatValueFromList("stopWatch", "mil");
	}

	return true;
}

//---------------------------------------------------------------------------------------
void MainApp::LogicUpdate()
{
	curScreen->UpdateScene();
}
//---------------------------------------------------------------------------------------
void MainApp::GraphicsUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	curScreen->DrawScene();

	SDL_UpdateTexture(screenBufferTexture, NULL, curScreen->GetSceneScreenBuffer()->pixels, screenStruct.screenW * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
//---------------------------------------------------------------------------------------
void MainApp::InitWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullScreen)
{
	screenStruct.screenW = SCREEN_WIDTH;
	screenStruct.screenH = SCREEN_HEIGHT;
	screenSaver = new ScreenSaver(&screenStruct);

	// Create an application window with the following settings:
	if (!fullScreen)
		window = SDL_CreateWindow(
			"ScreenSaver",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			screenStruct.screenW,                               // width, in pixels
			screenStruct.screenH,                               // height, in pixels
			SDL_WINDOW_RESIZABLE
		);
	else
		window = SDL_CreateWindow(
			"ScreenSaver",                  // window title
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
	screenBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, screenStruct.screenW, screenStruct.screenH);

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
