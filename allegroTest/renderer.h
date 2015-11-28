#ifndef RENDERER_H
#define RENDERER_H
#include <allegro.h>
#include <winalleg.h>


#include <string>
#include <vector>

#include "RenderObject.h"



class Renderer
{
	BITMAP*screenBuffer;
	int bufferWidth;
	int bufferHeight;
	//to avoid object slicing, the vector is full of pointers to RenderObject and dervied objs
	std::vector<RenderObject *> renderList;
	void drawAllRenderObjectsToBuffer();
	void killScreenBuffer();
public:
	void init(int sw, int sh);
	~Renderer();
	void addToRenderList(RenderObject *r);
	void blitToScreen(bool clearBuffer = true);
	BITMAP* getScreenBuffer();
	RenderObject * getRenderObject(size_t index);
	void updateAllRenderObjects();
	void resizeScreenBuffer(int screenW, int screenH);
};

#endif //RENDERER_H