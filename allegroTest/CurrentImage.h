#pragma once

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
	int getRandomNum(int min, int max);
public:
	bool imageTransition;
	virtual void update();
	CurrentImage();
	void noImageMessage();
	void loadImage(std::string imageToLoad);
	virtual void draw(BITMAP *dest);
};

class AppLegend : public RenderObject
{
public:
	AppLegend(int x, int y) : RenderObject(x, y, 200, 150)
	{
		textprintf_ex(bmp, font, 0, 0, makecol(255, 255, 255), 0, "RIGHT: change image");
		textprintf_ex(bmp, font, 0, 10, makecol(255, 255, 255), 0, "UP: toggle elapsed timer");
		textprintf_ex(bmp, font, 0, 20, makecol(255, 255, 255), 0, "DOWN: toggle countdown timer");
		textprintf_ex(bmp, font, 0, 30, makecol(255, 255, 255), 0, "I: delete image");
		textprintf_ex(bmp, font, 0, 40, makecol(255, 255, 255), 0, "G: delete gallery");
		textprintf_ex(bmp, font, 0, 50, makecol(255, 255, 255), 0, "S: stop backgroudn deletes");
		textprintf_ex(bmp, font, 0, 60, makecol(255, 255, 255), 0, "L: toggle legend");
		textprintf_ex(bmp, font, 0, 70, makecol(255, 255, 255), 0, "Esc: quits");
	}

};