#pragma once

#include <vector>
#include <string>

#include "baseImageSelector.h"

class randomImageSelector : ImageSelector
{
  protected:
    int width, height;  
  public:
    std::string getNextImage (std::vector<std::string> displayList);
	std::vector<std::string> randomizeFolderList(std::string path, int numFolders);
	std::string getRandomDir(std::string dir, bool useIgnoreList);
	std::string getRandomDirFromFolderList(std::vector<std::string> dirList);
};

