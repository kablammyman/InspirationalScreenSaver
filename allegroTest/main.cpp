#include <allegro.h>
#include <winalleg.h>

#include <sys/stat.h>


#include <string>
#include <vector>
#include <stdio.h>

#include "GraphicsProxy.h"
#include "WindowsFiles.h"
#include "mainApp.h"
#include "optionScreen.h"
#include "renderer.h"



//windows debugging symbols
//debug definitions are turned on with /D

using namespace std;




int main(int argc, char* argv[])
{
	
	string temp = argv[0];
	string filePath;
	int found = temp.find_last_of("/\\");
	bool done = false;

	string filePathBase = temp.substr(0,found);

	GraphicsProxy::initGraphics();
	GraphicsProxy::setColorDepth();
	
	if(!GraphicsProxy::changeScreenRes(true))
	{
		exit(-1);
	}

	initAllegroTimer();


	Scene *curScreen;
	mainApp app;
	optionsScreen options;

	app.readCFG(filePathBase);		
	
	curScreen = &app;

	do//  all the looping begins here, duh
	{                                 
		while (speed_counter > 0)//this makes sure the game runs at a constant rate on any machine
		{
			if (key[KEY_ESC])  //this will exit you from the game...and the program as of now
				done = true;

			curScreen->update();
			speed_counter--;   //for constant rate

		}//end logic while loop
		curScreen->draw();	
		
		frame_counter++;  //update the fps
	} while (!done);

	
	return 0;
}
END_OF_MAIN()