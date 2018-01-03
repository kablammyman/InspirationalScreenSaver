#include "workoutTimer.h"
#include "mainApp.h"
#include "Globals.h"

WorkoutTimer::WorkoutTimer (int x, int y) : RenderObject(x,y,75,16)
{
	soundPlayed = false;
	timerOn = true;
	StartElapsedTimer();
	sound = nullptr;
}

WorkoutTimer::~WorkoutTimer()
{
	KillSound();
}

void WorkoutTimer::KillSound()
{
	if (sound != nullptr)
	{
		delete sound;
		sound = nullptr;
	}
}
//---------------------------------------------------------------------------------------	
void WorkoutTimer::LoadSoundFile(const char* filePath)
{
	KillSound();
	sound = new SoundUtils(filePath);
}
//---------------------------------------------------------------------------------------		
void WorkoutTimer::Update()
{
	if(!timerOn)
		return;

	workoutTimer.UpdateStopWatch();

	if(sound != 0 && !soundPlayed && workoutTimer.timeOver)
	{
		sound->PlaySound();
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
	workoutTimer.StartElapsedTimer();
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
	workoutTimer.StartCountdown(Globals::min, Globals::sec, Globals::mil);
	soundPlayed = false;
	
}
//---------------------------------------------------------------------------------------
 void WorkoutTimer::Draw(PIXMAP *dest)
	{
		if (!Globals::viewWorkoutTimer)
			return;
		//VIC//clear(bmp);
		//VIC//textprintf_ex(bmp, font, 0, 0, makecol(255, 255, 255), 0, "%d:%d:%d", workoutTimer.minutes, workoutTimer.seconds, workoutTimer.decimals);

		//blit(bmp, dest, 0, 0, x, y, w, h); 
		//VIC//stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h,x-100,y+30, bmp->w*2, bmp->h*2);
	}