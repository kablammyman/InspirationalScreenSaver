#include "optionScreen.h"
#include "GraphicsProxy.h"
#include "keyProxy.h"
#include "mainApp.h"

optionsScreen::optionsScreen() 
{
	caret  = 0;
	insert = true;
	iter = edittext.begin();
	enable_hardware_cursor();

	menu = new menu_class();
	menu->addMenuOption("toggle path info",(int)MainApp::Instance()->viewPathInfo);
	menu->addMenuOption("toggle clock",(int)MainApp::Instance()->viewClock);
	menu->addMenuOption("toggle workout timer",(int) MainApp::Instance()->viewWorkoutTimer);
	menu->addMenuOption("toggle image memory",(int)MainApp::Instance()->useImageMemory);
	menu->addMenuOption("image selection type", MainApp::Instance()->dirSelectionForDisplay);
	menu->addMenuOption("image display timer", MainApp::Instance()->imageDisplayTimeLength);
	menu->addMenuOption("num image to remember", MainApp::Instance()->imageMemAmt);

	menu->set_menu_positions(GraphicsProxy::getScreenWidth()/2, GraphicsProxy::getScreenHeight()/3, 25, makecol(255, 255, 255), makecol(0, 255, 0));

	infoImg = new RenderObject(0,0,900,30);

	renderer.init(GraphicsProxy::getScreenWidth(), GraphicsProxy::getScreenHeight());
	//renderer.addToRenderList(infoImg);
	renderer.addToRenderList(menu);
}

optionsScreen::~optionsScreen()
{
	remove_mouse();
	disable_hardware_cursor();
}

void optionsScreen::draw()
{
	clear(infoImg->getBitmap());
      // output the string to the screen
      textout(infoImg->getBitmap(), font, edittext.c_str(), 0, 10, makecol(255,255,255));
 
      // output some stats using Allegro's printf functions
      textprintf(infoImg->getBitmap(), font,  0, 20, makecol(255,255,255), "length:   %d", edittext.length());
      textprintf(infoImg->getBitmap(), font,  0, 30, makecol(255,255,255), "capacity: %d", edittext.capacity());
      textprintf(infoImg->getBitmap(), font,  0, 40, makecol(255,255,255), "empty?:   %d", edittext.empty());
      if(insert)
         textout(infoImg->getBitmap(), font, "Inserting", 0, 50, makecol(255,255,255));
      else
         textout(infoImg->getBitmap(), font, "Replacing", 0, 50, makecol(255,255,255));
 
      // draw the caret
      vline(infoImg->getBitmap(), caret * 8, 8, 18, makecol(255,255,255));

	renderer.blitToScreen();
}
void optionsScreen::update()
{
	poll_mouse();
	menu->update();

      while(keypressed())
      {
         int  newkey   = readkey();
         char ASCII    = newkey & 0xff;
         char scancode = newkey >> 8;
 
         // a character key was pressed; add it to the string
         if(ASCII >= 32 && ASCII <= 126)
         {
            // add the new char, inserting or replacing as need be
            if(insert || iter == edittext.end())
               iter = edittext.insert(iter, ASCII);
            else
               edittext.replace(caret, 1, 1, ASCII);
 
            // increment both the caret and the iterator
            caret++;
            iter++;
         }
         // some other, "special" key was pressed; handle it here
         else
            switch(scancode)
            {
               case KEY_DEL:
                  if(iter != edittext.end()) iter = edittext.erase(iter);
               break;
 
               case KEY_BACKSPACE:
                  if(iter != edittext.begin())
                  {
                     caret--;
                     iter--;
                     iter = edittext.erase(iter);
                  }
               break;
 
               case KEY_RIGHT:
                  if(iter != edittext.end())   caret++, iter++;
               break;
 
               case KEY_LEFT:
                  if(iter != edittext.begin()) caret--, iter--;
               break;
 
               case KEY_INSERT:
                  if(insert) insert = 0; else insert = 1;
               break;
 
               default:
 
               break;
            }
      }
}

void menu_class::addMenuOption(string add_menu_option, int value)
{
	menuItems.push_back(make_pair(add_menu_option,value));
}


void menu_class::set_menu_positions(int _x, int _y, int _level_y, int text_color1, int text_color2)
{
	x = _x;
	y = _y;
	level_y = _level_y;
	font1_color = text_color1;
	font2_color = text_color2;
}

