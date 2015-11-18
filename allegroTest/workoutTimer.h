#include "renderer.h"
#include "AllegroTimer.h"
#include "SoundProxy.h"

class WorkoutTimer : public renderObj
{
	AllegroTimer workoutTimer;
	bool timerOn;
	float min, sec,mil;
	SoundProxy *sound;
	bool soundPlayed;
public: 
	const char * soundFilePath;
	WorkoutTimer (int x, int y);
	
	void loadSoundFile(const char* filePath);

	virtual void update();
	void pauseWorkoutTimer();
	void startCountdownTimer();
	void startElapsedTimer();
	void draw(BITMAP *dest);
};
