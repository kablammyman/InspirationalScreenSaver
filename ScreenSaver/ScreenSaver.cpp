#ifdef _WIN32
#include <Windows.h> //GetLatError()
#endif

#include "ScreenSaver.h"

#include "keyProxy.h"
#include "mainApp.h"
#include "Globals.h"
#include <ctime>

ScreenSaver::ScreenSaver(SDL_ScreenStruct *s)
{
	ss = s;
	timerOn = false;
	showLegend = false;
	timeOver = false;

	folderNum = 0;
	

	//workoutTimer = new WorkoutTimer(ss->screenW - 100, 10);
	//workoutTimer->loadSoundFile(mainApp->sndFile.c_str());
	//workoutTimer->pauseWorkoutTimer(true);

	legend = new AppLegend(ss->screenW - 300,ss->screenH - 100);
	
	curImage = new CurrentImage(ss);

	renderer.Init(ss->screenW, ss->screenH);
	renderer.AddToRenderList(legend);
	renderer.AddToRenderList(curImage);
	//renderer.AddToRenderList(workoutTimer);
	SetCurImgObj(curImage);

	//imageSelector.Init(mainApp->numFoldersInBase);

	/*	switch(dirSelectionForDisplay)
	{
	case GET_RANDOM_FOLDERS:

	break;
	case GET_SEQUENTIAL_FOLDERS:

	break;
	//TODO: make it actually shuffled...stop being lazy, lol
	case GET_SHUFFLED_FOLDERS:

	break;
	}*/

	imageSelector.SetDisplayList(displayDirs);
	imageSelector.SetImageMemAmt(Globals::imageMemAmt);
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	logFile = fopen("myfile.txt", "w");
	fprintf(logFile, "\nCurrent local time and date: %s \n", asctime(timeinfo));
}
//---------------------------------------------------------------------------------------
void ScreenSaver::SetCurImgObj( CurrentImage *c)
{
	curImage = c;
}
//---------------------------------------------------------------------------------------
void ScreenSaver::ChangeScreenSize(int screenW, int screenH)
{
	Scene::ChangeScreenSize(screenW, screenH);
	//workoutTimer->setX( GraphicsProxy::getScreenWidth() - 100); 
	legend->SetX(ss->screenW - 300);
	legend->SetY(ss->screenH - 100);
}
//---------------------------------------------------------------------------------------
bool ScreenSaver::DoDelete(string path, string createDate)
{
	string lastError = "";
	if (createDate != "")
	{
		string delString = ("deleting: " + path + "created: " + createDate);
		WriteToLogFile(delString);
	}
	else
	{
		string delString = ("deleting: " + path);
		WriteToLogFile(delString);
	}
	
	int recycleErrorVal = 	FileUtils::Delete_File( path.c_str() );
	int permDeleteErrorVal = 0;
	if(recycleErrorVal > 0)//try to send to recycle bin failed
	{
		permDeleteErrorVal = FileUtils::Delete_File( path.c_str(),true );
		if(permDeleteErrorVal == 0)//cant send there, perm delete
		{
			lastError = FileUtils::DeleteAllFilesInDir( path.c_str() );
			if(lastError != "") //try to delete each file individually
			{
				string errorString = ("-------recycle error1: " + recycleErrorVal);
				WriteToLogFile(errorString);

				errorString = ("-------perm error: " + permDeleteErrorVal);
				WriteToLogFile(errorString);
#ifdef _WIN32
				errorString = ("-------GetLastError: " + GetLastError());
				WriteToLogFile(errorString);
#endif
				return false;
			}
		}
	}
	

	if(recycleErrorVal == 0)
		WriteToLogFile("-----sent to recycle");
	else if(permDeleteErrorVal > 0)
		WriteToLogFile("-----sent to hell!");
	return true;

}
//---------------------------------------------------------------------------------------
void ScreenSaver::ChangeImage(string newImage)
{			
	if (!newImage.empty())
		filePath = newImage;
	else
		filePath = imageSelector.GetNextImage();

	//if we STILL dont have an image...
	if (filePath.empty())
	{
		curImage->NoImageMessage();
		return;
	}

	imageTimer.StartCountdown(0, Globals::imageDisplayTimeLength,0);
	imageTimer.pause = true;
	curImage->Load_Image(filePath);
}
//---------------------------------------------------------------------------------------
void ScreenSaver::Update()
{
	//when the timer is up, but we are still in logic loop, this will cause imgages to be skipped over
	if(imageTimer.IsTimeUp())
		ChangeImage();

	renderer.UpdateAllRenderObjects();
	imageTimer.UpdateStopWatch();
	
	
	refreshTimer.UpdateStopWatch();

	if(!curImage->imageTransition)
		imageTimer.pause = false;

	int keys = keyProxy.convertKeyCodesToKeyFunction();

	switch(keys)
	{
	case KeyProxy::nextImage:
			GotoNextImage();
			break;

		case KeyProxy::KeyFunctions::prevImage:
			GotoPrevImage();
			break;
		case KeyProxy::pauseImage:
			//GotoNextImage();
			break;

		case KeyProxy::deleteImage:
			//GotoPrevImage();
			break;
		case KeyProxy::deleteGallery:
			//gotoNextImage();
			break;

		case KeyProxy::startDownTimer:
			//workoutTimer->startCountdownTimer();
			break;
		case KeyProxy::startUpTimer:
			//workoutTimer->startElapsedTimer();
			break;
	}
}
//---------------------------------------------------------------------------------------
void ScreenSaver::Draw()
{
	//if (Globals::viewPathInfo)
	//	renderer.drawText(10, 0, RGB{ 255, 255, 255 }, filePath);

	//renderer.drawText( 10, 10, makecol(255, 255, 255), 0, to_string((int)fps));
	
	//if(Globals::viewClock)
	//	renderer.drawText(10, 20, RGB{ 255, 255, 255 }, mainApp->getTimeString());

	/*#ifdef _DEBUG
	textprintf_ex(screenBuffer, font, 10, 10, makecol(255, 255, 255), 0, "scale: %f (%f x %f)", scaleFactor, imgWidth, imgHeight);
	textprintf_ex(screenBuffer, font, 10, 20, makecol(255, 255, 255), 0, "%d:%d:%d", imageTimer.minutes, imageTimer.seconds, imageTimer.decimals);
	textprintf_ex(dest, font, 10, 10,  makecol(255,255,255), 0, "x t:  (%d x %d)", x,y);
	textprintf_ex(dest, font, 10, 20,  makecol(255,255,255), 0, "tarX tarY: %f (%d x %d)",scaleFactor, targetX,targetY);
	textprintf_ex(screenBuffer, font, 10, 40, makecol(255, 255, 255), 0, "%s", filePath.c_str());
	textprintf_ex(screenBuffer, font, 10, 50, makecol(255, 255, 255), 0, "%s", asctime(timeinfo));
	#endif*/
}
void ScreenSaver::GotoNextImage()
{
	string img = imageSelector.GotoNextImage();
	ChangeImage(img);
}
//---------------------------------------------------------------------------------------
void ScreenSaver::GotoPrevImage()
{
	string img = imageSelector.GotoPrevImage();
	ChangeImage(img);
	
}
//---------------------------------------------------------------------------------------
void ScreenSaver::DeleteSingleImage(string fileToDelete)
{
	//imageSelector.myDeleteFile( filePath.c_str() );
	DoDelete(fileToDelete);
	//clearScreen();
	//textprintf_ex(screen, font, screenWidth/4, screenHeight/2,  makecol(255,255,255), 0, "deleted: %s",filePath.c_str());
}
//---------------------------------------------------------------------------------------
void ScreenSaver::DeleteGallery(string galleryToDelete)
{
	DoDelete(galleryToDelete);
	//clearScreen();
	//textprintf_ex(screen, font, screenWidth/4, screenHeight/2,  makecol(255,255,255), 0, "deleted: %s",filePath.c_str());
}
//---------------------------------------------------------------------------------------
void ScreenSaver::ToggleLegend()
{
	showLegend = !showLegend;
}
//---------------------------------------------------------------------------------------
void ScreenSaver::WriteToLogFile(string line)
{
	if (!logFile)
		return;
	fprintf(logFile, "%s\n", line.c_str());
}