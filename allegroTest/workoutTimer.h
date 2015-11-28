#include "renderer.h"
#include "AllegroTimer.h"
#include "SoundProxy.h"

class WorkoutTimer : public RenderObject
{
	AllegroTimer workoutTimer;
	bool timerOn;
	SoundProxy *sound;
	bool soundPlayed;
	void killSound();
public: 
	WorkoutTimer (int x, int y);
	~WorkoutTimer();

	void loadSoundFile(const char* filePath);

	void update();
	void pauseWorkoutTimer(bool shouldPause);
	void startCountdownTimer();
	void startElapsedTimer();
	void draw(BITMAP *dest);
};
