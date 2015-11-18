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
};

#endif //SCENE_H