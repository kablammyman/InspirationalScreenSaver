#include "renderer.h"
#include "GraphicsProxy.h"
#include "AllegroTimer.h"
void Renderer::init(int sw, int sh)
{
	screenWidth = sw;
	screenHeight = sh;

	screenBuffer = create_bitmap(screenWidth, screenHeight);
	clear(screenBuffer);
}
//---------------------------------------------------------------------------------------
Renderer::~Renderer()
{
	//since we have a list of pointers, we have to delete those items ourslves. smart pointers would avoid this as extra step
	for(size_t i = 0; i < renderList.size(); i++)
		delete renderList[i];

	renderList.clear();
	if(screenBuffer)
	{
		destroy_bitmap(screenBuffer);
		screenBuffer = NULL;
	}
}
//---------------------------------------------------------------------------------------
void Renderer::addToRenderList(renderObj *r)
{
	renderList.push_back(r);
}
//---------------------------------------------------------------------------------------
void Renderer::blitToScreen()
{
	clear(screenBuffer);
	for(size_t i = 0; i < renderList.size(); i++)
		renderList[i]->draw(screenBuffer);
	
	blit(screenBuffer, screen, 0, 0, 0, 0, screenWidth, screenHeight); //blit finial product to the screen, makes it slow but smooth
}
//---------------------------------------------------------------------------------------
void Renderer::update()
{
	for(size_t i = 0; i < renderList.size(); i++)
		renderList[i]->update();
}
//---------------------------------------------------------------------------------------
renderObj * Renderer::getRenderObj(size_t index)
{
    return renderList[index];
}
//---------------------------------------------------------------------------------------
CurrentImage::CurrentImage() : renderObj(0,0, 200, 200)
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
	if(!bmp)//sometimes the bmp fails to load, until i figure out why, ill just do this
	{
		bmp = NULL;
		return;
	}
	imageTransition = true;
	float bw = bmp->w;
	float bh = bmp->h;	
	if(bmp->w >= bmp->h)
		targetScaleFactor = float(screenWidth / bw);
	else
		targetScaleFactor = float(screenHeight / bh);
	//scale it to fit up whole screen with aspect ratio
	targetImgHeight = bmp->h * ((targetScaleFactor*100) / 100)+1;
	targetImgWidth  = bmp->w  * ((targetScaleFactor*100) / 100)+1;

	//postion img in center of screen
	targetX = (screenWidth/2) - (targetImgWidth/2);
	targetY = (screenHeight/2) - (targetImgHeight/2);

	x = getRandomNum(-(screenWidth/2) ,(screenWidth) );
	y = getRandomNum(-(screenHeight/2) ,(screenHeight) );
	
	scaleFactor = 0;
}
//---------------------------------------------------------------------------------------
void CurrentImage::update()
{
	if(!imageTransition)
		return;

	if(!bmp)
		return;

	if(scaleFactor < targetScaleFactor) 
		scaleFactor+=amt;
	else scaleFactor = targetScaleFactor;

	curImgHeight = bmp->h * scaleFactor;
	curImgWidth  = bmp->w * scaleFactor;

	if(curImgWidth >= targetImgWidth)
		curImgWidth = targetImgWidth;

	if(curImgHeight >= targetImgHeight)
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


	if(scaleFactor >= targetScaleFactor && (abs(x - targetX) <= imgSpeed && abs(y - targetY) <= imgSpeed ))
		imageTransition = false;
	
}
//---------------------------------------------------------------------------------------
void CurrentImage::draw(BITMAP *dest) 
{
	if (!bmp)
	{
		textprintf_ex(dest, font, dest->w/4, (dest->h/2)+10,  makecol(255,255,255), 0, "Error loading %s",curImagePath.c_str());
		return;
	}
	//textprintf_ex(dest, font, 10, 10,  makecol(255,255,255), 0, "x t:  (%d x %d)", x,y);
	//textprintf_ex(dest, font, 10, 20,  makecol(255,255,255), 0, "tarX tarY: %f (%d x %d)",scaleFactor, targetX,targetY);

	if(imageTransition)			
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h,x, y, (int)curImgWidth, (int)curImgHeight);
	else
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h,targetX, targetY, targetImgWidth, targetImgHeight);		
}
//---------------------------------------------------------------------------------------
int CurrentImage::getRandomNum(int min, int max)
{
	//if(rand()%10 > 5)
	{
		int diff = ((max - min) + 1);
		return ((diff * rand())/RAND_MAX) + min;
	}
	//return rand()%max + min;
}


/*
void clearScreen()
{
	if(bmp)
	{
		destroy_bitmap(bmp);
		bmp = NULL;
	}
	clear(screen);
}


void dosomeSht()
{
	if(drawNewImage)
		{
			clear(screen);
			scaleFactor = 0.0f;
			imgWidth = 0, imgHeight = 0;
		}

		
			
			#ifdef _DEBUG
			textprintf_ex(screenBuffer, font, 10, 10,  makecol(255,255,255), 0, "scale: %f (%f x %f)",scaleFactor,imgWidth,imgHeight);
			textprintf_ex(screenBuffer, font, 10, 20,  makecol(255,255,255), 0, "%d:%d:%d", imageTimer.minutes,imageTimer.seconds,imageTimer.decimals);	
			#endif
			
			textprintf_ex(screenBuffer, font, 10, 40,  makecol(255,255,255), 0, "%s",filePath.c_str());
			textprintf_ex(screenBuffer, font, 10, 50,  makecol(255,255,255), 0,"%s", asctime (timeinfo));
			
		}	
}*/