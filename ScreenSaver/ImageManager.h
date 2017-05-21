#pragma once

#include <map>
#include <string>
#include "FileUtils.h"
#include "BitMask.h"
#include "GalleryMemory.h"
#include "ImageSelector.h"

/*
struct Gallery
{
	string path;
	int BITMASK;
	int fileCount;
};
*/

class ImageManager
{
  protected:
	
	
	GalleryMemory galMemory;
	ImageSelector *imgSelector;

	unsigned int  curDirIndex;
	string curDir;

	

	string GetDirFromIndex(string baseDir, size_t index);

	inline int GetNextFolderListIndex(string path, int curIndex)
	{
		if(curIndex < FileUtils::GetNumFilesInDir(path))
			curIndex++;
		else 
			curIndex = 0;

		return curIndex;
	}

	
  public:
	ImageManager();
	void SetDisplayList(std::vector<std::string> dispList);
	std::string GetNewImage();
	std::string GetNextImage();
	std::string GotoPrevImage();
	std::string GotoNextImage();

	void SetImageMemAmt(int x);
};
