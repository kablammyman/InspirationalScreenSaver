#include "workoutTimer.h"
#include "mainApp.h"

WorkoutTimer::WorkoutTimer (int x, int y) : RenderObject(x,y,75,16)
{
	soundPlayed = false;
	timerOn = true;
	StartElapsedTimer();
	sound = 0;
}

WorkoutTimer::~WorkoutTimer()
{
	KillSound();
}

void WorkoutTimer::KillSound()
{
	if (sound != 0)
	{
		delete sound;
		sound = 0;
	}
}
//---------------------------------------------------------------------------------------	
void WorkoutTimer::LoadSoundFile(const char* filePath)
{
	KillSound();
	sound = new SoundProxy(filePath);
}
//---------------------------------------------------------------------------------------		
void WorkoutTimer::Update()
{
	if(!timerOn)
		return;

	workoutTimer.UpdateStopWatch();

	if(sound != 0 && !soundPlayed && workoutTimer.timeOver)
	{
		sound->playSound();
		soundPlayed = true;
	}
}
//---------------------------------------------------------------------------------------		
void WorkoutTimer::PauseWorkoutTimer(bool shouldPause)
{
	timerOn = shouldPause;
	workoutTimer.pause = timerOn;
}
//---------------------------------------------------------------------------------------	
void WorkoutTimer::StartElapsedTimer()
{
	workoutTimer.startElapsedTimer();
	timerOn = true;
	soundPlayed = false;
}
//---------------------------------------------------------------------------------------
void WorkoutTimer::StartCountdownTimer()
{
	if(!workoutTimer.timeOver)
		timerOn = !timerOn;
	else
		timerOn = true;
	workoutTimer.startCountdown(MainApp::Instance()->min, MainApp::Instance()->sec, MainApp::Instance()->mil);
	soundPlayed = false;
	
}
//---------------------------------------------------------------------------------------
 void WorkoutTimer::Draw(PIXMAP *dest)
	{
		if (!MainApp::Instance()->viewWorkoutTimer)
			return;
		//VIC//clear(bmp);
		//VIC//textprintf_ex(bmp, font, 0, 0, makecol(255, 255, 255), 0, "%d:%d:%d", workoutTimer.minutes, workoutTimer.seconds, workoutTimer.decimals);

		//blit(bmp, dest, 0, 0, x, y, w, h); 
		//VIC//stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h,x-100,y+30, bmp->w*2, bmp->h*2);
	}