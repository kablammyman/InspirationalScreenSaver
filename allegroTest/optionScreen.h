#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

#include "Scene.h"
using namespace std;
class optionsScreen : public Scene
{
	int     caret;                       // tracks the text caret
	bool    insert;                    // true of should text be inserted
	string  edittext;                         // an empty string for editting
	string::iterator iter; // string iterator
	RenderObject *infoImg;
public:
	
	optionsScreen();
	void draw();
	void update();
};

#endif //OPTIONS_H