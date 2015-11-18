
#ifndef ALLEGRO_INPUT_PROXY_H
#define ALLEGRO_INPUT_PROXY_H

#include <allegro.h>
//#include <alleggl.h>
#include <winalleg.h>


class AllegroKeys
{
private:
	static int curKeyPress;
public:
	static bool getKeyByAsciiCode(char ascii);
	static int getKeyByScanCode();
	static bool getCompleteKeyPress(int k);

};

#endif //ALLEGRO_INPUT_PROXY_H

