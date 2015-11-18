#include "mainApp.h"
#include "WindowsFiles.h"
#include "CFGReaderDll.h"
#include "GraphicsProxy.h"
#include "keyProxy.h"


#include <Windows.h>
#include <ctime> 

mainApp::mainApp()
{
	dirSelectionForDisplay = 0;
	mainWorkingPath = "C:\\";//main path to work from
	
	timeinfo = NULL;

	timerOn = false;
	showLegend = false;
	timeOver = false;

	folderNum = 0;
	
	
	min = 2, sec = 5,mil = 0;

	srand((unsigned)time(0));
	long ltime = time(NULL);
	int stime = (unsigned) ltime/2;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	
	
	
	logFile = fopen ("myfile.txt","w");
	fprintf (logFile,"\nCurrent local time and date: %s \n", asctime (timeinfo));
	infoImg = new renderObj(0,0,900,30);
	workoutTimer = new WorkoutTimer(GraphicsProxy::getScreenWidth() - 100,10);

	
	
	legend = new AppLegend(GraphicsProxy::getScreenWidth() - 300,GraphicsProxy::getScreenHeight() -100);
	
	curImage = new CurrentImage();
	curImage->screenWidth = GraphicsProxy::getScreenWidth();
	curImage->screenHeight = GraphicsProxy::getScreenHeight();

	renderer.init(GraphicsProxy::getScreenWidth(), GraphicsProxy::getScreenHeight());
	renderer.addToRenderList(legend);
	renderer.addToRenderList(curImage);
	renderer.addToRenderList(workoutTimer);
	renderer.addToRenderList(infoImg);
	setCurImgObj(curImage);

	
}
//---------------------------------------------------------------------------------------
mainApp::~mainApp()
{
	fclose (logFile);
}
//---------------------------------------------------------------------------------------
void mainApp::setCurImgObj( CurrentImage *c)
{
	curImage = c;
}
//---------------------------------------------------------------------------------------
bool mainApp::readCFG(string filePathBase)
{
	string sndFile = filePathBase + "\\snd.wav";
	//sndFile.replace( sndFile.begin(), sndFile.end(), '\\', '/' );

	workoutTimer->loadSoundFile(sndFile.c_str());

	string ignoreFilePath = filePathBase + "\\morningGloryCfg.txt"; 
	string deletedFilesPath = filePathBase + "\\deletedFiles.txt"; 

	if(!CFG::CFGReaderDLL::readCfgFile(ignoreFilePath,'|'))
	{
		printf ("Error opening %s\n",ignoreFilePath.c_str());
		//alert("errorz", ignoreFilePath.c_str(), "Using defaults.","&Continue", NULL, 'c', 0);
		return -1;
	}

	mainWorkingPath = CFG::CFGReaderDLL::getCfgStringValue("mainWorkingPath");
	dirSelectionForDisplay = CFG::CFGReaderDLL::getCfgIntValue("dirSelectionForDisplay");
	vector<string> displayDirs = CFG::CFGReaderDLL::getCfgListValue("displayDirs");
	
	vector<string> stopWatch = CFG::CFGReaderDLL::getCfgListValue("stopWatch");
	if(!stopWatch.empty())
	{
		min = CFG::CFGReaderDLL::getFloatValueFromList("stopWatch","min");
		sec = CFG::CFGReaderDLL::getFloatValueFromList("stopWatch","sec");
		mil = CFG::CFGReaderDLL::getFloatValueFromList("stopWatch","mil");
	}

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
	
		

	int numFoldersInBase = WindowsFiles::countFoldersinDir(mainWorkingPath);


	allFiles.init(numFoldersInBase);

	//if we say all anywhere in the list, then the display list will be set to the master folder list
	for(size_t i = 0; i < displayDirs.size(); i++) 
		if(displayDirs[i] == "all")
		{
			//gotta dewlete other folders first
			displayDirs.clear();
			displayDirs = WindowsFiles::getFolders(mainWorkingPath);
			break;
		}

	if(displayDirs.size() == 0)
	{
		if(mainWorkingPath[mainWorkingPath.size()-1] != '\\')
			mainWorkingPath.append("\\");
		displayDirs.push_back(mainWorkingPath);
	}
	allFiles.setDisplayList(displayDirs);

	return true;
}
//---------------------------------------------------------------------------------------
bool mainApp::doDelete(string path, string createDate)
{
	string lastError = "";
	if(createDate != "")
		fprintf(logFile,"deleting: %s created: %s\n",path.c_str(),createDate.c_str());
	else
		fprintf(logFile,"deleting: %s\n",path.c_str());
	int recycleErrorVal = 	WindowsFiles::myDeleteFile( path.c_str() );
	int permDeleteErrorVal = 0;
	if(recycleErrorVal > 0)//try to send to recycle bin failed
	{
		permDeleteErrorVal = WindowsFiles::myDeleteFile( path.c_str(),true );
		if(permDeleteErrorVal == 0)//cant send there, perm delete
		{
			lastError = WindowsFiles::deleteAllFilesInDir( path.c_str() );
			if(lastError != "") //try to delete each file individually
			{
				fprintf(logFile,"->  recycle error1: %d, perm error %d, lastError %d, %s\n",recycleErrorVal, permDeleteErrorVal,GetLastError(),lastError);
				return false;
			}
		}
	}
	

	if(recycleErrorVal == 0)
		fprintf(logFile,"->  sent to recycle\n");
	else if(permDeleteErrorVal > 0)
		fprintf(logFile,"->  sent to hell!\n");
	return true;

}
//---------------------------------------------------------------------------------------
void mainApp::changeImage(bool update)
{			
	filePath = allFiles.changeImage(update);
	if(filePath.empty())
		return;
	
	imageTimer.startCountdown(0,5,0);
	imageTimer.pause = true;
	curImage->loadImage(filePath);
}
//---------------------------------------------------------------------------------------
void mainApp::update()
{
	//when the timer is up, but we are still in logic loop, this will cause imgages to be skipped over
	if(imageTimer.isTimeUp())
		changeImage();

	if(!curImage->imageTransition)
		imageTimer.pause = false;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
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
	clear(infoImg->getBitmap());
	textprintf_ex(infoImg->getBitmap(), font, 10, 0,  makecol(255,255,255), 0, "%s",filePath.c_str());
	textprintf_ex(infoImg->getBitmap(), font, 10, 10,  makecol(255,255,255), 0, "fps: %d",fps);
	textprintf_ex(infoImg->getBitmap(), font, 10, 20,  makecol(255,255,255), 0,"%s", asctime (timeinfo));
	imageTimer.updateStopWatch();
	refreshTimer.updateStopWatch();

	renderer.update();
}
//---------------------------------------------------------------------------------------
void mainApp::draw()
{
	renderer.blitToScreen();
}
void mainApp::gotoNextImage()
{
	allFiles.gotoNextImage();
	changeImage(false);
}
//---------------------------------------------------------------------------------------
void mainApp::gotoPrevImage()
{
	allFiles.gotoPrevImage();
	changeImage(false);
	
}
//---------------------------------------------------------------------------------------
void mainApp::deleteSingleImage(string fileToDelete)
{
	//allFiles.myDeleteFile( filePath.c_str() );
	doDelete(fileToDelete);
	//clearScreen();
	//textprintf_ex(screen, font, screenWidth/4, screenHeight/2,  makecol(255,255,255), 0, "deleted: %s",filePath.c_str());
}
//---------------------------------------------------------------------------------------
void mainApp::deleteGallery(string galleryToDelete)
{
	doDelete(galleryToDelete);
	//clearScreen();
	//textprintf_ex(screen, font, screenWidth/4, screenHeight/2,  makecol(255,255,255), 0, "deleted: %s",filePath.c_str());
}
//---------------------------------------------------------------------------------------
void mainApp::toggleLegend()
{
	showLegend = !showLegend;
}
//---------------------------------------------------------------------------------------