void menu_class::set_menu_delay(int time)
{
	if (wait_flag == true)
		delay--;

	if (delay <= 0)
	{
		wait_flag = false;
		delay = time;
	}
}

void menu_class::menu_up(void)
{
	if (menuItemIndex > 0)
	{
		if (!wait_flag)
		{
			menuItemIndex--;
			wait_flag = true;
		}
	}
}
void menu_class::menu_down(void)
{
	if (menuItemIndex < (int)menuItems.size() - 1)
	{
		if (!wait_flag)
		{
			menuItemIndex++;
			wait_flag = true;
		}
	}
}

void menu_class::menu_inc(void)
{
	if (!wait_flag)
	{
		menuItems[menuItemIndex].second++;
		wait_flag = true;
	}
}
void menu_class::menu_dec(void)
{
	if (!wait_flag)
	{
		menuItems[menuItemIndex].second--;
		wait_flag = true;
	}
}
int menu_class::set_boundries(int index, int low_num, int hi_num)
{
	if (menuItems[index].second <= low_num)
		menuItems[index].second = low_num;
	else if (menuItems[index].second >= hi_num)
		menuItems[index].second = hi_num;

	return menuItems[index].second;
}
int menu_class::setToggleBoundries(int index)
{
	if (menuItems[index].second <= 0)
		menuItems[index].second = 0;
	else menuItems[index].second = 1;

	return menuItems[index].second;
}

int menu_class::show_menu(DATAFILE *the_datafile, BITMAP *bmp, int da_font)
{
	text_mode(text_mode_type);
	if (the_datafile != NULL && da_font != -1)
	{
		for (int i = 0; i < (int)menuItems.size(); i++)
		{
			if (i == menuItemIndex)
				textout(bmp, (FONT*)the_datafile[da_font].dat, menuItems[i].first.c_str(), x, y + level_y * i, font1_color);
			else
				textout(bmp, (FONT*)the_datafile[da_font].dat, menuItems[i].first.c_str(), x, y + level_y * i, font2_color);
			if (menuItems[i].second >= 0)
				textprintf(bmp, (FONT*)the_datafile[da_font].dat, x + (font_size + (font_size*menuItems[i].first.size())), y + level_y * i, font1_color, "%d", menuItems[i].second);
		}
	}
	else
	{
		for (int i = 0; i < (int)menuItems.size(); i++)
		{
			if (i == menuItemIndex)
				textout(bmp, font, menuItems[i].first.c_str(), x, y + level_y * i, font1_color);
			else
				textout(bmp, font, menuItems[i].first.c_str(), x, y + level_y * i, font2_color);
			if (menuItems[i].second >= 0)
				textprintf(bmp, font, x + (font_size + (font_size*menuItems[i].first.size())), y + level_y * i, font1_color, "%d", menuItems[i].second);
		}
	}
	return menuItemIndex;
}
void menu_class::update()
{
	set_menu_delay(5);
	
	//i need to use the key proxy...i gotta improve it first tho
	if (key[KEY_UP])
	{
		while (key[KEY_UP]) {}//only do action once key is released
		menu_up();
	}

	else if (key[KEY_DOWN])
	{
		while (key[KEY_DOWN]) {}//only do action once key is released
		menu_down();
	}

	if (key[KEY_LEFT])
	{
		while (key[KEY_LEFT]) {}//only do action once key is released
		menu_dec();
	}

	else if (key[KEY_RIGHT])
	{
		while (key[KEY_RIGHT]) {}//only do action once key is released
		menu_inc();
	}
	
	MainApp::Instance()->viewPathInfo = setToggleBoundries(0);
	MainApp::Instance()->viewClock = setToggleBoundries(1); 
	MainApp::Instance()->viewWorkoutTimer = setToggleBoundries(2);
	MainApp::Instance()->useImageMemory = setToggleBoundries(3);
	MainApp::Instance()->dirSelectionForDisplay = set_boundries(4, 1, 3);
	MainApp::Instance()->imageDisplayTimeLength = set_boundries(5, 3, 99);
	MainApp::Instance()->imageMemAmt = set_boundries(6, 0, 100);
}

void menu_class::draw(BITMAP *dest)
{
	show_menu(NULL, dest, 0);
}
