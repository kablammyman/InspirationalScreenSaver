#include "CurrentImage.h"
#include "mainApp.h"
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
		delete bmp;
		bmp = nullptr;
	}


	int bw;
	int bh;
	int bpp;
	unsigned char* imgData = stbi_load(imageToLoad.c_str(), &bw, &bh, &bpp, 4);
	if (!imgData)
	{
		return;
	}
	bmp = new PIXMAP(imgData,bw,bh);
	//once the data ahs been copied into our class, get rid of raw data
	stbi_image_free(imgData);

	if (!bmp)//sometimes the bmp fails to load, until i figure out why, ill just do this
	{	
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

	x = GetRandomNum(-(screenStruct->screenW / 2), (screenStruct->screenW));
	y = GetRandomNum(-(screenStruct->screenH / 2), (screenStruct->screenH));
	scaleFactor = 0;
	test = 0;
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
	{
		bmp->DrawScaledCopy(dest, x, y, (unsigned int)curImgWidth, (unsigned int)curImgHeight);
		//bmp->Blit(dest, x, y);
		//test++;
		//if(test > 15)
		//imageTransition = false;
	}
		//font.Draw(dest, "Doing a cool transition!!!", dest->w / 4, (dest->h / 2) + 10);
		//stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h, x, y, (int)curImgWidth, (int)curImgHeight);
	else
		//bmp->DrawScaledCopy(dest, x, y, (unsigned int)curImgWidth, (unsigned int)curImgHeight);
		//bmp->Blit(dest,x,y);
		bmp->DrawScaledCopy(dest, x, y, targetImgWidth, targetImgHeight);
		//stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h, targetX, targetY, targetImgWidth, targetImgHeight);*/
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