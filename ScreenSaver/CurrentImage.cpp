#include "CurrentImage.h"
#include "MainApp.h"
#include "Globals.h"
#include <random>
#include "stb_image.h"
CurrentImage::CurrentImage(SDL_ScreenStruct *ss) : RenderObject(0, 0, 200, 200)
{
	screenStruct = ss;
	targetX = 0, targetY = 0;
	imgSpeed = 4;
	delX = 0;
	delY = 0;
	targetImgWidth = 0, targetImgHeight = 0;
	scaleFactor = 1.0f;
	curImgWidth = 0, curImgHeight = 0;

	targetScaleFactor = 1.0f;

	imageTransition = false;
	amt = 0.05f;
}
//---------------------------------------------------------------------------------------
void CurrentImage::Load_Image(std::string imageToLoad)
{
	noImages = false;
	targetScaleFactor = 1.0f;
	targetImgWidth = 0, targetImgHeight = 0;
	curImagePath = imageToLoad;

	//release mem from prev image
	if (bmp)
	{
		bmp->Destroy();
		delete bmp;
		bmp = nullptr;
	}

	int bw;
	int bh;
	int bpp;
	unsigned char* imgData = stbi_load(imageToLoad.c_str(), &bw, &bh, &bpp, 4);
	if (!imgData)
	{
		Globals::LogError("could not load image: "+ imageToLoad);
		return;
	}
	bmp = new PIXMAP(imgData,bw,bh);
	//once the data ahs been copied into our class, get rid of raw data
	stbi_image_free(imgData);

	if (!bmp)//sometimes the bmp fails to load, until i figure out why, ill just do this
	{
		Globals::LogError("bmp wasnt created even tho the image loaded for some reason..."+imageToLoad);
		bmp = nullptr;
		return;
	}
	imageTransition = true;

	if (bmp->w >= bmp->h)
		targetScaleFactor = float(screenStruct->screenW) / float(bw);
	else
		targetScaleFactor = float(screenStruct->screenH) / float( bh);
	//scale it to fit up whole screen with aspect ratio
	targetImgHeight = bmp->h * ((targetScaleFactor * 100) / 100) + 1;
	targetImgWidth = bmp->w  * ((targetScaleFactor * 100) / 100) + 1;

	//postion img in center of screen
	targetX = (screenStruct->screenW / 2) - (targetImgWidth / 2);
	targetY = (screenStruct->screenH / 2) - (targetImgHeight / 2);

	x = FileUtils::GetRandomInt(-(screenStruct->screenW / 2), (screenStruct->screenW));
	y = FileUtils::GetRandomInt(-(screenStruct->screenH / 2), (screenStruct->screenH));
	scaleFactor = 0;

}
//---------------------------------------------------------------------------------------
void CurrentImage::Update()
{
	if (!imageTransition)
		return;

	if (!bmp)
		return;

	if (scaleFactor < targetScaleFactor)
		scaleFactor += amt;
	else scaleFactor = targetScaleFactor;

	curImgHeight = bmp->h * scaleFactor;
	curImgWidth = bmp->w * scaleFactor;

	if (curImgWidth >= (float) targetImgWidth)
		curImgWidth = (float)targetImgWidth;

	if (curImgHeight >= (float)targetImgHeight)
		curImgHeight = (float)targetImgHeight;



	if(x < (targetX - imgSpeed))
		x += imgSpeed;
	else if (x > (targetX+imgSpeed))
		x -= imgSpeed;
	else x = targetX;

	if (y < (targetY - imgSpeed))
		y += imgSpeed;
	else if (y > (targetY + imgSpeed))
		y -= imgSpeed;
	else y = targetY;

	if (scaleFactor >= targetScaleFactor && (abs(x - targetX) <= imgSpeed && abs(y - targetY) <= imgSpeed))
		imageTransition = false;

}
//---------------------------------------------------------------------------------------
void CurrentImage::Draw(PIXMAP *dest)
{

	if (!bmp)
	{
		string msg = "Error loading " + curImagePath;
		font.Draw(dest, msg,dest->w / 4, (dest->h / 2) + 10 );
		return;
	}

	if (noImages)
	{
		string msg = "NO IMAGES IN MAIN WORKING PATH! Check the log file and your cfg file";
		font.Draw(dest, msg, dest->w / 8, (dest->h / 2) + 20);
		return;
	}
	if (imageTransition)
		bmp->DrawScaledCopy(dest, x, y, (unsigned int)curImgWidth, (unsigned int)curImgHeight);

	else
		bmp->DrawScaledCopy(dest, x, y, targetImgWidth, targetImgHeight);
}
//---------------------------------------------------------------------------------------
void CurrentImage::NoImageMessage()
{
	noImages = true;
}


string CurrentImage::GetDebugPosString()
{
	return "pos: " + to_string(x) + " x " + to_string(y);
}

string CurrentImage::GetDebugScaleString()
{
	return "scale: " + to_string(scaleFactor) + " " + to_string(round  (curImgWidth)) + " x " + to_string(round  (curImgHeight));
}

void DebugInfo::Draw(PIXMAP *dest)
{
	if ( !enabled || !bmp)
	{
		return;
	}
	/*
	* textprintf_ex(screenBuffer, font, 10, 10, makecol(255, 255, 255), 0, "scale: %f (%f x %f)", scaleFactor, imgWidth, imgHeight);

	textprintf_ex(dest, font, 10, 10,  makecol(255,255,255), 0, "x t:  (%d x %d)", x,y);
	textprintf_ex(dest, font, 10, 20,  makecol(255,255,255), 0, "tarX tarY: %f (%d x %d)",scaleFactor, targetX,targetY);
	textprintf_ex(screenBuffer, font, 10, 40, makecol(255, 255, 255), 0, "%s", filePath.c_str());
	textprintf_ex(screenBuffer, font, 10, 50, makecol(255, 255, 255), 0, "%s", asctime(timeinfo));
	*/
	bmp->Blit(dest, x, y);
	bmp->Clear();
}

void DebugInfo::Textout(int _x, int _y, string text)
{
	font.Draw(bmp, text, _x, _y);
}