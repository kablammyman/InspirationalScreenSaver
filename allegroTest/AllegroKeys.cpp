#include "AllegroKeys.h"

int AllegroKeys::curKeyPress;

bool AllegroKeys::getKeyByAsciiCode(char ascii)
{
	if(keypressed()) 
	{
	curKeyPress = readkey();
	  return ((curKeyPress & 0xff) == ascii);
	}
	return false;

      /*if ((curKeyPress & 0xff) == 'd')     // by ASCII code 
	 allegro_message("You pressed 'd'\n");*/
}
int AllegroKeys::getKeyByScanCode()
{
	if(keypressed()) 
	{
		curKeyPress = readkey(); 
		clear_keybuf();
		return curKeyPress >> 8;
	}
	return -1;
}
bool AllegroKeys::getCompleteKeyPress(int k)
{
	if(key[KEY_ALT] && key[KEY_ENTER])
	{
		while (key[KEY_ALT] && key[KEY_ENTER]) {}//only do action once key is released
			allegro_message("You pressed 'd'\n");
	}

	 if ((curKeyPress & 0xff) == 3)       /* ctrl+letter */
	 allegro_message("You pressed Control+C\n");



      if (curKeyPress == (KEY_X << 8))     /* alt+letter */
	 allegro_message("You pressed Alt+X\n");
	  
	  return true;
}
	
