

#include <algorithm>

#include <ctime> 
#include <string>

#include "MainApp.h"
#include "Globals.h"
#include "StopWatchScreen.h"
#include <sys/stat.h>

//this is the screen where we just have a stop watch, and buttons to change values
using namespace std;
StopWatchScreen::StopWatchScreen(SDL_ScreenStruct *s)
{
	done = false;
	timeOver = false;//used to know when to play time over sound

	infoImg = new RenderObject(0, 0, 900, 30);
	timer = new RenderObject((s->screenW / 2), (s->screenH / 4), 900, 200);


	/*string fontFile = Globals::filePathBase + "\\gothicHeavy.pcx";
	myFont = load_font(fontFile.c_str(), palette, 0);
	if (!myFont)
	{
		string errorString = ("couldnt load font: " + fontFile);
		Globals::writeToLogFile(errorString);
		myFont = font;
	}

	sound = new SoundProxy(Globals::sndFile.c_str());
	*/
	
	InitRenderController(s->screenW, s->screenH);


	AddToRenderList(infoImg);
	AddToRenderList(timer);

	int x = 200, y = 250;
	int w = 64, h = 32;
	int spacing = 80;


	Button *button1 = new Button(1, x, y, w, h, "m_up", "m_up");
	button1->theCallBack = this;
	button1->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button1);
	AddToRenderList(button1);

	Button *button2 = new Button(2, x, y + (h + 2), w, h, "m_dn", "m_dn");
	button2->theCallBack = this;
	button2->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button2);
	AddToRenderList(button2);

	Button *button3 = new Button(3, x + spacing, y, w, h, "s_up", "s_up");
	button3->theCallBack = this;
	button3->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button3);
	AddToRenderList(button3);

	Button *button4 = new Button(4, x + spacing, y + (h + 2), w, h, "s_dn", "s_dn");
	button4->theCallBack = this;
	button4->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button4);
	AddToRenderList(button4);

	Button *button5 = new Button(5, x + (spacing * 2), y, w, h, "n_up", "n_up");
	button5->theCallBack = this;
	button5->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button5);
	AddToRenderList(button5);

	Button *button6 = new Button(6, x + (spacing * 2), y + (h + 2), w, h, "n_dn", "n_dn");
	button6->theCallBack = this;
	button6->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button6);
	AddToRenderList(button6);

	Button *button7 = new Button(7, x, y + 100, w, h, "start", "pause");
	button7->theCallBack = this;
	button7->buttonPressed = &ButtonCallback::buttonPressed;
	button7->isToggleable = true;
	stopWatchButtons.push_back(button7);
	AddToRenderList(button7);

	Button *button8 = new Button(8, x + spacing, y + 100, w, h, "reset", "reset");
	button8->theCallBack = this;
	button8->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button8);
	AddToRenderList(button8);

	Button *button9 = new Button(9, (x + spacing * 2), y + 100, w, h, "cntDn", "cntUp");
	button9->theCallBack = this;
	button9->buttonPressed = &ButtonCallback::buttonPressed;
	button9->isToggleable = true;
	stopWatchButtons.push_back(button9);
	AddToRenderList(button9);

	/*workoutTimer.minutes = Globals::min;
	workoutTimer.seconds = Globals::sec;
	workoutTimer.decimals = Globals::mil;*/

	workoutTimer.elapsedTimer = false;
	workoutTimer.pause = true;

}

StopWatchScreen::~StopWatchScreen()
{
	//delete sound;
}

void StopWatchScreen::UpdateScene()
{			
	//poll_mouse();
	if(mouse.button1)
		mouseClicked = true;
	else
		mouseClicked = false;

	for(size_t i = 0; i < stopWatchButtons.size(); i++)
	{
		stopWatchButtons[i]->ButtonLogic(mouse.x,mouse.y,mouseClicked);
	}
	
/*	if(key[KEY_UP])
	{
		while (key[KEY_UP]) {}//only do action once key is released
		workoutTimer.StartElapsedTimer();
		timeOver = false;
	}
	else if(key[KEY_DOWN])
	{
		while (key[KEY_DOWN]) {}
		workoutTimer.startCountdown(Globals::min, Globals::sec , Globals::mil);
		timeOver = false;
	}
		
	else if(key[KEY_SPACE])
	{
		while (key[KEY_SPACE]) {}//only do action once key is released
		start();
	}

	Globals::updateTime();		
	workoutTimer.updateStopWatch();

	if (sound && workoutTimer.timeOver == true && timeOver == false)
	{
		sound->playSound();
		timeOver = true;
		stopWatchButtons[6]->resetButton();
	}*/
}

