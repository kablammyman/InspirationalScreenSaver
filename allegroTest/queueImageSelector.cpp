
#include "queueImageSelector.h"
#include "WindowsFiles.h"

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

std::string queueImageSelector::getNextImage (std::vector<std::string> displayList)
{
	string dir = displayList[curDirIndex];

	if(curDirIndex < displayList.size()-1)
		curDirIndex++;
	else 
		curDirIndex = 0;

	int numFodlersInDir = WindowsFiles::countFoldersinDir(dir);
	//first time we doing this for this dir, start at a random spot
	if(sequentialIndex[curDirIndex] == -1) 	
		sequentialIndex[curDirIndex] = getRandomNum(0,numFodlersInDir-1);
	
	if(sequentialIndex[curDirIndex] < numFodlersInDir && sequentialIndex[curDirIndex] > -1)	
		sequentialIndex[curDirIndex] ++;
	else
		sequentialIndex[curDirIndex] = 0;

	
	string newDir = getRandomDir( WindowsFiles::getDirFromIndex(dir, sequentialIndex[curDirIndex],false),false);
	return WindowsFiles::getRandomFileFromDir(newDir);
}
//--------------------------------------------------------------------------------------------------------
vector<string> queueImageSelector::queueFolderList(string path)
{
	
	//cout << "making a queue, starting from a random folder...\n";
	
	vector<string> folderList = WindowsFiles::getFolders(path);
	int numFolders = WindowsFiles::countFoldersinDir(path);
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
				if(seqList[curDir] < WindowsFiles::countFoldersinDir(dir) &&  seqList[curDir] > -1)	
					seqList[curDir] ++;
				else
					seqList[curDir] = 0;
				
				folderList.push_back(WindowsFiles::getDirFromIndex(dir, seqList[curDir]));
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
