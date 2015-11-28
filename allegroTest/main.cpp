#include <allegro.h>
#include <winalleg.h>


#include <string>
#include <vector>

#include "GraphicsProxy.h"
#include "myFileDirDll.h"
#include "ScreenSaver.h"
#include "optionScreen.h"
#include "renderer.h"
#include "stopWatchMain.h"

#include "mainApp.h"

//windows debugging symbols
//debug definitions are turned on with /D
//property pages -> c/c++-> Preprocessor Definitions -> /D turns on _DEBUG

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
	
	if(!GraphicsProxy::changeScreenRes(false,false,1280,1024))
	{
		exit(-1);
	}

	initAllegroTimer();
	
	MainApp::Instance()->initVars(filePathBase);
	MainApp::Instance()->readCFG();

	vector<Scene*> allScenes;

	Scene *curScreen;
	ScreenSaver screenSaver;
	optionsScreen options;
	StopWatchMain stopWatchScreen;

	allScenes.push_back(&screenSaver);
	allScenes.push_back(&options);
	allScenes.push_back(&stopWatchScreen);

	size_t sceneIndex = 0;

	curScreen = allScenes[sceneIndex];

	do//  all the looping begins here, duh
	{                                 
		while (speed_counter > 0)//this makes sure the game runs at a constant rate on any machine
		{
			if (key[KEY_ESC])  //this will exit you from the game...and the program as of now
				done = true;
			if (key[KEY_ALT] && key[KEY_ENTER])
			{
				while (key[KEY_ALT] && key[KEY_ENTER]) {}//only do action once key is released

				if(GraphicsProxy::isFullScreen())
					GraphicsProxy::changeScreenRes(false,false,1280,1024);
				else
					GraphicsProxy::changeScreenRes(true,true);

				curScreen->changeScreenSize(GraphicsProxy::getScreenWidth(), GraphicsProxy::getScreenHeight());
			}

			if (key[KEY_F2])
			{
				while (key[KEY_F2]) {}//only do action once key is released

				if (sceneIndex < (allScenes.size() - 1))
					sceneIndex++;
				else
					sceneIndex = 0;

				curScreen = allScenes[sceneIndex];
			}
			curScreen->update();
			speed_counter--;   //for constant rate

		}//end logic while loop
		curScreen->draw();	
		
		frame_counter++;  //update the fps
	} while (!done);

	
	return 0;
}
END_OF_MAIN()