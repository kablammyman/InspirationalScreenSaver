
#include "ImageSelector.h"
#include "WindowsFiles.h"

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
	int numFiles = WindowsFiles::countFilesInDir(curDir);
	if(numFiles == 0)
		return "";

	unsigned int galImgeCounter = seenGalleries[curDir];

	//we have seen everything, reset counter
	if(BitMask::countBits(galImgeCounter) >= numFiles)
		seenGalleries[curDir] = 0;

	for(int i = 0; i < numFiles; i++)
	{
		img = WindowsFiles::getRandomFileFromDir(curDir);
		index = WindowsFiles::getIndexFromFile(img);
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
//pics a dir from the master list, then "digs" down to get soething new
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
		vector<string> curDirList = WindowsFiles::getFolders(curDir);
		
		if(curDirList.size() == 0)//there are no more folders
			done = true;
		else if(loopCount > 10)
		{
			curDir = "";//return an empty string, since no valid directorys were "found" (more like stumbled upon)
			done = true;
		}

		else
		{
			int nextDir = 0;
			if(curDirList.size()-1 > 1)
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
	if(dirList.size() > 0)
		return dirList[getRandomNum(0,dirList.size()-1)];
	return "";
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