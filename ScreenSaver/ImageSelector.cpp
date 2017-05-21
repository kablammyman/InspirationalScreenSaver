#include "ImageSelector.h"
#include "StringUtils.h"


int ImageSelector::GetRandomNum(int min, int max)
{
	if (max - min == 1)
		return (1 + rand() % 10) > 5 ? 1 : 0;

	else
	{
		int diff = ((max - min) + 1);
		return ((diff * rand()) / RAND_MAX) + min;
	}
}
//--------------------------------------------------------------------------------------------------------
void ImageSelector::AddRangeToIgnoreList(std::vector<std::string> range)
{
	for (int i = 0; i < (int)range.size(); i++)
		ignoreList.push_back(range[i]);
}
//--------------------------------------------------------------------------------------------------------
bool ImageSelector::CheckForIgnorePathList(std::string curPath)
{
	size_t found;

	StringUtils::ToUpper(curPath);

	for (int i = 0; i < (int)ignoreList.size(); i++)
	{
		StringUtils::ToUpper(ignoreList[i]);

		found = curPath.find(ignoreList[i]);
		if (found != std::string::npos && ignoreList[i].size() > 1)
		{
			//cout << curPath << " vs: " << ignoreList[i];
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------
void ImageSelector::SetDisplayList(std::vector<std::string> dispList)
{
	displayList = dispList;
}
//--------------------------------------------------------------------------------------------------------
void ImageSelector::RemoveImageFromList(std::string badImg)
{
	for (size_t i = 0; i < displayList.size(); i++)
		if (displayList[i] == badImg)
			displayList.erase(displayList.begin() + i);
}