void StopWatchScreen::DrawScene()
{
	ClearScreenBuffer();
	Scene::DrawScene();

	//string fpsString = "fps: " + to_string(fps);

	//font.Draw(infoImg->GetPIXMAP(),fps, 0, 10);
	//font.Draw(infoImg->GetPIXMAP(), Globals::getTimeString(), 0, 30);

	//clear(timer->getBitmap());


	workoutTimer.ToString(curTime);
	
	font.Draw(timer->GetPIXMAP(), curTime, 0, 0);

	//i need a way to interupt the drawin process so anything that is drawn directly to the screen buffer can get drawn at correct time
	//show_mouse(renderer.getScreenBuffer());
	
}

void StopWatchScreen::ButtonPressed(int _id)
{
	switch (_id)
	{
	case 1:
		AddMin(1);
		break;
	case 2:
		SubMin(1);
		break;
	case 3:
		AddSec(1);
		break;
	case 4:
		SubSec(1);
		break;
	case 5:
		AddMil(1);
		break;
	case 6:
		SubMil(1);
		break;
	case 7:
		Start();
		break;
	case 8:
		Reset();
		break;
	case 9:
		ToggleTimerType();
		break;
	}
}

double StopWatchScreen::convertSecondsToDays(double secs)
{
	//return secs/86400;
	double t = secs / 86400;
	return t;
	//1.15741
}

void StopWatchScreen::AddMin( int x)
{
	Globals::min += x;
	workoutTimer.minutes = Globals::min;
}
void StopWatchScreen::SubMin( int x)
{
	if (Globals::min > 0)
	{
		Globals::min -= x;
		workoutTimer.minutes = Globals::min;
	}
}
void StopWatchScreen::AddSec( int x)
{
	if (Globals::sec < 59)
		Globals::sec += x;
	else
		Globals::sec = 0;

	workoutTimer.seconds = Globals::sec;
}
void StopWatchScreen::SubSec( int x)
{
	if (Globals::sec > 0)
		Globals::sec -= x;
	else
		Globals::sec = 59;
		
	workoutTimer.seconds = Globals::sec;
	
}
void StopWatchScreen::AddMil( int x)
{
	if (Globals::mil < 99)
		Globals::mil += x;
	else
		Globals::mil = 0;

	workoutTimer.decimals = Globals::mil;
	
}
void StopWatchScreen::SubMil( int x)
{
	if (Globals::mil > 0)
		Globals::mil -= x;
	else
		Globals::mil = 99;

	workoutTimer.decimals = Globals::mil;
	
}
void StopWatchScreen::Start()
{
	workoutTimer.pause = !workoutTimer.pause;
	if (workoutTimer.decimals == 0)
	{
		if (workoutTimer.seconds > 1)
			workoutTimer.seconds--;
		else if (workoutTimer.minutes > 1)
		{
			workoutTimer.minutes--;
			workoutTimer.seconds = 59;
		}
	}
	//if we pause so we can change the timer, let the values be accurate
	if (workoutTimer.pause)
	{
		Globals::min = workoutTimer.minutes;
		Globals::sec = workoutTimer.seconds;
		Globals::mil = workoutTimer.decimals;
	}
}


void StopWatchScreen::Reset()
{
	if (!workoutTimer.elapsedTimer)
	{
		workoutTimer.minutes = Globals::min;
		workoutTimer.seconds = Globals::sec;
		workoutTimer.decimals = Globals::mil;
	}
	else
	{
		workoutTimer.minutes = 0;
		workoutTimer.seconds = 0;
		workoutTimer.decimals = 0;
	}
	workoutTimer.pause = true;
	workoutTimer.timeOver = false;
	timeOver = false;
}

void StopWatchScreen::ToggleTimerType()
{
	workoutTimer.elapsedTimer = !workoutTimer.elapsedTimer;
	Reset();
}
