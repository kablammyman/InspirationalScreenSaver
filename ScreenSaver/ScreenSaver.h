#pragma once

#include <string>
#include <vector>

#include "Scene.h"

#include "KeyProxy.h"
#include "SDL_ScreenStruct.h"
#include "CurrentImage.h"
#include "StopWatch.h"
#include "ImageSelector.h"

//#include "queueImageSelector.h"
//#include "shuffledImageSelector.h"
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

	ImageSelector imageSelector;
	KeyProxy keyProxy;

	string filePath;
	AppLegend* legend;
	CurrentImage* curImage;
	

	//WorkoutTimer* workoutTimer;
	SDL_ScreenStruct *ss;


	FILE *logFile;
	void WriteToLogFile(string line);

	
public:
	int dirSelectionForDisplay;
	vector<string> displayDirs;
	ScreenSaver(SDL_ScreenStruct *s);
	~ScreenSaver()
	{
		if (logFile)
			fclose(logFile);
	}
	void SetCurImgObj(CurrentImage *c);
	
	bool DoDelete(string path, string createDate = "");
	void Update();

	void ChangeImage(string newImage = "");
	void GotoNextImage();
	void GotoPrevImage();
	void DeleteSingleImage(string fileToDelete);
	void DeleteGallery(string galleryToDelete);
	void ToggleLegend();
	//void PauseWorkoutTimer();
	virtual void ChangeScreenSize(int screenW, int screenH);
	void Draw();

};

