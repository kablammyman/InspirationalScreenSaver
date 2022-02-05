#include "workoutTimer.h"
#include "MainApp.h"
#include "Globals.h"

WorkoutTimer::WorkoutTimer (int x, int y) : RenderObject(x,y,100,16)
{
	soundPlayed = false;
	timerOn = false;
	StartElapsedTimer();
	sound = nullptr;
	this->x -= xOff;
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
		if (!timerOn)
			return;
	/*	bmp->Clear();
		font.Draw(bmp, workoutTimer.ToString(), 0, 0);
		bmp->Blit(dest, x, y);*/

		font.Draw(dest, workoutTimer.ToString(), x, y);
	}
