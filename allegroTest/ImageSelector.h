#ifndef BASE_IMG_SEL_H
#define BASE_IMG_SEL_H

#include <map>
#include <string>
#include "myFileDirDll.h"
#include "BitMask.h"

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
	  	/*
	create a has for each image gallery we encounter.
	ex: C:/3rdDir/1StDir/2Nd -> /3/1/2 (we exclude the base dir)
	
	Use the bit vector to mark off what individual files we seen.
	this way, we wont ever see the same exact image file more than once, and we wont need to store large strings 

	who cares about the hash...too uch effort
	*/
	std::map<std::string,unsigned int> seenGalleries;

	std::vector<std::string> ignoreList;
	std::vector<std::string> displayList;
	std::vector<std::string> seenImgList;

    int width, height; 
	int MAX_LOOP_COUNT;
	unsigned int  curDirIndex;
	unsigned int  curImgSeenIndex; //are we showing a new image, or soemething we already seen?
	string curDir;

	std::string toUpper(std::string word);
	bool checkForIgnorePathList(std::string curPath);
	void addRangeToIgnoreList(std::vector<std::string> range);

	int getIndexFromFile(string path);
	string getDirFromIndex(string baseDir, size_t index, bool useIgnoreList = true);

	inline int getNextFolderListIndex(string path, int curIndex)
	{
		if(curIndex < FileDir::MyFileDirDll::getNumFilesInDir(path))
			curIndex++;
		else 
			curIndex = 0;

		return curIndex;
	}

	inline int getRandomNum(int min, int max)
	{
	//	if(rand()%10 > 5)
		{
			int diff = ((max - min) + 1);
			return ((diff * rand())/RAND_MAX) + min;
		}
	//	return rand()%max + min;
	}
  public:

	ImageSelector()
	{
		MAX_LOOP_COUNT = 5;
		curImgSeenIndex = 0; //are we shpowing a new image, or soemething we already seen?
	}
	~ImageSelector(){ignoreList.erase (ignoreList.begin(),ignoreList.end());}
	
	void setDisplayList(std::vector<std::string> dispList);
    std::string getNextImage();
	std::vector<std::string> randomizeFolderList(std::string path, int numFolders);
	std::string getRandomDir(std::string dir, bool useIgnoreList);
	std::string getRandomDirFromFolderList(std::vector<std::string> &dirList);
	std::string changeImage(bool update = true);
	void gotoPrevImage();
	void gotoNextImage();
};
#endif