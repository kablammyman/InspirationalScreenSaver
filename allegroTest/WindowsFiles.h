#ifndef WINDOWS_FILES_H
#define WINDOWS_FILES_H

#include <string>
#include <vector>

using namespace std;

class WindowsFiles
{
public:
	
	static vector<string> getFolders(string path);//needs to have *.fileExt to work
	static int countFoldersinDir(string path);
	static int countFilesInDir(string path);
	static int myDeleteFile(string file, bool permanetDelete = false);
	static string deleteAllFilesInDir(string path);
	static string getRandomFileFromDir(string path);
	static vector<string> getAllFilesFromDir(string path);
	static string getFileFromIndex(string path, size_t index);
	static int getIndexFromFile(string path, string file);
	static int getIndexFromFile(string path);
	static string getDirFromIndex(string baseDir, size_t index, bool useIgnoreList = true);
	static string getFileFromPathString(string path);
	static string getPathFromPathString(string path);
private:
	struct tm* clock;               // create a time structure
	struct stat attrib;         // create a file attribute structure
	
	static int getRandomNum(int min, int max);
	static string prepPathForTraversal(string path);
};

#endif//WINDOWS_FILES_H