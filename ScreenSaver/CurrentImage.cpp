#include "CurrentImage.h"
#include "mainApp.h"

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
	amt = 0.005f;
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
		bmp = nullptr;
	}

	//bmp = GraphicsProxy::loadJPEG(imageToLoad.c_str());
	if (!bmp)//sometimes the bmp fails to load, until i figure out why, ill just do this
	{
		bmp = 0;
		return;
	}
	imageTransition = true;
	int bw = bmp->w;
	int bh = bmp->h;
	if (bmp->w >= bmp->h)
		targetScaleFactor = float(screenStruct->screenW / bw);
	else
		targetScaleFactor = float(screenStruct->screenH / bh);
	//scale it to fit up whole screen with aspect ratio
	targetImgHeight = bmp->h * ((targetScaleFactor * 100) / 100) + 1;
	targetImgWidth = bmp->w  * ((targetScaleFactor * 100) / 100) + 1;

	//postion img in center of screen
	targetX = (screenStruct->screenW / 2) - (targetImgWidth / 2);
	targetY = (screenStruct->screenH / 2) - (targetImgHeight / 2);

	x = GetRandomNum(-(screenStruct->screenW / 2), (screenStruct->screenW));
	y = GetRandomNum(-(screenStruct->screenH / 2), (screenStruct->screenH));

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

	if (curImgWidth >= targetImgWidth)
		curImgWidth = targetImgWidth;

	if (curImgHeight >= targetImgHeight)
		curImgHeight = targetImgHeight;



	int curPos = x - targetX;

	x += (curPos - imgSpeed);
	/*if(curPos > imgSpeed+1)
	x -= imgSpeed;
	else if(curPos < imgSpeed)
	x += imgSpeed;
	else
	x = targetX;
	*/
	curPos = y - targetY;
	y += (curPos - imgSpeed);

	/*if(curPos > imgSpeed+1)
	y -= imgSpeed;
	else if(curPos < imgSpeed)
	y += imgSpeed;
	else
	y = targetY;*/


	if (scaleFactor >= targetScaleFactor && (abs(x - targetX) <= imgSpeed && abs(y - targetY) <= imgSpeed))
		imageTransition = false;

}
//---------------------------------------------------------------------------------------
void CurrentImage::Draw(PIXMAP *dest)
{
	/*if (!bmp)
	{
		

		textprintf_ex(dest, font, dest->w / 4, (dest->h / 2) + 10, makecol(255, 255, 255), 0, "Error loading %s", curImagePath.c_str());
		return;
	}
	
	if (noImages)
	{
		textprintf_ex(dest, font, dest->w / 4, (dest->h / 2) + 10, makecol(255, 255, 255), 0, "NO IMAGES IN %s, Check your cfg file", mainApp->mainWorkingPath.c_str());
		return;
	}*/
	/*if (imageTransition)
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h, x, y, (int)curImgWidth, (int)curImgHeight);
	else
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h, targetX, targetY, targetImgWidth, targetImgHeight);*/
}
//---------------------------------------------------------------------------------------
int CurrentImage::GetRandomNum(int min, int max)
{
	//if(rand()%10 > 5)
	{
		int diff = ((max - min) + 1);
		return ((diff * rand()) / RAND_MAX) + min;
	}
	//return rand()%max + min;
}
//---------------------------------------------------------------------------------------
void CurrentImage::NoImageMessage()
{
	noImages = true;
}