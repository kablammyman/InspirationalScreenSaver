#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

class GalleryMemory
{
	
	unsigned int  curImgSeenIndex; 
	

	//all the gallaries, so we can make sure that if we shown in image from this dir
	//we can either look for a new dir, or make sure to find a differnt image from this dir
	//we will have a map of string pointers (the path to a gallery from the seenImgList) and how many of the images has been seen.
	//used with the trie, we can verify no image will be seen more than once until all images from teh gallery has been seen

	vector<string> seenImgList; //all the images we shown so far, so we can go back in the list
	//gallery,index from seenImgList
	map<string, vector<int>> seenGalleriesImageCount;

	//int maxSizeImageSeenList;
public:
	GalleryMemory()
	{
		curImgSeenIndex = 0; 
		//maxSizeImageSeenList = 0;// 0 means umlimited
	}
	string getNextImage();
	string getPrevImage();
	string getNewImage();
	bool isAtTopOfList()
	{
		if (seenImgList.size() == 0) 
			return true;
		if (curImgSeenIndex == seenImgList.size()-1)
			return true;
		return false;
	}
	string getCurrentImage()
	{
		return seenImgList[curImgSeenIndex];
	}

	void addImageToList(string imagePath);
	bool hasSeenImage(string imagePath, int numFilesinDir);
	void resetGallerySeenCount(string galleryName);
};