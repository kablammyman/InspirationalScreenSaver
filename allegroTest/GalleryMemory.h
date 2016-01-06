#pragma once

#include <vector>
#include <list>
#include <string>
#include <map>

using namespace std;

class GalleryMemory
{
	
	//unsigned int  curImgSeenIndex; 	
	list<string>::iterator curImgSeenItr;

	//all the gallaries, so we can make sure that if we shown in image from this dir
	//we can either look for a new dir, or make sure to find a differnt image from this dir
	//we will have a map of string pointers (the path to a gallery from the seenImgList) and how many of the images has been seen.
	//used with the trie, we can verify no image will be seen more than once until all images from teh gallery has been seen

	list<string> seenImgList; //all the images we shown so far, so we can go back in the list
	//gallery,pointer to string in seenImgList
	map<string, vector<string *>> seenGalleriesImageCount;

	int maxSizeImageSeenList;
public:
	GalleryMemory()
	{
		curImgSeenItr = seenImgList.begin();
		maxSizeImageSeenList = 0;// 0 means umlimited
	}

	void setImageMemAmt(int x) { maxSizeImageSeenList = x; }

	bool isAtTopOfList();
	string getNextImage();
	string getPrevImage();
	void addImageToList(string imagePath);
	bool hasSeenImage(string imagePath);
	string * getImgPathPtrFromMap(string imagePath);
	void resetGallerySeenCount(string galleryName);
};