#pragma once

#include <cmath>
#include <ctime>

struct TimeUnit
{
	//reset is a time we enter
	int min,max;
	int unit;
	
	TimeUnit *next;
	TimeUnit *prev;
	TimeUnit(int m, int n)
	{
		min = m;
		max = n;
		unit = min;
	}
	void Inc(int amt)
	{
		
	}

	//returns true if bottomed out
	bool Dec(int amt)
	{
		//if we are the last time unit, and we are alrady at zero, then the prev
		//unit should not reset
		if (IsBottomedOut() && next == nullptr)
		{
			return true;
		}
		//figure out how much time has passed between last go round
		int numUnitsElapsed = 0;
		if (unit - amt < min)
		{
		//how to get how many revs and remainder with divsion?

			if (next != nullptr)
			{			
				//if (numUnitsElapsed > 0)
				//	unit = min;

				if(next->Dec(numUnitsElapsed))
					unit = min;
			}
			else //at teh end of the list
			{
				return false;
			}
			
		}
		
		else
		{
			unit -= amt;
			return false;
		}
		return true;
	}

	bool IsBottomedOut()
	{
		return unit == min;
	}
	bool IsToppedOut()
	{
		return unit == max;
	}
	
};
struct StopWatch
{
	
	// decimals, seconds, minutes, hours;	
	TimeUnit *mil;
	TimeUnit *sec;
	TimeUnit *min;
	TimeUnit *hour;
	bool elapsedTimer;

	bool pause;
	bool timeOver;
	clock_t latestClockMilis;

	StopWatch();


	void StartElapsedTimer();
	void StartCountdown(int min, int sec, int milli);
	void UpdateElapsedTime();
	void UpdateCountdown(int amt);
	void UpdateStopWatch();
	bool IsTimeUp();
	void Convert_to_standard(int time, int &min, int &sec, int &dec);
	int Convert_to_milliseconds(int min, int sec,int dec);
	void ToString(char * outStr);
};
