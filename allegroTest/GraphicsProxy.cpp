#include "GraphicsProxy.h"


int GraphicsProxy::screenWidth;
int GraphicsProxy::screenHeight;
bool GraphicsProxy::fullScreen;


void GraphicsProxy::initGraphics()
{
	allegro_init();
	//install_allegro_gl();
	install_keyboard();
	install_mouse();

	if(install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL) != 0)
		allegro_message("Error setting up Sound, so the game will be silent!\n%s\n", allegro_error);     
}


void GraphicsProxy::setColorDepth()
{
	//use same color depth as current desktop color depth
	int depth =  desktop_color_depth();
	if (depth != 0) 
         set_color_depth(depth);
	else
		alert("bad color depth", "couldnt set it", "Using defaults.","&Continue", NULL, 'c', 0);
}
//isFullScreen
bool GraphicsProxy::changeScreenRes(bool fs, int sw, int sh )
{

	fullScreen = fs;
	
#ifdef _DEBUG
	fullScreen = false;
#endif

	if (get_desktop_resolution(&screenWidth, &screenHeight) == 0)
	{
		int ret = 0;
		//property pages -> c/c++-> Preprocessor Definitions -> /D turns on _DEBUG
		if(!fullScreen)
		{
			ret=set_gfx_mode(GFX_AUTODETECT_WINDOWED,1280,1024,0,0); screenWidth = 1280; screenHeight = 1024;
			//let the program run in the background
			set_display_switch_mode(SWITCH_BACKGROUND);
		}
		else
		{
			if(sw > 0 && sh > 0)
			{
				screenWidth = sw;
				screenHeight = sh;
			}
			ret=set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,screenWidth,screenHeight,0,0);
			//let the program run in the background
			set_display_switch_mode(SWITCH_BACKAMNESIA);
		}

		if(ret!=0)
		{
			allegro_message(allegro_error);
			return false;
		}
	}
	return true;
}



//return true when key is pressed, then released	
bool GraphicsProxy::getCompleteKeyPress(int k)
{
	if(key[k])
	{
	while (key[k]) {}//only do action once key is released
		return true;
	}
	return false;
}


BITMAP* GraphicsProxy::loadJPEG(const char * imageToLoad)
{
	//release mem from prev image
	BITMAP *bmp;

	bmp = load_jpg(imageToLoad, NULL);
	if(!bmp)//sometimes the jpg fails to load, until i figure out why, ill just do this
		return NULL;

	return bmp;
}

 int GraphicsProxy::getScreenWidth()
 {
	 return screenWidth;
 }

 int GraphicsProxy::getScreenHeight()
 {
	 return screenHeight;
 }

bool GraphicsProxy::isFullScreen()
 {
	 return fullScreen;
 }