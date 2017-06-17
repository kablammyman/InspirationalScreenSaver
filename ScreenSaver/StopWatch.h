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
		unit += amt;
		if (unit > max+1)
		{
			//make this a loop in case its overa time unit
			unit -= max;
			if(next != nullptr)
				next->Inc(1);
			else unit = max;
		}
		else if(unit == max)
		{
			unit = min;
			if (next != nullptr)
				next->Inc(1);
			else unit = max;
		}
		
	}
	int GetNumUnitsElapsed(int amt)
	{
		int numLoops = 0;
		if (unit - amt < min)
		{
			numLoops++;
			unit = max-amt;
			while (amt > max)
			{
				amt -= max;
				numLoops++;
				unit = amt;
				
			}
		}
		else
		{
			unit -= amt;
		}
		return numLoops;
	}

	void Dec(int amt)
	{
		if (IsBottomedOut())
		{
			if(next == nullptr)
				return;
			else
			{
				if(next->IsBottomedOut())
					return;
			}
		}

		int numUnitsElapsed = GetNumUnitsElapsed(amt);
		if (numUnitsElapsed > 0)
		{
			if (next != nullptr)
			{
				if (next->IsBottomedOut())
				{
					unit = min;
					return;
				}
				else
					next->Dec(numUnitsElapsed);
			}
		}
	}

	bool IsBottomedOut()
	{
		return unit == min;
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
