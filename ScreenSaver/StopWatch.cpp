
#include "StopWatch.h"

void StopWatch::UpdateMilli()
{
	end = time(NULL);
	milliSec = difftime(end, begin);
	/*hour = milliSec / 3600;
	
	long v = totsec % 3600;
	min = v / 60;
	sec = v % 60;
	*/
}

void StopWatch::StartElapsedTimer()
{  
	startMilli = milliSec;
	elapsedTimer = true;
	decimals = 0;
	seconds = 0;
	minutes = 0;
	pause = false;
	timeOver = false;
}
//---------------------------------------------------
void StopWatch::UpdateElapsedTime()
{  
	if(pause)
	{
		startMilli = milliSec;
		return;
	}
	if(milliSec >= (startMilli+99))
	{                             
		int updateAmt = milliSec - (startMilli+99);
		if(updateAmt > 99)//if more than a second passed by
		{
			int min,sec,dec;
			Convert_to_standard(updateAmt, min, sec, dec);
			decimals += dec;
			seconds += sec;
			minutes += min;
		}
		else
			decimals = updateAmt;             
		startMilli = milliSec;
		seconds++;
	}
	else
	{
		decimals++;
	}
	if(seconds >= 60)
	{                                                      
		seconds = 0;
		minutes++;                    
	}      
}

//---------------------------------------------------
void StopWatch::StartCountdown(int min, int sec, int milli)
{  
	startMilli = milliSec;
	elapsedTimer = false;
	decimals = milli;
	seconds = sec;
	minutes = min;

	if(decimals == 0)
	{
		if(seconds > 0)
			seconds--;
		else if(minutes > 0)
		{
			minutes--;
			seconds = 59;
		}
	}

	pause = false;
	timeOver = false;
	
}
//---------------------------------------------------
void StopWatch::UpdateCountdown()
{  
	if(pause)
	{
		startMilli = milliSec;
		return;
	}

	decimals = (startMilli+99) - milliSec;
	
	if(decimals <= 0)
	{                             
		if(minutes == 0 && seconds == 0)
		{
			decimals = 0;
			timeOver = true;
			return;
		}
		int updateAmt = milliSec - (startMilli+99);
		if(updateAmt > 99)//if more than a second passed by
		{
			int min,sec,dec;
			Convert_to_standard(updateAmt, min, sec, dec);
			decimals = dec;
			seconds -= sec;
			minutes -= min;
		}
		decimals = 0;
		bool secChange = false;

		if(minutes > 0 && seconds == 0)
		{
			minutes--;
			seconds = 59;
			secChange = true;
		}
		if(seconds > 0)
		{
			if(!secChange)//if we already modified the seconds, dont mod it again
				seconds--;
			startMilli = milliSec; 
		}
		if(seconds <= 0)
			seconds = 0;
		if(minutes <= 0)
			minutes = 0;
		
	}
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
	if(decimals <= 0 && seconds <= 0 && minutes <= 0)
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
	decimals += amt;
}
//---------------------------------------------------
void StopWatch::ToString(char * outStr)
{
	//return 2 digits for each time unit
	outStr[0] = char('0' + (hours / 10));
	outStr[1] = char('0' + (hours % 10));
	outStr[2] = ':';

	outStr[3] = char('0' + (minutes / 10));
	outStr[4] = char('0' + (minutes % 10));
	outStr[5] = ':';

	outStr[6] = char('0' + (seconds / 10));
	outStr[7] = char('0' + (seconds % 10));
	outStr[8] = ':';

	outStr[9] = char('0' + (decimals / 10));
	outStr[10] = char('0' + (decimals % 10));
	outStr[11] = '\0';

}