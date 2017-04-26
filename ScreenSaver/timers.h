#ifndef INC_TIMERS_H
#define INC_TIMERS_H

extern volatile unsigned int speed_counter;
extern volatile unsigned int milliSec;
extern volatile int fps;
extern volatile int frame_counter;

void fps_proc(); //this counts frame rate
void increment_speed_counter(); 
void inc_milliSec();

struct stopWatch
{
	int decimals, seconds, minutes;
	int dec_factor, sec_factor, min_factor;
	bool elapsedTimer;
	unsigned int startMilli;
	bool pause;
	bool timeOver;

	stopWatch()
	{
		decimals = seconds = minutes = 0;
		dec_factor = sec_factor = min_factor = 0;
		elapsedTimer = true;
		startMilli = milliSec;
	}

	void startElapsedTimer();
	void startCountdown(int min, int sec, int milli);
	void updateElapsedTime();
	void updateCountdown();
	void updateStopWatch();
	bool isTimeUp();
	void convert_to_standard(int time, int &min, int &sec, int &dec);
	int convert_to_milliseconds(int min, int sec,int dec);
};


#endif //INC_TIMERS_H

