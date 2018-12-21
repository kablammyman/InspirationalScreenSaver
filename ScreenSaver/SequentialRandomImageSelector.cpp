#include <algorithm>    // std::sort
#include "SequentialRandomImageSelector.h"
#include "FileUtils.h"

using namespace std;
//--------------------------------------------------------------------------------------------------------
//picks a dir from the master list, then "digs" down to get soething new
string SequentialRandomImageSelector::GetRandomDirFromSequentialList(bool useIgnoreList)
{
	string curDir = GetNextDirFromFolderList();

	//short circuit for ignore stuff
	if (useIgnoreList)
	{
		if (CheckForIgnorePathList(curDir))
			return "";
	}

	//int curDepth = 0;
	bool done = false;
	int loopCount = 0;
	vector<string> digPath; //to keep track of the way we get to our final folder

	while (!done)//keep "digging" until theres no more folders, just images remain
	{
		if (curDir == "")
		{
			break;
		}
		vector<string> curDirList = FileUtils::GetAllFolderNamesInDir(curDir);

		if (curDirList.size() == 0)//there are no more folders
			done = true;
		else if (loopCount > MAX_LOOP_COUNT)
		{
			curDir = "";//return an empty string, since no valid directorys were "found" (more like stumbled upon)
			done = true;
		}

		else
		{
			size_t size = curDirList.size();
			size_t nextDir = 0;

			//if we have 1
			if (size == 1)
				nextDir = 0;
			//we want the bigger dirs to have priority over smaller ones, so lets find the bigest one!
			else if (size > 1 && size < 4)
			{
				vector<long long> dirSizes;
				long long runningSize = 0;
				for (size_t i = 0; i < size; i++)
				{
					dirSizes.push_back(FileUtils::GetDirSize(curDirList[i]));
					runningSize += dirSizes.back();//add the latest item to the running count
				}

				//now treat all directors in here as 100%, find the percentage of each, so the rand
				//has a high chance of picking the biggest dir
				sort(dirSizes.begin(), dirSizes.end());

				for (size_t i = 0; i < size; i++)
				{
					double temp = ((double)dirSizes[i] / (double)runningSize);
					temp *= 100;
					dirSizes[i] = (long long)temp;
					if (dirSizes[i] == 0)
						dirSizes[i] = 1;
				}
				int index = GetRandomNum(0, 100);
				nextDir = size - 1;

				for (size_t i = size - 1; i > 0; i--)
				{
					if (index < dirSizes[i])
						nextDir = i;
				}
			}
			else
				nextDir = GetRandomNum(0, (int)curDirList.size() - 1);

			string newDir = curDirList[nextDir];

			if (useIgnoreList)
			{
				if (CheckForIgnorePathList(newDir)) //if we find something to ignore
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
string SequentialRandomImageSelector::GetNextDirFromFolderList()
{
	if (displayList.size() == 0)
		return "";
	else if (displayList.size() == 1)
		return displayList[0];
	
	if (masterPathIndex < displayList.size() - 1)
		masterPathIndex++;
	else masterPathIndex = 0;
	return displayList[masterPathIndex];
}

//--------------------------------------------------------------------------------------------------------
string SequentialRandomImageSelector::GetNewImage()
{
	string returnImg;
	bool isUniqueImg = false;
	int count = 0;

	while (!isUniqueImg)
	{
		count++;
		string curDir = GetRandomDirFromSequentialList(true);
		int numFiles = FileUtils::GetNumFilesInDir(curDir);

		if (numFiles == 0)
		{
			if (count > MAX_LOOP_COUNT)
				isUniqueImg = true;
			else
				continue;
		}
		else
		{
			returnImg = FileUtils::GetRandomFileQuick(curDir);
			isUniqueImg = true;
		}
	}

	return returnImg;
}
