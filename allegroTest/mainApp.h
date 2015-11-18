#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>

#include "Scene.h"

#include "AllegroTimer.h"

#include "KeyProxy.h"



#include "ImageSelector.h"
#include "queueImageSelector.h"
#include "shuffledImageSelector.h"
#include "workoutTimer.h"


#define GET_RANDOM_FOLDERS 0
#define GET_SEQUENTIAL_FOLDERS 1
#define GET_SHUFFLED_FOLDERS 2

using namespace std;


class mainApp : public Scene
{
	int dirSelectionForDisplay;
	unsigned int  folderNum;

	string mainWorkingPath;//main path to work from
	string filePath;

	AllegroTimer imageTimer;
	AllegroTimer refreshTimer;
	
	FILE *logFile; 

	time_t rawtime;
	struct tm* timeinfo;

	bool timerOn;
	bool showLegend;
	bool timeOver;

	queueImageSelector allFiles;
	KeyProxy keyProxy;

	float min, sec,mil;

	
	AppLegend* legend;
	CurrentImage* curImage;

public:
	WorkoutTimer* workoutTimer;
	renderObj *infoImg;
	
	mainApp();
	~mainApp();

	void setCurImgObj(CurrentImage *c);
	bool readCFG(string filePathBase);
	bool doDelete(string path, string createDate = "");
	void update();

	void changeImage(bool update = true);
	void gotoNextImage();
	void gotoPrevImage();
	void deleteSingleImage(string fileToDelete);
	void deleteGallery(string galleryToDelete);
	void toggleLegend();
	void pauseWorkoutTimer();

	bool openDataBase(std::string name);
	void closeDataBase();

	
	std::string createHash(std::string path);
	void draw();

};

#endif //MAIN_H
/*

if (snd && workoutTimer.timeOver == true && timeOver == false)
{
	play_sample(snd, 255, 128, 1000, 0);
	timeOver = true;
}

if(key[KEY_D])
		{
			clear(screenBuffer);
			scaleFactor -= amt;
			imgHeight -= 1;//bmp->h * (int)((scaleFactor*100) / 100)+1;
			imgWidth  -= 1;//bmp->w * (int)((scaleFactor*100) / 100)+1;
			imgX= (SCREEN_W/2) - (imgWidth/2);
			imgY= (SCREEN_H/2) - (imgHeight/2);
			//clear(screen);
			//stretch_blit(bmp, screenBuffer, 0, 0, bmp->w, bmp->h,imgX, imgY, imgWidth, imgHeight);
		}
			if(key[KEY_U])
		{
			clear(screenBuffer);
			scaleFactor += amt;
			imgHeight += 1;//bmp->h * (int)((scaleFactor*100) / 100)+1;
			imgWidth  += 1;//bmp->w * (int)((scaleFactor*100) / 100)+1;
			imgX = (SCREEN_W/2) - (imgWidth/2);
			imgY = (SCREEN_H/2) - (imgHeight/2);
			//clear(screen);
			//stretch_blit(bmp, screenBuffer, 0, 0, bmp->w, bmp->h,imgX, imgY, imgWidth, imgHeight);
		}*/