#include "renderer.h"
#include "GraphicsProxy.h"
#include "AllegroTimer.h"
void Renderer::init(int sw, int sh)
{
	bufferWidth = sw;
	bufferHeight = sh;

	screenBuffer = create_bitmap(bufferWidth, bufferHeight);
	clear(screenBuffer);
}
//---------------------------------------------------------------------------------------
Renderer::~Renderer()
{
	//since we have a list of pointers, we have to delete those items ourslves. smart pointers would avoid this as extra step
	for(size_t i = 0; i < renderList.size(); i++)
		delete renderList[i];

	renderList.clear();
	killScreenBuffer();
}
//---------------------------------------------------------------------------------------
void Renderer::killScreenBuffer()
{
	if (screenBuffer)
	{
		destroy_bitmap(screenBuffer);
		screenBuffer = NULL;
	}
}
//---------------------------------------------------------------------------------------
void Renderer::addToRenderList(RenderObject *r)
{
	renderList.push_back(r);
}
//---------------------------------------------------------------------------------------
void Renderer::drawAllRenderObjectsToBuffer()
{
	for (size_t i = 0; i < renderList.size(); i++)
		renderList[i]->draw(screenBuffer);
}
//---------------------------------------------------------------------------------------
BITMAP* Renderer::getScreenBuffer()
{
	return screenBuffer;
}
//---------------------------------------------------------------------------------------
void Renderer::blitToScreen(bool clearBuffer)
{
	if(clearBuffer)
		clear(screenBuffer);
	
	drawAllRenderObjectsToBuffer();
	
	blit(screenBuffer, screen, 0, 0, 0, 0, bufferWidth, bufferHeight); //blit finial product to the screen, makes it slow but smooth
}
//---------------------------------------------------------------------------------------
RenderObject * Renderer::getRenderObject(size_t index)
{
    return renderList[index];
}
//---------------------------------------------------------------------------------------
void Renderer::updateAllRenderObjects()
{
	for(size_t i = 0; i < renderList.size(); i++)
	renderList[i]->update();
}
//---------------------------------------------------------------------------------------
void Renderer::resizeScreenBuffer(int screenW, int screenH)
{
	killScreenBuffer();
	init(screenW, screenH);
	drawAllRenderObjectsToBuffer();
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

		
			
			
			
		}	
}*/