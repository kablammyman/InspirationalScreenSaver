#include "GalleryMemory.h"
#include "FileUtils.h"
#include <algorithm> //for the remove method

using namespace std;

bool GalleryMemory::isAtTopOfList()
{
	if (seenImgList.size() == 0 || curImgSeenItr == seenImgList.end())
		return true;
	if (curImgSeenItr == --seenImgList.end())
		return true;
	return false;
}
//---------------------------------------------------------------------------------------
string GalleryMemory::getNextImage()
{
	if (curImgSeenItr != seenImgList.end())//make sure we can go forward
		curImgSeenItr++;
	else
		curImgSeenItr = seenImgList.end();
		
	if(curImgSeenItr == seenImgList.end())
		curImgSeenItr--;

	return (*curImgSeenItr);
}
//---------------------------------------------------------------------------------------
string GalleryMemory::getPrevImage()
{
	if (curImgSeenItr != seenImgList.begin())//make sure we can go back
		curImgSeenItr--;
	else
		curImgSeenItr = seenImgList.begin();

	return (*curImgSeenItr);
}
//---------------------------------------------------------------------------------------
void GalleryMemory::addImageToList(string imagePath)
{
	if (imagePath.empty())
		return;
	
	string dir = FileUtils::GetPathFromFullyQualifiedPathString(imagePath);

	seenImgList.push_back(imagePath);
	
	curImgSeenItr = seenImgList.end();
	//go back 1 so you get the latest element, not the end!
	curImgSeenItr--;
	//get the raw pointer from the iterator
	seenGalleriesImageCount[dir].push_back(&*curImgSeenItr);

	//if we are limiting how many images displayed, remove oldest element from list
	//and make sure to remove the pointer from the map
	if (maxSizeImageSeenList > 0 && maxSizeImageSeenList < seenImgList.size())
	{
		string imgToForget = (*seenImgList.begin());
		string *ptr = getImgPathPtrFromMap(imgToForget);
		//now the dir needs to be from the image we are removing from the list
		dir = FileUtils::GetPathFromFullyQualifiedPathString(imgToForget);
		
		seenGalleriesImageCount[dir].erase(std::remove(seenGalleriesImageCount[dir].begin(), seenGalleriesImageCount[dir].end(), ptr), seenGalleriesImageCount[dir].end());
		seenImgList.pop_front();

	}
}
//--------------------------------------------------------------------------------------------------------
void GalleryMemory::resetGallerySeenCount(string galleryName)
{
	seenGalleriesImageCount[galleryName].clear();
}
//---------------------------------------------------------------------------------------
bool GalleryMemory::hasSeenImage(string imagePath)
{
	string *ptr = getImgPathPtrFromMap(imagePath);

	if (ptr == NULL)
		return false;
	return true;
}

string * GalleryMemory::getImgPathPtrFromMap(string imagePath)
{
	string dir = FileUtils::GetPathFromFullyQualifiedPathString(imagePath);
	string file = FileUtils::GetFileNameFromPathString(imagePath);
	size_t size = seenGalleriesImageCount[dir].size();

	//if the gallery has been accesed, the size of the vector assicated with it will be greater than 0
	if (size > 0)
	{
		//trying to do this in one line caused issues...my syntax was prob off.
		vector<string *> tempVec = seenGalleriesImageCount[dir];
		
		//go thru the vec to match the stored strng pointer with the list of seen files, if we have a match, then we seen this image already
		for (size_t i = 0; i < size; i++)
		{
			string *imgName = tempVec[i];
			if (imgName == NULL)
				continue;
			if ((*imgName) == imagePath)
				return imgName;
		}
	}

	return NULL;
}