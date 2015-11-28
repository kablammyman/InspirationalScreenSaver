#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <allegro.h>
#include <string>

//any class that wants to use buttons need to inherit this
class ButtonCallback
{
public:
	//return button ID
	virtual void buttonPressed(int x) =0;
};




class Button : public RenderObject
{

public:
	int id;
	short x, y,width, height;
	bool isPressed;
	bool isHighlighted;
	bool isToggleable;
	bool toggle;
	bool waitToRelease;
	std::string text[3];
	//array of bitmaps kept crashing :(
	BITMAP *img1;//first is button not pressed img, 2nd is pressed img
	BITMAP *img2;//first is button not pressed img, 2nd is pressed img
	
	Button(int id, short _x, short _y, short _w, short _h, std::string name1, std::string name2) : RenderObject(x, y, _w, _h)
	{
		init(id, _x, _y, _w, _h, name1, name2);
	}
	
	ButtonCallback *theCallBack; //this is the instance that will have the function we want to call
	void (ButtonCallback::*buttonPressed)(int); //this is the actual function to call(and what its signature will be)

	void init(int _id, short _x, short _y, short _w, short _h, std::string name1, std::string name2)
	{
		id = _id;
		x =_x;
		y =_y;
		width = _w;
		height = _h;
		text[0] = name1;
		text[1] = name2;
		text[2] = name1;

		isHighlighted = false;
		isPressed = false;
		isToggleable = false;
		toggle = false;
		waitToRelease = false;

		img1 = create_bitmap(_w, _h);
		img2 = create_bitmap(_w, _h);

		clear(img1);
		clear(img2);

		rectfill(img1, 0, 0, width, height, makecol(0,0,255));
		rectfill(img2, 0, 0, width, height, makecol(255,0,0));
	}
	bool mouseCollision(int mx, int my)
	{
		if((mx > x) && mx < (x+width) &&
		   (my > y) && my < (y+height))
		{
		   isHighlighted = true;
			return true;
		}
		isHighlighted = false;
		return false;
	}
	void draw(BITMAP *buffer)
	{
		if(isPressed)
		{
			draw_sprite(buffer,img2, x, y);
			if(isHighlighted)
				rect(buffer, x, y, x+width-1, y+height-1, makecol(100,100,100));
			textout_ex(img2, font, text[2].c_str(), 1, 1, makecol(255,255,255), 0);
		}
		else
		{
			draw_sprite(buffer,img1, x, y);
			if(isHighlighted)
				rect(buffer, x, y, x+width-1, y+height-1, makecol(100,100,100));
			textout_ex(img1, font, text[2].c_str(), 1, 1, makecol(255,255,255), 0);
		}
		
	}
	void buttonLogic(int x,int y, bool changeState)//change state basically means do or stop doing the button action
	{
		mouseCollision(x, y);
				
		if(isHighlighted)
		{
			if(changeState)
			{
				if(!waitToRelease)
					waitToRelease = true;
				isPressed = true;
				if(!isToggleable)
					text[2] = text[1];
			}
			else
			{
				if(waitToRelease)
				{
					waitToRelease = false;
					(theCallBack->*buttonPressed)(id);
					if(isToggleable)
					{
						if(toggle)
						{
							toggle = false;
							text[2] = text[0];
						}
						else
						{
							toggle = true;
							text[2] = text[1];
						}
					}//end toggble button
					else
						text[2] = text[0];
				}//end wait to release
			}
		}
		else
			isPressed = false;
	}
	//sued for toggle buttons when the state of program changes, and buttonsneed to reflect that
	void resetButton()
	{
		toggle = false;
		text[2] = text[0];
	}
};
#endif //MY_BUTTON_H