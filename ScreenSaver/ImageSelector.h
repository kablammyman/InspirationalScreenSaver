#pragma once
#include <string>
#include <vector>

class ImageSelector
{
protected:
	std::vector<std::string> ignoreList;
	std::vector<std::string> displayList;

	void AddRangeToIgnoreList(std::vector<std::string> range);
	bool CheckForIgnorePathList(std::string curPath);
	int GetRandomNum(int min, int max);

public:
	void SetDisplayList(std::vector<std::string> dispList);
	void RemoveImageFromList(std::string badImg);
	virtual std::string GetNewImage() = 0;
	
};