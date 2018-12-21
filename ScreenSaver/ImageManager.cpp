
#include "ImageManager.h"
#include "FileUtils.h"
#include "CFGUtils.h"
#include "RandomImageSelector.h"
#include "SequentialRandomImageSelector.h"

using namespace std;

ImageManager::ImageManager()
{
	//imgSelector = new RandomImageSelector();
	imgSelector = new SequentialRandomImageSelector();
	
}


void ImageManager::SetDisplayList(std::vector<std::string> dispList)
{
	imgSelector->SetDisplayList(dispList);
}




//---------------------------------------------------------------------------------------
std::string ImageManager::GetNewImage()
{
	bool isUniqueImg = false;
	string img;
	int count = 0;
	while (!isUniqueImg)
	{
		count++;

		img = imgSelector->GetNewImage();
		if (!galMemory.hasSeenImage(img))
		{
			isUniqueImg = true;
			break;
		}
		
		//break out if we cant find an image after 100 tries
		if (count > 100)
			isUniqueImg = true;
	}

	galMemory.addImageToList(img);
	return img;
}
//---------------------------------------------------------------------------------------
string ImageManager::GetNextImage()
{			
	string returnImage;
	
	if (galMemory.isAtTopOfList())
		returnImage = GetNewImage();

	else
		returnImage = galMemory.getNextImage();
		
	//if the image is not valid, remove it from the list (if its there)
	if (returnImage == "") 
	{
		imgSelector->RemoveImageFromList(returnImage);
	}
			
	return returnImage;
}
//---------------------------------------------------------------------------------------
string ImageManager::GotoNextImage()
{
	if (!galMemory.isAtTopOfList())
		return galMemory.getNextImage();
	return "";//this will single the changeImage method to get a new image
}
//---------------------------------------------------------------------------------------
string ImageManager::GotoPrevImage()
{
	return galMemory.getPrevImage();
}
//--------------------------------------------------------------------------------------------------------
string ImageManager::GetDirFromIndex(string baseDir, size_t index)
{
	//short circuit for ignore stuff
	/*if(useIgnoreList)
	{
	if(checkForIgnorePathList(ignoreList, baseDir))
	return "";
	}*/

	vector<string> curDirList = FileUtils::GetAllFileNamesInDir(baseDir);
	if (index >= curDirList.size())
		index = curDirList.size() - 1;
	if (index < curDirList.size() && index > -1)
	{
		string returnDir = curDirList[index];
	
		return returnDir;
	}

	//if we are here, then we prob had an invalid index
	return "";
}
//---------------------------------------------------------------------------------------
void ImageManager::SetImageMemAmt(int x)
{
	galMemory.setImageMemAmt(x);
}
