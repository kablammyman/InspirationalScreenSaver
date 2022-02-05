#pragma once

#include "RenderController.h"
#include "StopWatch.h"
#include "SoundUtils.h"

class WorkoutTimer : public RenderObject
{
	StopWatch workoutTimer;
	bool timerOn;
	SoundUtils *sound;
	StockBitmapFont font;
	bool soundPlayed;
	
	void KillSound();
public: 
	int xOff = 200;
	//int yOff = 30;
	WorkoutTimer (int x, int y);
	~WorkoutTimer();

	void LoadSoundFile(const char* filePath);

	void Update();
	void PauseWorkoutTimer(bool shouldPause);
	void StartCountdownTimer();
	void StartElapsedTimer();
	void Draw(PIXMAP *dest);
};
