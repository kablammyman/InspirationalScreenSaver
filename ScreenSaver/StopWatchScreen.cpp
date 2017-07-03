

#include <algorithm>

#include <ctime> 
#include <string>

#include "MainApp.h"

#include "StopWatchScreen.h"
#include <sys/stat.h>


using namespace std;
StopWatchScreen::StopWatchScreen()
{
	done = false;
	timeOver = false;//used to know when to play time over sound

	int screenWidth = GraphicsProxy::getScreenWidth();  
	int screenHeight = GraphicsProxy::getScreenHeight();

	

	infoImg = new RenderObject(0, 0, 900, 30);
	timer = new RenderObject((screenWidth / 2), (screenHeight / 4), 900, 200);

	string fontFile = MainApp::Instance()->filePathBase + "\\gothicHeavy.pcx";
	myFont = load_font(fontFile.c_str(), palette, 0);
	if (!myFont)
	{
		string errorString = ("couldnt load font: " + fontFile);
		MainApp::Instance()->writeToLogFile(errorString);
		myFont = font;
	}

	sound = new SoundProxy(MainApp::Instance()->sndFile.c_str());

	renderer.init(GraphicsProxy::getScreenWidth(), GraphicsProxy::getScreenHeight());
	renderer.addToRenderList(infoImg);
	renderer.addToRenderList(timer);

	int x = 200, y = 250;
	int w = 64, h = 32;
	int spacing = 80;


	Button *button1 = new Button(1, x, y, w, h, "m_up", "m_up");
	button1->theCallBack = this;
	button1->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button1);
	renderer.addToRenderList(button1);

	Button *button2 = new Button(2, x, y + (h + 2), w, h, "m_dn", "m_dn");
	button2->theCallBack = this;
	button2->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button2);
	renderer.addToRenderList(button2);

	Button *button3 = new Button(3, x + spacing, y, w, h, "s_up", "s_up");
	button3->theCallBack = this;
	button3->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button3);
	renderer.addToRenderList(button3);

	Button *button4 = new Button(4, x + spacing, y + (h + 2), w, h, "s_dn", "s_dn");
	button4->theCallBack = this;
	button4->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button4);
	renderer.addToRenderList(button4);

	Button *button5 = new Button(5, x + (spacing * 2), y, w, h, "n_up", "n_up");
	button5->theCallBack = this;
	button5->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button5);
	renderer.addToRenderList(button5);

	Button *button6 = new Button(6, x + (spacing * 2), y + (h + 2), w, h, "n_dn", "n_dn");
	button6->theCallBack = this;
	button6->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button6);
	renderer.addToRenderList(button6);

	Button *button7 = new Button(7, x, y + 100, w, h, "start", "pause");
	button7->theCallBack = this;
	button7->buttonPressed = &ButtonCallback::buttonPressed;
	button7->isToggleable = true;
	stopWatchButtons.push_back(button7);
	renderer.addToRenderList(button7);

	Button *button8 = new Button(8, x + spacing, y + 100, w, h, "reset", "reset");
	button8->theCallBack = this;
	button8->buttonPressed = &ButtonCallback::buttonPressed;
	stopWatchButtons.push_back(button8);
	renderer.addToRenderList(button8);

	Button *button9 = new Button(9, (x + spacing * 2), y + 100, w, h, "cntDn", "cntUp");
	button9->theCallBack = this;
	button9->buttonPressed = &ButtonCallback::buttonPressed;
	button9->isToggleable = true;
	stopWatchButtons.push_back(button9);
	renderer.addToRenderList(button9);

	workoutTimer.minutes = MainApp::Instance()->min;
	workoutTimer.seconds = MainApp::Instance()->sec;
	workoutTimer.decimals = MainApp::Instance()->mil;

	workoutTimer.elapsedTimer = false;
	workoutTimer.pause = true;

}

StopWatchScreen::~StopWatchScreen()
{
	remove_mouse();
	disable_hardware_cursor();
	destroy_font(myFont);
	delete sound;
}

