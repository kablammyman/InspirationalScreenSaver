#ifndef SHUFFLED_IMG_SEL_H
#define SHUFFLED_IMG_SEL_H

#include <vector>
#include <string>

#include "ImageSelector.h"

class shuffledImageSelector : ImageSelector
{
  protected:
    int width, height;  
  public:
    std::string getNextImage (std::vector<std::string> &displayList);
	std::vector<std::string> shuffleFolderList(std::string path);
};

#endif