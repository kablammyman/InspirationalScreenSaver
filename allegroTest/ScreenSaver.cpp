#include "ScreenSaver.h"
#include "GraphicsProxy.h"
#include "keyProxy.h"
#include "mainApp.h"


ScreenSaver::ScreenSaver()
{
	timerOn = false;
	showLegend = false;
	timeOver = false;

	folderNum = 0;
	
	infoImg = new RenderObject(0,0,900,30);
	workoutTimer = new WorkoutTimer(GraphicsProxy::getScreenWidth() - 100, 10);
	workoutTimer->loadSoundFile(MainApp::Instance()->sndFile.c_str());
	workoutTimer->pauseWorkoutTimer(true);

	legend = new AppLegend(GraphicsProxy::getScreenWidth() - 300,GraphicsProxy::getScreenHeight() -100);
	
	curImage = new CurrentImage();

	renderer.init(GraphicsProxy::getScreenWidth(), GraphicsProxy::getScreenHeight());
	renderer.addToRenderList(legend);
	renderer.addToRenderList(curImage);
	renderer.addToRenderList(workoutTimer);
	renderer.addToRenderList(infoImg);
	setCurImgObj(curImage);

	allFiles.init(MainApp::Instance()->numFoldersInBase);

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

	allFiles.setDisplayList(MainApp::Instance()->displayDirs);
}
//---------------------------------------------------------------------------------------
void ScreenSaver::setCurImgObj( CurrentImage *c)
{
	curImage = c;
}
//---------------------------------------------------------------------------------------
void ScreenSaver::changeScreenSize(int screenW, int screenH)
{
	Scene::changeScreenSize(screenW, screenH);
	workoutTimer->setX( GraphicsProxy::getScreenWidth() - 100); 
	legend->setX(GraphicsProxy::getScreenWidth() - 300); 
	legend->setY(GraphicsProxy::getScreenHeight() - 100);
}
//---------------------------------------------------------------------------------------
bool ScreenSaver::doDelete(string path, string createDate)
{
	string lastError = "";
	if (createDate != "")
	{
		string delString = ("deleting: " + path + "created: " + createDate);
		MainApp::Instance()->writeToLogFile(delString);
	}
	else
	{
		string delString = ("deleting: " + path);
		MainApp::Instance()->writeToLogFile(delString);
	}
	
	int recycleErrorVal = 	FileDir::MyFileDirDll::deleteFile( path.c_str() );
	int permDeleteErrorVal = 0;
	if(recycleErrorVal > 0)//try to send to recycle bin failed
	{
		permDeleteErrorVal = FileDir::MyFileDirDll::deleteFile( path.c_str(),true );
		if(permDeleteErrorVal == 0)//cant send there, perm delete
		{
			lastError = FileDir::MyFileDirDll::deleteAllFilesInDir( path.c_str() );
			if(lastError != "") //try to delete each file individually
			{
				string errorString = ("-------recycle error1: " + recycleErrorVal);
				MainApp::Instance()->writeToLogFile(errorString);

				errorString = ("-------perm error: " + permDeleteErrorVal);
				MainApp::Instance()->writeToLogFile(errorString);
				
				errorString = ("-------GetLastError: " + GetLastError());
				MainApp::Instance()->writeToLogFile(errorString);

				return false;
			}
		}
	}
	

	if(recycleErrorVal == 0)
		MainApp::Instance()->writeToLogFile("-----sent to recycle");
	else if(permDeleteErrorVal > 0)
		MainApp::Instance()->writeToLogFile("-----sent to hell!");
	return true;

}
//---------------------------------------------------------------------------------------
void ScreenSaver::changeImage(bool update)
{			
	filePath = allFiles.changeImage(update);
	if(filePath.empty())
		return;
	
	imageTimer.startCountdown(0,5,0);
	imageTimer.pause = true;
	curImage->loadImage(filePath);
}
//---------------------------------------------------------------------------------------
void ScreenSaver::update()
{
	//when the timer is up, but we are still in logic loop, this will cause imgages to be skipped over
	if(imageTimer.isTimeUp())
		changeImage();

	renderer.updateAllRenderObjects();
	imageTimer.updateStopWatch();
	refreshTimer.updateStopWatch();

	if(!curImage->imageTransition)
		imageTimer.pause = false;

	MainApp::Instance()->updateTime();

	int keys = keyProxy.convertKeyCodesToKeyFunction();

	switch(keys)
	{
	case KeyProxy::nextImage:
			gotoNextImage();
			break;

		case KeyProxy::KeyFunctions::prevImage:
			gotoPrevImage();
			break;
		case KeyProxy::pauseImage:
			//gotoNextImage();
			break;

		case KeyProxy::deleteImage:
			//gotoPrevImage();
			break;
		case KeyProxy::deleteGallery:
			//gotoNextImage();
			break;

		case KeyProxy::startDownTimer:
			workoutTimer->startCountdownTimer();
			break;
		case KeyProxy::startUpTimer:
			workoutTimer->startElapsedTimer();
			break;
	}
}
//---------------------------------------------------------------------------------------
void ScreenSaver::draw()
{
	clear(infoImg->getBitmap());
	textprintf_ex(infoImg->getBitmap(), font, 10, 0, makecol(255, 255, 255), 0, "%s", filePath.c_str());
	textprintf_ex(infoImg->getBitmap(), font, 10, 10, makecol(255, 255, 255), 0, "fps: %d", fps);
	textprintf_ex(infoImg->getBitmap(), font, 10, 20, makecol(255, 255, 255), 0, "%s", MainApp::Instance()->getTimeString().c_str());
	/*#ifdef _DEBUG
	textprintf_ex(screenBuffer, font, 10, 10, makecol(255, 255, 255), 0, "scale: %f (%f x %f)", scaleFactor, imgWidth, imgHeight);
	textprintf_ex(screenBuffer, font, 10, 20, makecol(255, 255, 255), 0, "%d:%d:%d", imageTimer.minutes, imageTimer.seconds, imageTimer.decimals);
	textprintf_ex(dest, font, 10, 10,  makecol(255,255,255), 0, "x t:  (%d x %d)", x,y);
	textprintf_ex(dest, font, 10, 20,  makecol(255,255,255), 0, "tarX tarY: %f (%d x %d)",scaleFactor, targetX,targetY);
	textprintf_ex(screenBuffer, font, 10, 40, makecol(255, 255, 255), 0, "%s", filePath.c_str());
	textprintf_ex(screenBuffer, font, 10, 50, makecol(255, 255, 255), 0, "%s", asctime(timeinfo));
	#endif*/

	renderer.blitToScreen();
}
void ScreenSaver::gotoNextImage()
{
	allFiles.gotoNextImage();
	changeImage(false);
}
//---------------------------------------------------------------------------------------
void ScreenSaver::gotoPrevImage()
{
	allFiles.gotoPrevImage();
	changeImage(false);
	
}
//---------------------------------------------------------------------------------------
void ScreenSaver::deleteSingleImage(string fileToDelete)
{
	//allFiles.myDeleteFile( filePath.c_str() );
	doDelete(fileToDelete);
	//clearScreen();
	//textprintf_ex(screen, font, screenWidth/4, screenHeight/2,  makecol(255,255,255), 0, "deleted: %s",filePath.c_str());
}
//---------------------------------------------------------------------------------------
void ScreenSaver::deleteGallery(string galleryToDelete)
{
	doDelete(galleryToDelete);
	//clearScreen();
	//textprintf_ex(screen, font, screenWidth/4, screenHeight/2,  makecol(255,255,255), 0, "deleted: %s",filePath.c_str());
}
//---------------------------------------------------------------------------------------
void ScreenSaver::toggleLegend()
{
	showLegend = !showLegend;
}
//---------------------------------------------------------------------------------------
