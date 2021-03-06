#pragma once

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
	int ConvertKeyCodesToKeyFunction();
	int pollKeys();

};


