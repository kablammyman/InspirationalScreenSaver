#include "shuffledImageSelector.h"
#include "FileUtils.h"

using namespace std;

std::string shuffledImageSelector::getNextImage (std::vector<std::string> &displayList)
{
	if(curDirIndex > 0)
		curDirIndex--;
	else
		curDirIndex = displayList.size()-1;
	return displayList[curDirIndex];
}
//--------------------------------------------------------------------------------------------------------
vector<string> shuffledImageSelector::shuffleFolderList(string path)
{
	vector<string> folderList = FileUtils::GetFloatValueFromList(path);
	int numFolders = FileUtils::getNumFilesInDir(path);

	//cout << "shuffling folders...\n";

	//if this number is too big, make it smaller so we arnt in an endless loop
	//if(numFolders > (masterFolderList.size() - ignoreList.size()) )
	//	numFolders = (masterFolderList.size() - ignoreList.size());

	for(int i = 0; i < numFolders; i++)
	{
		bool validFile = false;
		int loopCpunter = 0;
		int randomDir = getRandomNum(0,numFolders);

		do{
			if(loopCpunter >=MAX_LOOP_COUNT)
			{
				validFile = true;
			}

			
			string curDir = folderList[randomDir];
			
			if(checkForIgnorePathList(curDir))
			{
				validFile = false;
				loopCpunter++;
				randomDir = getNextFolderListIndex(path,randomDir);
			}
			else
			{
				bool isIncluded = false;
				for(int j = 0; j < (int)folderList.size(); j++)
				{
					if(folderList[j] == curDir)//if this dir is alraedy in the list, ignore it
					{
						isIncluded = true;
						loopCpunter++;
						break;
					}
				}
				if(!isIncluded)
				{
					folderList.push_back(curDir);
					validFile = true;
				}
			}
			
		}while(!validFile);
	}
	return folderList;
}