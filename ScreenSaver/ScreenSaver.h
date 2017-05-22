#pragma once

#include <string>
#include <vector>

#include "Scene.h"
#include "RenderController.h"

#include "KeyProxy.h"
#include "SDL_ScreenStruct.h"
#include "CurrentImage.h"
#include "StopWatch.h"
#include "ImageManager.h"



//#include "queueImageManager.h"
//#include "shuffledImageManager.h"
//#include "workoutTimer.h"


#define GET_RANDOM_FOLDERS 0
#define GET_SEQUENTIAL_FOLDERS 1
#define GET_SHUFFLED_FOLDERS 2

using namespace std;


class ScreenSaver : public Scene
{
	unsigned int  folderNum;
	StopWatch imageTimer;
	StopWatch refreshTimer;
	
	bool timerOn;
	bool showLegend;
	bool timeOver;

	ImageManager imageManager;
	KeyProxy keyProxy;

	string filePath;
	AppLegend* legend;
	CurrentImage* curImage;
	

	//WorkoutTimer* workoutTimer;
	SDL_ScreenStruct *ss;

	time_t rawtime;
	struct tm* timeinfo;

	long ltime;
	int stime;

	FILE *logFile;
	
	
	void updateTime();
	string getTimeString();

public:
	int dirSelectionForDisplay;
	//vector<string> displayDirs;
	ScreenSaver(SDL_ScreenStruct *s);
	~ScreenSaver()
	{
		if (logFile)
			fclose(logFile);
	}
	void SetCurImgObj(CurrentImage *c);
	
	bool DoDelete(string path, string createDate = "");
	void UpdateScene();
	void SetDisplayDirs(vector<string> dirs);
	void ChangeImage(string newImage = "");
	void GotoNextImage();
	void GotoPrevImage();
	void DeleteSingleImage(string fileToDelete);
	void DeleteGallery(string galleryToDelete);
	void ToggleLegend();
	//void PauseWorkoutTimer();
	void ChangeScreenSize(int screenW, int screenH);
	void DrawScene();
	void WriteToLogFile(string line);
};

