
#include "StopWatch.h"

StopWatch::StopWatch()
{
	mil = new TimeUnit(0,99);
	TimeUnit *sec = new TimeUnit(0,59);
	TimeUnit *min = new TimeUnit(0,59); 
	TimeUnit *hour = new TimeUnit(0,24);

	mil->next = sec;
	mil->prev = nullptr;

	sec->next = min;
	sec->prev = mil;

	min->next = hour;
	min->prev = sec;

	hour->next = nullptr;
	hour->prev = min;

}
//---------------------------------------------------
void StopWatch::StartElapsedTimer()
{  
	
}
//---------------------------------------------------
void StopWatch::UpdateElapsedTime()
{  
}

//---------------------------------------------------
void StopWatch::StartCountdown(int min, int sec, int milli)
{  
	//startMilli = milliSec;
	elapsedTimer = false;
	//decimals = milli;
	//seconds = sec;
	//minutes = min;
	pause = false;
	timeOver = false;
	
}
//---------------------------------------------------
void StopWatch::UpdateCountdown()
{  
}
//---------------------------------------------------
void StopWatch::UpdateStopWatch()
{  
	if(elapsedTimer)
		UpdateElapsedTime();
	else
		UpdateCountdown();
}
//---------------------------------------------------
bool StopWatch::IsTimeUp()
{  
	/*if(decimals <= 0 && seconds <= 0 && minutes <= 0)
		return true;
	return false;*/
	return true;
}

int StopWatch::Convert_to_milliseconds(int min, int sec,int dec)
{
   return (min*60000)+(sec*1000)+dec; 
}
//---------------------------------------------------
void StopWatch::Convert_to_standard(int time, int &min, int &sec, int &dec)
{
	dec = time%99;
	int x = time/99;
	min = x/60;
	sec = x%60;
}

