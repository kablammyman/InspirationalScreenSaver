#include <windows.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "WindowsFiles.h"

//--------------------------------------------------------------------------------------------------------
int WindowsFiles::getRandomNum(int min, int max)
{
//	if(rand()%10 > 5)
	{
		int diff = ((max - min) + 1);
		return ((diff * rand())/RAND_MAX) + min;
	}
//	return rand()%max + min;
}

//--------------------------------------------------------------------------------------------------------
vector<string> WindowsFiles::getFolders(string path)//needs to have *.fileExt to work
{
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	string curDir = prepPathForTraversal(path);
	char sTmp[MAX_PATH]="\0";
	vector<string> folderList;
	
	//make sure that the path ends with '\' otherwise, weid shit happens!


	hFind = FindFirstFile(curDir.c_str(), &FindFileData);

	int removeAst = curDir.length()-1;
	curDir.resize (removeAst); //curDir[removeAst]='\0';//remove the asterisk

	if(hFind != INVALID_HANDLE_VALUE)
	do{
		if( strcmp(FindFileData.cFileName,".") == 0 || strcmp(FindFileData.cFileName,"..") == 0)//ignore anything we put in this list
			continue;
 
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{		
			strcpy(sTmp, curDir.c_str());
			strcat(sTmp, FindFileData.cFileName);//cur dir + new folder name = new dir to explre
			strcat(sTmp, "\\");
			folderList.push_back(sTmp);
		}

	}while(FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	
	/*if(folderList.size() <= 0)//no dirs!
		return NULL;

	int index = rand()%folderList.size();
	return folderList[index];*/
	return folderList;
}
//--------------------------------------------------------------------------------------------------------
int WindowsFiles::countFoldersinDir(string path)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	string curDir = prepPathForTraversal(path);
	char sTmp[MAX_PATH]="\0";
	int folderNum = 0;

	hFind = FindFirstFile(curDir.c_str(), &FindFileData);

	int removeAst = curDir.length()-1;
	curDir.resize (removeAst); //curDir[removeAst]='\0';//remove the asterisk

	if(hFind != INVALID_HANDLE_VALUE)
	do{
		if( strcmp(FindFileData.cFileName,".") == 0 || strcmp(FindFileData.cFileName,"..") == 0)
			continue;
 
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			folderNum++;


	}while(FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	
	return folderNum;
}
//--------------------------------------------------------------------------------------------------------
int WindowsFiles::countFilesInDir(string path)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	string curDir = prepPathForTraversal(path);
	char sTmp[MAX_PATH]="\0";
	int folderNum = 0;

	hFind = FindFirstFile(curDir.c_str(), &FindFileData);

	int removeAst = curDir.length()-1;
	curDir.resize (removeAst); //curDir[removeAst]='\0';//remove the asterisk

	if(hFind != INVALID_HANDLE_VALUE)
	do{
		if( strcmp(FindFileData.cFileName,".") == 0 || strcmp(FindFileData.cFileName,"..") == 0)
			continue;
 
		if(!FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		else
			folderNum++;
	}while(FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	
	return folderNum;
}
//--------------------------------------------------------------------------------------------------------
int WindowsFiles::myDeleteFile(string file, bool permanetDelete)
{
	if(permanetDelete)
	{
		//If the function succeeds, the return value is nonzero.
		//If the function fails, the return value is zero (0). To get extended error information, call GetLastError.
		return DeleteFile(file.c_str());
	}

	int len = file.size()+2;
    char* pathToFile = new char[len];
    strcpy(pathToFile, file.c_str());
    pathToFile[len-1] = pathToFile[len-2] = '\0';

	SHFILEOPSTRUCT operation;
	ZeroMemory(&operation, sizeof(operation));
	
	operation.wFunc = FO_DELETE;
	operation.pFrom = pathToFile;//"c:\\file\to\delete.txt";
	operation.fFlags = FOF_ALLOWUNDO|FOF_NO_UI|FOF_NORECURSION;

	//Returns zero if successful; otherwise nonzero. Applications normally should simply check for zero or nonzero.
	//http://msdn.microsoft.com/en-us/library/windows/desktop/bb762164(v=vs.85).aspx
	return SHFileOperation(&operation);

}
//--------------------------------------------------------------------------------------------------------
string WindowsFiles::deleteAllFilesInDir(string path)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	string curDir =  prepPathForTraversal(path);
	char sTmp[MAX_PATH]="\0";
	string returnString = "";

	hFind = FindFirstFile(curDir.c_str(), &FindFileData);

	int removeAst = curDir.length()-1;
	curDir.resize (removeAst); //curDir[removeAst]='\0';//remove the asterisk

	if(hFind != INVALID_HANDLE_VALUE)
	do{
		if( strcmp(FindFileData.cFileName,".") == 0 || strcmp(FindFileData.cFileName,"..") == 0)//ignore anything we put in this list
			continue;
 
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		else
		{
			string file = curDir + FindFileData.cFileName;
			if(myDeleteFile( file,true ) == false )
			{
				returnString += "Error deleting file: ";
				returnString += file;
				returnString += "\n";
			}
		}

	}while(FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	return returnString;
}
//--------------------------------------------------------------------------------------------------------
vector<string> WindowsFiles::getAllFilesFromDir(string path)
{
	
	vector<string> files;

	if(path == "" || path.empty())
		return files;
	
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	string curDir = prepPathForTraversal(path);
	char sTmp[MAX_PATH]="\0";

	hFind = FindFirstFile(curDir.c_str(), &FindFileData);

	int removeAst = curDir.length()-1;
	curDir.resize (removeAst); //curDir[removeAst]='\0';//remove the asterisk

	if(hFind != INVALID_HANDLE_VALUE)
	do {
		if( strcmp(FindFileData.cFileName,".") == 0 || strcmp(FindFileData.cFileName,"..") == 0 || strcmp(FindFileData.cFileName,"Thumbs.db")==0)//ignore anything we put in this list
			continue;
 
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		else
		{
			
			files.push_back(curDir + FindFileData.cFileName);
		}

	}while(FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	
	return files;
}

//--------------------------------------------------------------------------------------------------------
string WindowsFiles::getRandomFileFromDir(string path)
{
	vector<string> files = getAllFilesFromDir(path);

	if(files.size() > 0)
	{
		//used to crash here
		int num = getRandomNum(0, files.size()-1);
		return files[num];
	}
	return ""; //this dir was empty, return empty string
}
//--------------------------------------------------------------------------------------------------------
string WindowsFiles::getFileFromIndex(string path, size_t index)
{
	vector<string> files = getAllFilesFromDir(path);

	if(files.size() > 0)
	{
		if(index <  files.size())
			return files[index];
	}
	return ""; //this dir was empty, return empty string
}
//--------------------------------------------------------------------------------------------------------
int WindowsFiles::getIndexFromFile(string path, string file)
{
	vector<string> files = getAllFilesFromDir(path);

	for(size_t i = 0; i < files.size(); i++)
	{
		if(files[i].compare(path+file) == 0)
			return i;
	}
	return -1; //this dir was empty, return empty string
}
//--------------------------------------------------------------------------------------------------------
int WindowsFiles::getIndexFromFile(string path)
{
	string file = getFileFromPathString(path);
	string dirPath = getPathFromPathString(path);

	vector<string> files = getAllFilesFromDir(dirPath);

	for(size_t i = 0; i < files.size(); i++)
	{
		if(files[i].compare(path) == 0)
			return i;
	}
	return -1; //this dir was empty, return empty string
}
//--------------------------------------------------------------------------------------------------------
string WindowsFiles::getDirFromIndex(string baseDir, size_t index, bool useIgnoreList)
{
		//short circuit for ignore stuff
	/*if(useIgnoreList)
	{
		if(checkForIgnorePathList(ignoreList, baseDir)) 
			return "";
	}*/

	vector<string> curDirList = getFolders(baseDir.c_str());
	if(index >= curDirList.size())
		index = curDirList.size()-1;
	if(index < curDirList.size() && index > -1)
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
//--------------------------------------------------------------------------------------------------------
string WindowsFiles::prepPathForTraversal(string path)
{
	char lastChar = *path.rbegin();
	string newPath = path;
	if(lastChar == '\\')
		newPath += "*";//add asterisk to look for all "files" in cur dir
	else
		newPath += "\\*";//if we forgot to add the last back slash, add it, so we dont crash
	return  newPath;
}
//--------------------------------------------------------------------------------------------------------
string WindowsFiles::getFileFromPathString(string path)
{
	size_t found = path.find_last_of("\\");
	if(found != string::npos)
		return path.substr(found+1);
	return "";
}
//--------------------------------------------------------------------------------------------------------
string WindowsFiles::getPathFromPathString(string path)
{
	size_t found = path.find_last_of("\\");
	if(found != string::npos)
		return path.substr(0,found);
	return "";
}
