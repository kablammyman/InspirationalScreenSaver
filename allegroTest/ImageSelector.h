#ifndef BASE_IMG_SEL_H
#define BASE_IMG_SEL_H

#include <map>
#include <string>
#include "myFileDirDll.h"
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
	bool checkForIgnorePathList(std::string curPath);
	void addRangeToIgnoreList(std::vector<std::string> range);

	string getDirFromIndex(string baseDir, size_t index, bool useIgnoreList = true);

	inline int getNextFolderListIndex(string path, int curIndex)
	{
		if(curIndex < MyFileDirDll::getNumFilesInDir(path))
			curIndex++;
		else 
			curIndex = 0;

		return curIndex;
	}

	inline int getRandomNum(int min, int max)
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
	
	void setDisplayList(std::vector<std::string> dispList);
    std::string getNewImage();
	std::vector<std::string> randomizeFolderList(std::string path, int numFolders);
	std::string getRandomDir(std::string dir, bool useIgnoreList);
	std::string getRandomDirFromFolderList(std::vector<std::string> &dirList);
	std::string changeImage(bool update = true);
	void gotoPrevImage();
	void gotoNextImage();
};
#endif