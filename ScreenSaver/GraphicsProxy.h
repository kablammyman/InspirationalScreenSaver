#ifndef ALLEGRO_PROXY_H
#define ALLEGRO_PROXY_H

#include "GraphicsPrimitives.h"

class GraphicsProxy
{
	static bool fullScreen;
	static int screenWidth,screenHeight;

public:
	static void initGraphics();
	static void setColorDepth();
	static bool changeScreenRes(bool fullScreen, bool useDesktopRes, int sw = 0, int sh = 0);
	static PIXMAP* loadJPEG(const char * filePath);

	static int getScreenWidth();
	static int getScreenHeight();
	static bool isFullScreen();
};

#endif //ALLEGRO_PROXY_H