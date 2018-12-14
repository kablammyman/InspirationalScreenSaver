#include "ImageSelector.h"
#include "StringUtils.h"
#include <random>

int ImageSelector::GetRandomNum(int min, int max)
{
	 // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    return uniform_dist(e1);
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
