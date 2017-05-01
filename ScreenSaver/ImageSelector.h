#pragma once

#include <map>
#include <string>
#include "FileUtils.h"
#include "BitMask.h"
#include "GalleryMemory.h"

/*
struct Gallery
{
	string path;
	int BITMASK;
	int fileCount;
};
*/

class ImageSelector {
  protected:


	std::vector<std::string> ignoreList;
	std::vector<std::string> displayList;
	
	GalleryMemory galMemory;

    int width, height; 
	int MAX_LOOP_COUNT;
	unsigned int  curDirIndex;
	
	string curDir;

	std::string toUpper(std::string word);
	bool CheckForIgnorePathList(std::string curPath);
	void AddRangeToIgnoreList(std::vector<std::string> range);

	string GetDirFromIndex(string baseDir, size_t index, bool useIgnoreList = true);

	inline int GetNextFolderListIndex(string path, int curIndex)
	{
		if(curIndex < FileUtils::GetNumFilesInDir(path))
			curIndex++;
		else 
			curIndex = 0;

		return curIndex;
	}

	inline int GetRandomNum(int min, int max)
	{
		if (max - min == 1)
			return (1 + rand() % 10) > 5 ? 1 : 0;

		else
		{
			int diff = ((max - min) + 1);
			return ((diff * rand())/RAND_MAX) + min;
		}
	}
  public:

	ImageSelector()
	{
		MAX_LOOP_COUNT = 5;
	}
	~ImageSelector(){ignoreList.erase (ignoreList.begin(),ignoreList.end());}
	
	void SetDisplayList(std::vector<std::string> dispList);
    
	std::vector<std::string> RandomizeFolderList(std::string path, int numFolders);
	std::string GetRandomDir(std::string dir, bool useIgnoreList);
	std::string GetRandomDirFromFolderList(std::vector<std::string> &dirList);

	std::string GetNewImage();
	std::string GetNextImage();
	std::string GotoPrevImage();
	std::string GotoNextImage();

	void SetImageMemAmt(int x);
};
