#pragma once
#include   <time.h>
//we can use this to verify the setup was done. right now, no checks are in place

//to make sure the allegro timer stuff gets done, we will make the user call this method


class StopWatch
{
private:
	time_t begin, end;
	long elapsedTimeSinceLast;
	unsigned int milliSec;
	void UpdateMilli();
public:
	int decimals, seconds, minutes,hours;
	int dec_factor, sec_factor, min_factor;
	bool elapsedTimer;
	unsigned int startMilli;
	bool pause;
	bool timeOver;

	StopWatch()
	{
		hours = 0;
		decimals = seconds = minutes = 0;
		dec_factor = sec_factor = min_factor = 0;
		elapsedTimer = true;
		startMilli = milliSec;
	}
	void ToString(char *outStr);
	void StartElapsedTimer();
	void StartCountdown(int min, int sec, int milli);
	void UpdateElapsedTime();
	void UpdateCountdown();
	void UpdateStopWatch();
	bool IsTimeUp();
	void Convert_to_standard(int time, int &min, int &sec, int &dec);
	int Convert_to_milliseconds(int min, int sec,int dec);
	void AddToMins(int amt);
	void AddToSecs(int amt);
	void AddToMils(int amt);
};