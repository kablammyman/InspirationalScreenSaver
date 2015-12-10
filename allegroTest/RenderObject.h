#pragma once

#include <allegro.h>
#include <winalleg.h>

class RenderObject
{
protected:
	int x, y, w, h;
	BITMAP *bmp;
public:
	RenderObject() {
		x = 0; y = 0;
		w = 0; h = 0;
		bmp = NULL;
	}
	RenderObject(int _x, int _y, int _w, int _h)
	{
		bmp = NULL;
		init(_x, _y, _w, _h);
	}
	void init(int _x, int _y, int _w, int _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;

		if (bmp != NULL)
		{
			destroy_bitmap(bmp);
			bmp = NULL;
		}

		if (w < 1 || h < 1)
		{
			bmp = NULL;
			return;
		}
		bmp = create_bitmap(w, h);
		clear(bmp);
	}
	~RenderObject()
	{
		if (bmp)
		{
			destroy_bitmap(bmp);
			bmp = NULL;
		}
	}
	//rule of 3!
	//the copy ctor is needed since we will use vector.push_back...it copies the ob to its array, and destroys the original
	RenderObject(const RenderObject &obj)
	{
		x = obj.x;
		y = obj.y;
		w = obj.w;
		h = obj.h;
		bmp = create_bitmap(w, h);
		clear(bmp);
		//*bmp = *obj.bmp;// copy the value
		blit(obj.bmp, bmp, 0, 0, x, y, w, h); //this copies one bitmap to another
	}
	//the assignment is needed since we will use vector.push_back...it copies the ob to its array, and destroys the original
	RenderObject& operator=(RenderObject other) {
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;
		bmp = other.bmp;
		return *this;
	}
	BITMAP* getBitmap()
	{
		return bmp;
	}
	void setBitmap(BITMAP*b)
	{
		bmp = b;
		w = b->w;
		h = b->h;
	}
	virtual void draw(BITMAP *dest)
	{
		blit(bmp, dest, 0, 0, x, y, w, h);
		//stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h,dest->w-200,30, 300, 40);
	}
	void setX(int _x)
	{
		x = _x;
	}
	void setY(int _y)
	{
		y = _y;
	}
	virtual void update() {}
};
