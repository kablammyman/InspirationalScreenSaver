#include "workoutTimer.h"
#include "mainApp.h"

WorkoutTimer::WorkoutTimer (int x, int y) : RenderObject(x,y,75,16)
{
	soundPlayed = false;
	timerOn = true;
	startElapsedTimer();
	sound = NULL;
}

WorkoutTimer::~WorkoutTimer()
{
	killSound();
}

void WorkoutTimer::killSound()
{
	if (sound != NULL)
	{
		delete sound;
		sound = NULL;
	}
}
//---------------------------------------------------------------------------------------	
void WorkoutTimer::loadSoundFile(const char* filePath)
{
	killSound();
	sound = new SoundProxy(filePath);
}
//---------------------------------------------------------------------------------------		
void WorkoutTimer::update()
{
	if(!timerOn)
		return;

	workoutTimer.updateStopWatch();

	if(sound != NULL && !soundPlayed && workoutTimer.timeOver)
	{
		sound->playSound();
		soundPlayed = true;
	}
}
//---------------------------------------------------------------------------------------		
void WorkoutTimer::pauseWorkoutTimer(bool shouldPause)
{
	timerOn = shouldPause;
	workoutTimer.pause = timerOn;
}
//---------------------------------------------------------------------------------------	
void WorkoutTimer::startElapsedTimer()
{
	workoutTimer.startElapsedTimer();
	timerOn = true;
	soundPlayed = false;
}
//---------------------------------------------------------------------------------------
void WorkoutTimer::startCountdownTimer()
{
	if(!workoutTimer.timeOver)
		timerOn = !timerOn;
	else
		timerOn = true;
	workoutTimer.startCountdown(MainApp::Instance()->min, MainApp::Instance()->sec, MainApp::Instance()->mil);
	soundPlayed = false;
	
}
//---------------------------------------------------------------------------------------
 void WorkoutTimer::draw(BITMAP *dest)
	{
		clear(bmp);
		textprintf_ex(bmp, font, 0, 0, makecol(255, 255, 255), 0, "%d:%d:%d", workoutTimer.minutes, workoutTimer.seconds, workoutTimer.decimals);

		//blit(bmp, dest, 0, 0, x, y, w, h); 
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h,x-100,y+30, bmp->w*2, bmp->h*2);
	}