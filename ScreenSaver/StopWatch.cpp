
#include "StopWatch.h"

void StopWatch::UpdateMilli()
{
	curTime = high_resolution_clock::now();
	time_span = curTime - start;

	milli = time_span.count();
}

void StopWatch::StartElapsedTimer()
{  
	start = high_resolution_clock::now();
	elapsedTimer = true;
	milli = 0;
	seconds = 0;
	minutes = 0;
	pause = false;
	timeOver = false;
}
//---------------------------------------------------
void StopWatch::UpdateElapsedTime()
{  
	//this used to work becasue it would just take the updated amount of time, and "add" it to the curren time
	//and if the ipdated time diff is always 0, then it would add 0 to the current time, meaning no change.
	if(pause)
	{
		return;
	}
	
}

//---------------------------------------------------
void StopWatch::StartCountdown(int min, int sec, int _milli)
{  
	start = high_resolution_clock::now();
	elapsedTimer = false;
	milli = milli;
	seconds = sec;
	minutes = min;
	pause = false;
	timeOver = false;
}
//---------------------------------------------------
void StopWatch::UpdateCountdown()
{  
	if(pause)
	{
		return;
	}

}
//---------------------------------------------------
void StopWatch::UpdateStopWatch()
{  
	UpdateMilli();

	if(elapsedTimer)
		UpdateElapsedTime();
	else
		UpdateCountdown();
}
//---------------------------------------------------
bool StopWatch::IsTimeUp()
{  
	if(milli <= 0 && seconds <= 0 && minutes <= 0)
		return true;
	return false;
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

void StopWatch::ConvertMilliToTimePieces()
{
	dispHours = (milli / 3600000);//thats 5 zeros!
	over = (milli % 3600000);
	dispMinutes = (over / 60000);
	over = (over % 60000);
	dispSeconds = over / 1000;
	dispMilli = over % 1000;
}
//---------------------------------------------------
void StopWatch::AddToMins(int amt)
{
	minutes += amt;
}
//---------------------------------------------------
void StopWatch::AddToSecs(int amt)
{
	seconds += amt;
}
//---------------------------------------------------
void StopWatch::AddToMils(int amt)
{
	milli += amt;
}
//---------------------------------------------------
void StopWatch::ToString(char * outStr)
{
	//return 2 digits for each time unit
	outStr[0] = char('0' + (dispHours / 10));
	outStr[1] = char('0' + (dispHours % 10));
	outStr[2] = ':';

	outStr[3] = char('0' + (dispMinutes / 10));
	outStr[4] = char('0' + (dispMinutes % 10));
	outStr[5] = ':';

	outStr[6] = char('0' + (dispSeconds / 10));
	outStr[7] = char('0' + (dispSeconds % 10));
	outStr[8] = ':';

	outStr[9] = char('0' + (milli / 10));
	outStr[10] = char('0' + (milli % 10));
	outStr[11] = '\0';

}