void StopWatchScreen::UpdateScene()
{			
	poll_mouse();
	if(mouse_b & 1)
		mouseClicked = true;
	else
		mouseClicked = false;

	for(size_t i = 0; i < stopWatchButtons.size(); i++)
	{
		stopWatchButtons[i]->buttonLogic(mouse_x,mouse_y,mouseClicked);
	}
	
	if(key[KEY_UP])
	{
		while (key[KEY_UP]) {}//only do action once key is released
		workoutTimer.StartElapsedTimer();
		timeOver = false;
	}
	else if(key[KEY_DOWN])
	{
		while (key[KEY_DOWN]) {}
		workoutTimer.startCountdown(MainApp::Instance()->min, MainApp::Instance()->sec , MainApp::Instance()->mil);
		timeOver = false;
	}
		
	else if(key[KEY_SPACE])
	{
		while (key[KEY_SPACE]) {}//only do action once key is released
		start();
	}

	MainApp::Instance()->updateTime();		
	workoutTimer.updateStopWatch();

	if (sound && workoutTimer.timeOver == true && timeOver == false)
	{
		sound->playSound();
		timeOver = true;
		stopWatchButtons[6]->resetButton();
	}
}

void StopWatchScreen::DrawScene()
{
	//clear(infoImg->getBitmap());
	string fps = "fps: " + to_string(fps);
//	DrawTextOnScene(std::string text, int x, int y)
	font.Draw(infoImg->GetPIXMAP(),fps, 0, 10);
	font.Draw(infoImg->GetPIXMAP(), MainApp::Instance()->getTimeString(), 0, 30);

	//clear(timer->getBitmap());


	string timeString = to_string(workoutTimer.minutes)+ ":" +to_string( workoutTimer.seconds) +":" +to_string( workoutTimer.decimals);
	font.Draw(timer->GetPIXMAP(), timeString, 0, 0);

	//i need a way to interupt the drawin process so anything that is drawn directly to the screen buffer can get drawn at correct time
	show_mouse(renderer.getScreenBuffer());
	renderer.blitToScreen(false);
}

void StopWatchScreen::ButtonPressed(int id)
{
	switch (id)
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
	MainApp::Instance()->min += x;
	workoutTimer.minutes = MainApp::Instance()->min;
}
void StopWatchScreen::SubMin( int x)
{
	if (MainApp::Instance()->min > 0)
	{
		MainApp::Instance()->min -= x;
		workoutTimer.minutes = MainApp::Instance()->min;
	}
}
void StopWatchScreen::AddSec( int x)
{
	if (MainApp::Instance()->sec < 59)
		MainApp::Instance()->sec += x;
	else
		MainApp::Instance()->sec = 0;

	workoutTimer.seconds = MainApp::Instance()->sec;
}
void StopWatchScreen::SubSec( int x)
{
	if (MainApp::Instance()->sec > 0)
		MainApp::Instance()->sec -= x;
	else
		MainApp::Instance()->sec = 59;
		
	workoutTimer.seconds = MainApp::Instance()->sec;
	
}
void StopWatchScreen::AddMil( int x)
{
	if (MainApp::Instance()->mil < 99)
		MainApp::Instance()->mil += x;
	else
		MainApp::Instance()->mil = 0;

	workoutTimer.decimals = MainApp::Instance()->mil;
	
}
void StopWatchScreen::SubMil( int x)
{
	if (MainApp::Instance()->mil > 0)
		MainApp::Instance()->mil -= x;
	else
		MainApp::Instance()->mil = 99;

	workoutTimer.decimals = MainApp::Instance()->mil;
	
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
		MainApp::Instance()->min = workoutTimer.minutes;
		MainApp::Instance()->sec = workoutTimer.seconds;
		MainApp::Instance()->mil = workoutTimer.decimals;
	}
}


void StopWatchScreen::Reset()
{
	if (!workoutTimer.elapsedTimer)
	{
		workoutTimer.minutes = MainApp::Instance()->min;
		workoutTimer.seconds = MainApp::Instance()->sec; 
		workoutTimer.decimals = MainApp::Instance()->mil;
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
	reset();
}
