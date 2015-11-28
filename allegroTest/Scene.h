#ifndef SCENE_H
#define SCENE_H

#include "renderer.h"

class Scene
{
protected:
	Renderer renderer;
	
public:
	virtual void update() {}
	virtual void draw() {}
	virtual void changeScreenSize(int screenW, int screenH)
	{
		renderer.resizeScreenBuffer(screenW, screenH);
	}
};

#endif //SCENE_H