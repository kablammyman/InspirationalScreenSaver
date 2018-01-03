#pragma once

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std::chrono;

class StopWatch
{
private:
	high_resolution_clock::time_point start; 
	high_resolution_clock::time_point curTime;
	duration<double, std::milli> time_span;
	float seconds,minutes,hours;
	unsigned long over,milli;//used in conversion process
	void UpdateMilli();
public:
	//the vars hold what we will display on screen
	int dispMilli, dispSeconds, dispMinutes,dispHours;
	bool elapsedTimer;
	unsigned int startMilli;
	bool pause;
	bool timeOver;

	StopWatch()
	{
		dispMilli = dispSeconds = dispMinutes = dispHours = 0;
		elapsedTimer = true;
		startMilli = 0;
	}
	void ConvertMilliToTimePieces();
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