#include <algorithm>    // std::sort
#include "RandomImageSelector.h"
#include "FileUtils.h"

using namespace std;
//--------------------------------------------------------------------------------------------------------
//im not sure what this is for....so i keep changing it trying to make sense of it...
void RandomImageSelector::RandomizeFolderList(int numFolders)
{
	vector <string> newList = displayList;
	displayList.clear();
	bool done = false;
	while(!done)
	{
		bool validFile = false;
		int loopCpunter = 0;
		int i = GetRandomNum(0, numFolders);
		do {
			if (loopCpunter >= MAX_LOOP_COUNT)
			{
				validFile = true;
				break;
			}
			//countall the dirs in the path given, then get a random num from that!
			//int randomDir = getRandomNum(0,masterFolderList.size()-1);//doesnt seem to get last dir with the size() -1
			string newPath = newList[i];
			if (CheckForIgnorePathList(newPath))
			{
				validFile = false;
				loopCpunter++;
			}
			else
			{
				displayList.push_back(newPath);
				validFile = true;
			}

		} while (!validFile);
	}
}
//--------------------------------------------------------------------------------------------------------
//picks a dir from the master list, then "digs" down to get soething new
string RandomImageSelector::GetRandomDir(bool useIgnoreList)
{
	string curDir = GetRandomDirFromFolderList(displayList);

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
string RandomImageSelector::GetRandomDirFromFolderList(vector<string> &dirList)
{
	if (dirList.size() == 0)
		return "";
	else if (dirList.size() == 1)
		return dirList[0];

    int index = GetRandomNum(0, (int)dirList.size() - 1);
	return dirList[index];
}
//--------------------------------------------------------------------------------------------------------
string RandomImageSelector::GetNewImage()
{
	string returnImg;
	bool isUniqueImg = false;
	int count = 0;

	while (!isUniqueImg)
	{
		count++;
		string curDir = GetRandomDir(true);
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
