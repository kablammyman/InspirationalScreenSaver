#pragma once

#include <string>

#include "ImageSelector.h"

class RandomImageSelector : public ImageSelector
{
  private:
	int MAX_LOOP_COUNT;
	std::string GetRandomDir(bool useIgnoreList);
	std::string GetRandomDirFromFolderList();
	void RandomizeFolderList( int numFolders);
public:
	RandomImageSelector()
	{
		MAX_LOOP_COUNT = 5;
	}

	std::string GetNewImage();
	
};

