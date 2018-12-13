#pragma once
#include <math.h>
#include "GraphicsPrimitives.h"
#include "Scene.h"
#include "Button.h"
#include "BitmapFont.h"
//#include "SoundProxy.h"

#include <vector>

using namespace std;
#include "SDL_ScreenStruct.h"
struct MouseProxy
{
	int x,y;
	bool button1,button2;
};
class StopWatchScreen : public Scene, public ButtonCallback
{
	bool done;
	bool mouseClicked;
	
	int sizeOfWav;
	int timerX, timerY;
	
	RenderObject *timer;
	RenderObject *infoImg;
	//SoundProxy *sound;
	//FONT *myFont;
	StockBitmapFont font;
	void ButtonPressed(int _id);
	vector<Button *> stopWatchButtons;
	MouseProxy mouse;
	string curTime;
public:

	bool timeOver;//used to know when to play time over sound
	StopWatch workoutTimer;
	void UpdateScene();
	void DrawScene();
	StopWatchScreen(SDL_ScreenStruct *s);
	~StopWatchScreen();
	double convertSecondsToDays(double secs);

	void AddMin(int x);
	void SubMin(int x);
	void AddSec( int x);
	void SubSec( int x);
	void AddMil( int x);
	void SubMil( int x);
	void Start();
	void Reset();
	void ToggleTimerType();
	 

};