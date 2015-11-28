#include "optionScreen.h"
#include "GraphicsProxy.h"
#include "keyProxy.h"


optionsScreen::optionsScreen()
{
	caret  = 0;
	insert = true;
	iter = edittext.begin();

	infoImg = new RenderObject(0,0,900,30);

	renderer.init(GraphicsProxy::getScreenWidth(), GraphicsProxy::getScreenHeight());
	renderer.addToRenderList(infoImg);
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