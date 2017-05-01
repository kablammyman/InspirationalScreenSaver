#pragma once

#include <cmath>

struct TimeUnit
{
	//reset is a time we enter
	int min,max, reset;
	int unit;
	
	TimeUnit *next;
	TimeUnit *prev;
	TimeUnit(int m, int n)
	{
		min = m;
		max = n;
	}
	void Inc(int amt)
	{
		unit += amt;
		if (unit > max+1)
		{
			//make this a loop in case its overa time unit
			unit -= max;
			if(next != NULL)
				next->Inc(1);
			else unit = max;
		}
		else if(unit == max)
		{
			unit = min;
			if (next != NULL)
				next->Inc(1);
			else unit = max;
		}
		
	}

	void Dec(int amt)
	{
		unit -= amt;
		if (unit < min)
		{
			unit = max - abs(unit);
			if (prev != NULL)
				prev->Dec(1);
			else unit = min;
		}
		else if (unit == min)
		{
			unit = max;
			if (prev != NULL)
				prev->Dec(1);
			else unit = min;
		}
	}
};
struct StopWatch
{
	
	// decimals, seconds, minutes, hours;	
	TimeUnit *mil;

	bool elapsedTimer;

	bool pause;
	bool timeOver;

	StopWatch();


	void StartElapsedTimer();
	void StartCountdown(int min, int sec, int milli);
	void UpdateElapsedTime();
	void UpdateCountdown();
	void UpdateStopWatch();
	bool IsTimeUp();
	void Convert_to_standard(int time, int &min, int &sec, int &dec);
	int Convert_to_milliseconds(int min, int sec,int dec);
};
