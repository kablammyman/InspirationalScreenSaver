#ifndef ALLEGRO_PROXY_H
#define ALLEGRO_PROXY_H

#include <allegro.h>
//#include <alleggl.h>
#include <winalleg.h>
#include <jpgalleg.h>

class GraphicsProxy
{
	static bool fullScreen;
	static int screenWidth,screenHeight;

public:
	static void initGraphics();
	static void setColorDepth();
	static bool changeScreenRes(bool fullScreen, int sw = 0, int sh = 0);
	static bool getCompleteKeyPress(int k);
	static BITMAP* loadJPEG(const char * filePath);

	static int getScreenWidth();
	static int getScreenHeight();
	static bool isFullScreen();
};

#endif //ALLEGRO_PROXY_H