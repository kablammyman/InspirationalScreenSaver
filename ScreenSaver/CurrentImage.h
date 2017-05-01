#pragma once
#include "SDL_ScreenStruct.h"

#include "RenderObject.h"
#include <string>

class CurrentImage : public RenderObject
{
	int targetX, targetY;
	int imgSpeed;
	int delX;
	int delY;
	float amt;
	unsigned int  targetImgWidth, targetImgHeight;
	float scaleFactor;
	float curImgWidth, curImgHeight;
	float targetScaleFactor;
	bool noImages;
	std::string curImagePath;
	
	SDL_ScreenStruct *screenStruct;
	
	int GetRandomNum(int min, int max);
public:
	bool imageTransition;
	void Update();
	CurrentImage(SDL_ScreenStruct *ss);
	void NoImageMessage();
	void Load_Image(std::string imageToLoad);
	void Draw(PIXMAP *dest);
};

class AppLegend : public RenderObject
{
public:
	AppLegend(int x, int y) : RenderObject(x, y, 200, 150)
	{
		//VIC//textprintf_ex(bmp, font, 0, 0, makecol(255, 255, 255), 0, "RIGHT: change image");
		/*textprintf_ex(bmp, font, 0, 10, makecol(255, 255, 255), 0, "UP: toggle elapsed timer");
		textprintf_ex(bmp, font, 0, 20, makecol(255, 255, 255), 0, "DOWN: toggle countdown timer");
		textprintf_ex(bmp, font, 0, 30, makecol(255, 255, 255), 0, "I: delete image");
		textprintf_ex(bmp, font, 0, 40, makecol(255, 255, 255), 0, "G: delete gallery");
		textprintf_ex(bmp, font, 0, 50, makecol(255, 255, 255), 0, "S: stop backgroudn deletes");
		textprintf_ex(bmp, font, 0, 60, makecol(255, 255, 255), 0, "L: toggle legend");
		textprintf_ex(bmp, font, 0, 70, makecol(255, 255, 255), 0, "Esc: quits");*/
	}

};