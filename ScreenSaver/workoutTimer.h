#include "RenderController.h"
#include "StopWatch.h"
//#include "SoundProxy.h"

class WorkoutTimer : public RenderObject
{
	StopWatch workoutTimer;
	bool timerOn;
	//SoundProxy *sound;
	bool soundPlayed;
	void KillSound();
public: 
	WorkoutTimer (int x, int y);
	~WorkoutTimer();

	void LoadSoundFile(const char* filePath);

	void Update();
	void PauseWorkoutTimer(bool shouldPause);
	void StartCountdownTimer();
	void StartElapsedTimer();
	void Draw(PIXMAP *dest);
};
