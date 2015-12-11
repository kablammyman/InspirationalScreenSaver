#include <algorithm>    // std::sort
#include "ImageSelector.h"
#include "myFileDirDll.h"

using namespace std;

void ImageSelector::setDisplayList(std::vector<std::string> dispList)
{
	displayList = dispList;
}

std::string ImageSelector::getNextImage ()
{
	curDir = getRandomDir(getRandomDirFromFolderList(displayList),true);

	string img;
	int index = 0;
	int numFiles = FileDir::MyFileDirDll::getNumFilesInDir(curDir);
	if(numFiles == 0)
		return "";

	unsigned int galImgeCounter = seenGalleries[curDir];

	//we have seen everything, reset counter
	if(BitMask::countBits(galImgeCounter) >= numFiles)
		seenGalleries[curDir] = 0;

	for(int i = 0; i < numFiles; i++)
	{
		img = FileDir::MyFileDirDll::getRandomFileQuick(curDir);
		index = getIndexFromFile(img);
		galImgeCounter = seenGalleries[curDir];
		if(!BitMask::isBitSet(index,galImgeCounter))
			break;
	}

		BitMask::setBit(index,galImgeCounter);
		seenGalleries[curDir] = galImgeCounter;

	return img;
}

std::string ImageSelector::toUpper(std::string word)
{
	int i=0;
	char *newWord =new char[word.size()+1];
	char c;
	while (i < (int)word.size())
	{
		c=word[i];
		newWord[i] = toupper(c);
		newWord[i+1] = '\0';
		i++;
	}
	std::string returnWord = newWord;
	return returnWord;
}
//--------------------------------------------------------------------------------------------------------
int ImageSelector::getIndexFromFile(string path)
{
	string file = FileDir::MyFileDirDll::getFileNameFromPathString(path);
	string dirPath = FileDir::MyFileDirDll::getPathFromFullyQualifiedPathString(path);

	vector<string> files = FileDir::MyFileDirDll::getAllFolderNamesInDir(dirPath);

	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i].compare(path) == 0)
			return i;
	}
	return -1; //this dir was empty, return empty string
}
//--------------------------------------------------------------------------------------------------------
bool ImageSelector::checkForIgnorePathList(std::string curPath)
{
	size_t found;
	std::string path = toUpper(curPath);

	for(int i = 0; i < (int)ignoreList.size(); i++)
	{
		std::string comp = toUpper(ignoreList[i]);
		
		found=path.find(comp);
		if (found!=std::string::npos && comp.size() > 1)
		{
			//cout << curPath << " vs: " << ignoreList[i];
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------
void ImageSelector::addRangeToIgnoreList(std::vector<std::string> range)
{
	for(int i = 0; i < (int)range.size(); i++)
		ignoreList.push_back(range[i]);
}
//--------------------------------------------------------------------------------------------------------
vector<string> ImageSelector::randomizeFolderList(string path, int numFolders)
{
	//cout << "getting random folders...\n";
	vector<string> folderList;

	for(int i = 0; i < numFolders; i++)
	{
		bool validFile = false;
		int loopCpunter = 0;
		do{
			if(loopCpunter >= MAX_LOOP_COUNT)
			{
				validFile = true;
				break;
			}
			//countall the dirs in the path given, then get a random num from that!
			//int randomDir = getRandomNum(0,masterFolderList.size()-1);//doesnt seem to get last dir with the size() -1
			string newPath = "";
			if(checkForIgnorePathList(newPath))
			{
				validFile = false;
				loopCpunter++;
			}
			else
			{
				folderList.push_back(newPath);
				validFile = true;
			}
			
		}while(!validFile);
	}
	return folderList;
}
//--------------------------------------------------------------------------------------------------------
//picks a dir from the master list, then "digs" down to get soething new
string ImageSelector::getRandomDir(string dir, bool useIgnoreList)
{
	//short circuit for ignore stuff
	if(useIgnoreList)
	{
		if(checkForIgnorePathList(dir)) 
			return "";
	}

	int curDepth = 0;
	string curDir = dir;
	bool done = false;
	int loopCount = 0;
	vector<string> digPath; //to keep track of the way we get to our final folder

	while(!done)//keep "digging" until theres no more folders, just images remain
	{
		if(curDir == "")
		{
			break;
		}
		vector<string> curDirList = FileDir::MyFileDirDll::getAllFolderNamesInDir(curDir);
		
		if(curDirList.size() == 0)//there are no more folders
			done = true;
		else if(loopCount > 10)
		{
			curDir = "";//return an empty string, since no valid directorys were "found" (more like stumbled upon)
			done = true;
		}

		else
		{
			size_t size = curDirList.size();
			int nextDir = 0;

			//if we have 1
			if (size == 1)
				nextDir = 0;
			//we want the bigger dirs to have priority over smaller ones, so lets find the bigest one!
			else if (size > 1 && size < 4)
			{
				vector<__int64> dirSizes;
				__int64 runningSize = 0;
				for (size_t i = 0; i < size; i++)
				{
					dirSizes.push_back(FileDir::MyFileDirDll::getDirSize(curDirList[i]));
					runningSize += dirSizes.back();//add the latest item to the running count
				}

				//now treat all directors in here as 100%, find the percentage of each, so the rand
				//has a high chance of picking the biggest dir
				sort(dirSizes.begin(), dirSizes.end());

				for (size_t i = 0; i < size; i++)
				{
					double temp = ((double)dirSizes[i] / (double)runningSize);
					temp *= 100;
					dirSizes[i] =  (__int64)temp;
					if (dirSizes[i] == 0)
						dirSizes[i] = 1;
				}
				int index = getRandomNum(0, 100);
				nextDir = -1;

				for (size_t i = size-1; i > 0; i--)
				{
					if (index < dirSizes[i])
						nextDir = i;
				}

				if(nextDir == -1)
					nextDir = size-1;
			}
			else
				nextDir = getRandomNum(0, curDirList.size()-1);

			string newDir = curDirList[nextDir];

			if(useIgnoreList)
			{
				if(checkForIgnorePathList(newDir)) //if we find something to ignore
				{
					loopCount++;
					continue;//try again
				}
				else
				{
					curDir = newDir;//oitehrwise, keep digging
					loopCount = 0;//reset loop count
				}
			}
			else
				curDir = newDir;//no directory is off limits

		}
	}
	return curDir;
}
//--------------------------------------------------------------------------------------------------------
string ImageSelector::getRandomDirFromFolderList(vector<string> &dirList)
{
	if (dirList.size() == 0)
		return "";
	else if (dirList.size() == 1)
		return dirList[0];
	
	return dirList[getRandomNum(0,dirList.size()-1)];
}
//---------------------------------------------------------------------------------------
string ImageSelector::changeImage(bool update)
{			
	string newImage;
	if(curImgSeenIndex == seenImgList.size())//or whatever the top of the list is, then get a new img
	{
		newImage = getNextImage();
		if(!newImage.empty())
			seenImgList.push_back(newImage);
		else
			return "";
	}
	else
	{
		if(curImgSeenIndex > 0)
			newImage = seenImgList[curImgSeenIndex-1];
		else
			newImage = seenImgList[0];
	}
	if(update)
		curImgSeenIndex++;

	if(newImage == "") //we didnt find anything
	{
		for(size_t i = 0; i < displayList.size(); i++)
			if(displayList[i] == newImage)
				displayList.erase (displayList.begin()+i); //remove this path from list, since its empty
	}
	
	return newImage;
}
//---------------------------------------------------------------------------------------
void ImageSelector::gotoNextImage()
{
	if(curImgSeenIndex < seenImgList.size())//make sure we can go forward
		curImgSeenIndex++;
	else
		curImgSeenIndex = seenImgList.size();	
}
//---------------------------------------------------------------------------------------
void ImageSelector::gotoPrevImage()
{
	if(curImgSeenIndex > 0)//make sure we can go back
		curImgSeenIndex--;
	else
		curImgSeenIndex = 0;
}
//--------------------------------------------------------------------------------------------------------
string ImageSelector::getDirFromIndex(string baseDir, size_t index, bool useIgnoreList)
{
	//short circuit for ignore stuff
	/*if(useIgnoreList)
	{
	if(checkForIgnorePathList(ignoreList, baseDir))
	return "";
	}*/

	vector<string> curDirList = FileDir::MyFileDirDll::getAllFolderNamesInDir(baseDir.c_str());
	if (index >= curDirList.size())
		index = curDirList.size() - 1;
	if (index < curDirList.size() && index > -1)
	{
		string returnDir = curDirList[index];
		/*if(useIgnoreList)
		{
		if(checkForIgnorePathList(ignoreList, returnDir))
		return "";
		}*/
		return returnDir;
	}

	//if we are here, then we prob had an invalid index
	return "";
}