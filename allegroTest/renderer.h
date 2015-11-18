#ifndef RENDERER_H
#define RENDERER_H
#include <allegro.h>
#include <winalleg.h>


#include <string>
#include <vector>


class renderObj
{
protected:
	int x,y,w,h;
	BITMAP *bmp;
public:
	renderObj(){
		x = 0;y = 0;
		w = 0;h = 0;
		bmp = NULL;
	}
	renderObj(int _x, int _y, int _w, int _h)
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

		if(bmp == NULL)
		{
			bmp = create_bitmap(w, h);
			clear(bmp);
		}
		else
		{
			destroy_bitmap(bmp);
			bmp = NULL;
			bmp = create_bitmap(w, h);
			clear(bmp);
		}
	}
	~renderObj()
	{
		if(bmp)
		{
			destroy_bitmap(bmp);
			bmp = NULL;
		}
	}
	//rule of 3!
	//the copy ctor is needed since we will use vector.push_back...it copies the ob to its array, and destroys the original
	renderObj(const renderObj &obj)
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
	renderObj& operator=(renderObj other) {
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
	virtual void update(){}
};


class Renderer
{
	BITMAP*screenBuffer;
	int screenWidth; 
	int screenHeight;
	//to avoid object slicing, the vector is full of pointers to renderObj and dervied objs
	std::vector<renderObj *> renderList;
public:
	void init(int sw, int sh);
	~Renderer();
	void addToRenderList(renderObj *r);
	void update();
	void blitToScreen();
	renderObj * getRenderObj(size_t index);
};
class AppLegend : public renderObj
{
public:
	AppLegend (int x, int y) : renderObj(x, y, 200, 150)
	{
		textprintf_ex(bmp, font, 0, 0,  makecol(255,255,255), 0, "RIGHT: change image");
		textprintf_ex(bmp, font, 0, 10,  makecol(255,255,255), 0, "UP: toggle elapsed timer");
		textprintf_ex(bmp, font, 0, 20,  makecol(255,255,255), 0, "DOWN: toggle countdown timer");
		textprintf_ex(bmp, font, 0, 30,  makecol(255,255,255), 0, "I: delete image");
		textprintf_ex(bmp, font, 0, 40,  makecol(255,255,255), 0, "G: delete gallery");
		textprintf_ex(bmp, font, 0, 50,  makecol(255,255,255), 0, "S: stop backgroudn deletes");
		textprintf_ex(bmp, font, 0, 60,  makecol(255,255,255), 0, "L: toggle legend");
		textprintf_ex(bmp, font, 0, 70, makecol(255,255,255), 0, "Esc: quits");
	}
	//used for testing
	/*virtual void update(){ 
		x++;
	}*/

};


class CurrentImage : public renderObj
{
	int targetX, targetY;
	int imgSpeed;
	int delX;
	int delY;
	float amt;
	unsigned int  targetImgWidth, targetImgHeight;
	float scaleFactor;
	float curImgWidth, curImgHeight;
	float targetScaleFactor;

	std::string curImagePath;
	int getRandomNum(int min, int max);
public:
	int screenWidth,screenHeight;
	bool imageTransition;
	virtual void update();
	CurrentImage();
	void loadImage(std::string imageToLoad);
	virtual void draw(BITMAP *dest);
};


#endif //RENDERER_H