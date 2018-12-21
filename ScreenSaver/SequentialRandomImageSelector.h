#pragma once

#include <vector>
#include <string>

#include "RandomImageSelector.h"

//this class will go thru each folder in the main index 1 y 1 before drillign down to find a random image.
//so, most images are sill random, but it will make sure each main folder gets used
class SequentialRandomImageSelector : public RandomImageSelector
{
  private:
	int MAX_LOOP_COUNT;
	std::string GetRandomDirFromSequentialList(bool useIgnoreList);
	std::string GetNextDirFromFolderList();
	size_t masterPathIndex;
public:
	std::string GetNewImage();
};

