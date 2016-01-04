#include "GalleryMemory.h"
#include "myfiledirdll.h"

using namespace std;

//---------------------------------------------------------------------------------------
string GalleryMemory::getNextImage()
{
	if (curImgSeenIndex < seenImgList.size()-1)//make sure we can go forward
		curImgSeenIndex++;
	else
		curImgSeenIndex = seenImgList.size()-1;

	return seenImgList[curImgSeenIndex];
}
//---------------------------------------------------------------------------------------
string GalleryMemory::getPrevImage()
{
	if (curImgSeenIndex > 0)//make sure we can go back
		curImgSeenIndex--;
	else
		curImgSeenIndex = 0;

	return seenImgList[curImgSeenIndex];
}

string GalleryMemory::getNewImage()
{
	string curDir = "nothing!";



	return curDir;
}

void GalleryMemory::addImageToList(string imagePath)
{
	if (imagePath.empty())
		return;
	
	string dir = MyFileDirDll::getPathFromFullyQualifiedPathString(imagePath);

	seenImgList.push_back(imagePath);
	
	//has this gallery been accesed yet? if not, init the values!
	/*if (seenGalleriesImageCount[dir].size() == 0)
		seenGalleriesImageCount[dir].reserve(numFilesInDir);*/
	curImgSeenIndex = seenImgList.size() - 1;
	seenGalleriesImageCount[dir].push_back(curImgSeenIndex);

}
//--------------------------------------------------------------------------------------------------------
/*int GalleryMemory::getIndexFromFile(string dir, string fileName)
{
	vector<string> files = MyFileDirDll::getAllFolderNamesInDir(dir);

	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i].compare(fileName) == 0)
			return i;
	}
	return -1; //this dir was empty, return empty string
}*/
//---------------------------------------------------------------------------------------
bool GalleryMemory::hasSeenImage(string imagePath, int numFilesinDir)
{
	string dir = MyFileDirDll::getPathFromFullyQualifiedPathString(imagePath);
	string file = MyFileDirDll::getFileNameFromPathString(imagePath);
	size_t size = seenGalleriesImageCount[dir].size();

	//if the gallery has been accesed, the size of the vector assicated with it will be greater than 0
	if (size > 0)
	{
		//go thru the vec to match the stored index with the list of seen files, if we have a match, then we seen this image already
		for (size_t i = 0; i < size; i++)
		{
			size_t index = seenGalleriesImageCount[dir][i];
			if(seenImgList[index] == imagePath)
				return true;
		}
	}
	
	return false;
}


/*string GalleryMemory::changeImage(bool update)
{
	string newImage;
	if (curImgSeenIndex == seenImgList.size())//or whatever the top of the list is, then get a new img
	{
		newImage = getNewImage();
		
		else
			return "";
	}
	else
	{
		if (curImgSeenIndex > 0)
			newImage = seenImgList[curImgSeenIndex - 1];
		else
			newImage = seenImgList[0];
	}
	if (update)
		curImgSeenIndex++;


	return newImage;
}*/

