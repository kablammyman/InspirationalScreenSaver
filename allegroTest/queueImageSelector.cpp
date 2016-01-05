
#include "queueImageSelector.h"
#include "myFileDirDll.h"

using namespace std;

queueImageSelector::queueImageSelector()
{
	curDirIndex = 0;
}
void queueImageSelector::init(int numFoldersInBase)
{
	//make sure its the size we need it to be
	for(int i = 0; i < numFoldersInBase; i++)
		sequentialIndex.push_back(-1);
	curDirIndex = 0;
}
queueImageSelector::~queueImageSelector()
{
	sequentialIndex.clear();
}

std::string queueImageSelector::getNextImageInQueue (std::vector<std::string> &displayList)
{
	string dir = displayList[curDirIndex];

	if(curDirIndex < displayList.size()-1)
		curDirIndex++;
	else 
		curDirIndex = 0;

	int numFodlersInDir = MyFileDirDll::getNumFilesInDir(dir);
	//first time we doing this for this dir, start at a random spot
	if(sequentialIndex[curDirIndex] == -1) 	
		sequentialIndex[curDirIndex] = getRandomNum(0,numFodlersInDir-1);
	
	if(sequentialIndex[curDirIndex] < numFodlersInDir && sequentialIndex[curDirIndex] > -1)	
		sequentialIndex[curDirIndex] ++;
	else
		sequentialIndex[curDirIndex] = 0;

	
	string newDir = getRandomDir(getDirFromIndex(dir, sequentialIndex[curDirIndex],false),false);
	return MyFileDirDll::getRandomDirQuick(newDir);
}
//--------------------------------------------------------------------------------------------------------
vector<string> queueImageSelector::queueFolderList(string path)
{
	
	//cout << "making a queue, starting from a random folder...\n";
	
	vector<string> folderList = MyFileDirDll::getAllFolderNamesInDir(path);
	int numFolders = MyFileDirDll::getNumFilesInDir(path);
	int curDir = getRandomNum(0,numFolders);//doesnt seem to get last dir with the size() -1
	int seqIndex = 0;
	int *seqList = new int[numFolders];
	for(int i = 0; i < numFolders; i++)
	{
		bool validFile = false;
		do{

			if(checkForIgnorePathList( folderList[curDir]))
			{
				curDir = getNextFolderListIndex(path,curDir);
			}
			else
			{
				
				string dir = folderList[curDir];
				if(seqList[curDir] < MyFileDirDll::getNumFilesInDir(dir) &&  seqList[curDir] > -1)	
					seqList[curDir] ++;
				else
					seqList[curDir] = 0;
				
				folderList.push_back(getDirFromIndex(dir, seqList[curDir]));
				validFile = true;
				if(curDir < numFolders)
					curDir++;
				else
					curDir = 0;
			}
			
		}while(!validFile);
	}
	return folderList;
}
