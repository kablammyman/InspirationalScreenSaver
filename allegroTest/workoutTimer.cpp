
#include "workoutTimer.h"

WorkoutTimer::WorkoutTimer (int x, int y) : renderObj(x,y,75,16)
{
	soundPlayed = false;
	timerOn = true;
	min = 2, sec = 55,mil = 99;
	startElapsedTimer();
}
//---------------------------------------------------------------------------------------	
void WorkoutTimer::loadSoundFile(const char* filePath)
{
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
	clear(bmp);
	textprintf_ex(bmp, font, 0, 0,  makecol(255,255,255), 0,"%d:%d:%d", workoutTimer.minutes,workoutTimer.seconds,workoutTimer.decimals);
}
//---------------------------------------------------------------------------------------		
void WorkoutTimer::pauseWorkoutTimer()
{
	if(timerOn)
		workoutTimer.pause = !workoutTimer.pause;
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
	workoutTimer.startCountdown(min,sec,mil);
	soundPlayed = false;
	
}
//---------------------------------------------------------------------------------------
 void WorkoutTimer::draw(BITMAP *dest)
	{
		//blit(bmp, dest, 0, 0, x, y, w, h); 
		stretch_blit(bmp, dest, 0, 0, bmp->w, bmp->h,x-100,y+30, bmp->w*2, bmp->h*2);
	}