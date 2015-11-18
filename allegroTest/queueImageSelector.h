#ifndef QUEUE_IMG_SEL_H
#define QUEUE_IMG_SEL_H

#include <vector>
#include <string>

#include "ImageSelector.h"

class queueImageSelector : public ImageSelector
{
private:
	std::vector<int> sequentialIndex;
  protected:
    int width, height;  
  public:
	queueImageSelector();
	void init(int numFoldersInBase);
	~queueImageSelector();
    std::string getNextImage (std::vector<std::string> displayList);
	std::vector<std::string> queueFolderList(std::string path);
};

#endif