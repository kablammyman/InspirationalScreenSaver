#include "CurrentImage.h"
#include "GraphicsProxy.h"

CurrentImage::CurrentImage() : RenderObject(0, 0, 200, 200)
{
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
void CurrentImage::loadImage(std::string imageToLoad)
{
	targetScaleFactor = 1.0f;
	targetImgWidth = 0, targetImgHeight = 0;
	curImagePath = imageToLoad;

	//release mem from prev image
	if (bmp)
		destroy_bitmap(bmp);

	bmp = GraphicsProxy::loadJPEG(imageToLoad.c_str());
	if (!bmp)//sometimes the bmp fails to load, until i figure out why, ill just do this
	{
		bmp = NULL;
		return;
	}
	imageTransition = true;
	float bw = bmp->w;
	float bh = bmp->h;
	if (bmp->w >= bmp->h)
		targetScaleFactor = float(GraphicsProxy::getScreenWidth() / bw);
	else
		targetScaleFactor = float(GraphicsProxy::getScreenHeight() / bh);
	//scale it to fit up whole screen with aspect ratio
	targetImgHeight = bmp->h * ((targetScaleFactor * 100) / 100) + 1;
	targetImgWidth = bmp->w  * ((targetScaleFactor * 100) / 100) + 1;

	//postion img in center of screen
	targetX = (GraphicsProxy::getScreenWidth() / 2) - (targetImgWidth / 2);
	targetY = (GraphicsProxy::getScreenHeight() / 2) - (targetImgHeight / 2);

	x = getRandomNum(-(GraphicsProxy::getScreenWidth() / 2), (GraphicsProxy::getScreenWidth()));
	y = getRandomNum(-(GraphicsProxy::getScreenHeight() / 2), (GraphicsProxy::getScreenHeight()));

	scaleFactor = 0;
}
//---------------------------------------------------------------------------------------
void CurrentImage::update()
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
void CurrentImage::draw(BITMAP *dest)
{
	if (!bmp)
	{
		textprintf_ex(dest, font, dest->w / 4, (dest->h / 2) + 10, makecol(255, 255, 255), 0, "Error loading %s", curImagePath.c_str());
		return;
	}
	
	if (imageTransition)
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h, x, y, (int)curImgWidth, (int)curImgHeight);
	else
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h, targetX, targetY, targetImgWidth, targetImgHeight);
}
//---------------------------------------------------------------------------------------
int CurrentImage::getRandomNum(int min, int max)
{
	//if(rand()%10 > 5)
	{
		int diff = ((max - min) + 1);
		return ((diff * rand()) / RAND_MAX) + min;
	}
	//return rand()%max + min;
}