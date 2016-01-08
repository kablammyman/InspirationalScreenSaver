#ifndef SCREEN_SAVER_H
#define SCREEN_SAVER_H

#include <string>
#include <vector>

#include "Scene.h"

#include "AllegroTimer.h"
#include "workoutTimer.h"
#include "KeyProxy.h"

#include "CurrentImage.h"

#include "ImageSelector.h"
#include "queueImageSelector.h"
#include "shuffledImageSelector.h"



#define GET_RANDOM_FOLDERS 0
#define GET_SEQUENTIAL_FOLDERS 1
#define GET_SHUFFLED_FOLDERS 2

using namespace std;


class ScreenSaver : public Scene
{
	unsigned int  folderNum;
	AllegroTimer imageTimer;
	AllegroTimer refreshTimer;
	
	bool timerOn;
	bool showLegend;
	bool timeOver;

	queueImageSelector imageSelector;
	KeyProxy keyProxy;

	string filePath;
	AppLegend* legend;
	CurrentImage* curImage;
	int dirSelectionForDisplay;
public:
	
	ScreenSaver();
	WorkoutTimer* workoutTimer;
	void setCurImgObj(CurrentImage *c);
	
	bool doDelete(string path, string createDate = "");
	void update();

	void changeImage(string newImage = "");
	void gotoNextImage();
	void gotoPrevImage();
	void deleteSingleImage(string fileToDelete);
	void deleteGallery(string galleryToDelete);
	void toggleLegend();
	void pauseWorkoutTimer();
	virtual void changeScreenSize(int screenW, int screenH);
	void draw();

};

#endif //SCREEN_SAVER_H