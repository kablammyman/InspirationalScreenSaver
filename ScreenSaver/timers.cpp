
#include "timers.h"

volatile unsigned int speed_counter;
volatile unsigned int milliSec;
volatile int fps;
volatile int frame_counter;    
int decimals  = 0, seconds = 0, minutes = 0;
int dec_factor = 0, sec_factor = 0, min_factor = 0;


void fps_proc() //this counts frame rate
{
	fps = frame_counter;
	frame_counter = 0;
}

//---------------------------------------------------
void increment_speed_counter() 
{ 
	speed_counter++; 
}

//---------------------------------------------------
void inc_milliSec()
{
	milliSec++;
}

//---------------------------------------------------
void stopWatch::startElapsedTimer()
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
void stopWatch::updateElapsedTime()
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
			convert_to_standard(updateAmt, min, sec, dec);
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
void stopWatch::startCountdown(int min, int sec, int milli)
{  
	startMilli = milliSec;
	elapsedTimer = false;
	decimals = milli;
	seconds = sec;
	minutes = min;
	pause = false;
	timeOver = false;
	
}
//---------------------------------------------------
void stopWatch::updateCountdown()
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
			convert_to_standard(updateAmt, min, sec, dec);
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
void stopWatch::updateStopWatch()
{  
	if(elapsedTimer)
		updateElapsedTime();
	else
		updateCountdown();
}
//---------------------------------------------------
bool stopWatch::isTimeUp()
{  
	if(decimals <= 0 && seconds <= 0 && minutes <= 0)
		return true;
	return false;
}

int stopWatch::convert_to_milliseconds(int min, int sec,int dec)
{
   return (min*60000)+(sec*1000)+dec; 
}
//---------------------------------------------------
void stopWatch::convert_to_standard(int time, int &min, int &sec, int &dec)
{
	dec = time%99;
	int x = time/99;
	min = x/60;
	sec = x%60;
}

/*
void stopWatch::convert_to_standard(int time, int &min, int &sec, int &dec)
{
   dec = time%1000;
   int x = time/1000;
   min = x/60;
   sec = x%60;
}
*/
/*
//////////////////////////////////////////////////////////////////////////////
void stopWatch::updateCountdown()
{  
	
	if(decimals > 0)
		decimals--;
	if(milliSec >= (startMilli+99) )
	{                             
		if(seconds > 0)
		{
			startMilli = milliSec;
			decimals = 99;
			seconds--;             	
		}
	}

	if(seconds <= 0 && minutes >= 1)
	{                                                      
		seconds = 59;
		minutes--;                    
	}
}
1'1"78 = 61078 millsecs
/1000 = 61.078
/60 = 1.016
*/
//////////////////////////////////////////////////////////////////////////////