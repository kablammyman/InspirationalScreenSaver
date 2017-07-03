
#include "StopWatch.h"

StopWatch::StopWatch()
{
	mil = new TimeUnit(0,99);
	sec = new TimeUnit(0,59);
	min = new TimeUnit(0,59); 
	hour = new TimeUnit(0,24);

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
void StopWatch::StartCountdown(int mins, int secs, int milli)
{  
	elapsedTimer = false;
	mil->unit = milli;
	sec->unit = secs;
	min->unit = mins;
	pause = false;
	mil->Dec(1);
	latestClockMilis = clock();
}
//---------------------------------------------------
void StopWatch::UpdateCountdown(int amt)
{  
	mil->Dec(amt);
}
//---------------------------------------------------
void StopWatch::UpdateStopWatch()
{  

	//double duration = (clock() - latestClockMilis) / (double)CLOCKS_PER_SEC;
	//latestClockMilis = (clock() - latestClockMilis) / (int)CLOCKS_PER_SEC;
	double duration = clock() - latestClockMilis;

	if(elapsedTimer)
		UpdateElapsedTime();
	else
		UpdateCountdown((int)duration);
	latestClockMilis = clock();
}
//---------------------------------------------------
bool StopWatch::IsTimeUp()
{  
	 if (mil->IsBottomedOut() && sec->IsBottomedOut() && min->IsBottomedOut() && hour->IsBottomedOut())
		return true;
	 return false;
}

int StopWatch::Convert_to_milliseconds(int _min, int _sec,int _dec)
{
   return (_min*60000)+(_sec*1000)+_dec; 
}
//---------------------------------------------------
void StopWatch::Convert_to_standard(int time, int &_min, int &_sec, int &_dec)
{
	_dec = time%99;
	int x = time/99;
	_min = x/60;
	_sec = x%60;
}

void StopWatch::ToString(char * outStr)
{

	outStr[0] = char('0' + (hour->unit/10));
	outStr[1] = char('0' + (hour->unit % 10));
	outStr[2] = ':';
	
	outStr[3] = char('0' + (min->unit / 10));
	outStr[4] = char('0' + (min->unit % 10));
	outStr[5] = ':';
	
	outStr[6] = char('0' + (sec->unit / 10));
	outStr[7] = char('0' + (sec->unit % 10));
	outStr[8] = ':';
	
	outStr[9] = char('0' + (mil->unit / 10));
	outStr[10] = char('0' + (mil->unit % 10));
	outStr[11] = '\0';

}