#ifndef INPUT_PROXY_H
#define INPUT_PROXY_H

#include "AllegroKeys.h"

class KeyProxy
{

public:
	enum KeyFunctions
	{
		nextImage = 1,
		prevImage = 2,
		pauseImage = 4,
		deleteImage = 8,
		deleteGallery = 16,
		startUpTimer  = 32,
		startDownTimer = 64,
		stopTimer = 128,
		resetTimer = 256
	};

	KeyFunctions keyFunctions;
	int convertKeyCodesToKeyFunction();
	int pollKeys();

};

#endif //INPUT_PROXY_H
