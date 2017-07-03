#include "KeyProxy.h"

int KeyProxy::pollKeys()
{
	return 0;//AllegroKeys::getKeyByScanCode();
}
int KeyProxy::ConvertKeyCodesToKeyFunction()
{
	int temp = pollKeys();
	switch(temp)
	{
		//KEY_G
		case 7:
			return deleteGallery;
		//KEY_I
		case 9:
			return deleteImage;

		//KEY_SPACE
		case 75:
			return pauseImage;

		//KEY_LEFT
		case 82:
			return prevImage;
		//KEY_UP
		case 84:
			return startUpTimer;

		//KEY_RIGHT
		case 83:
			return nextImage;

		//KEY_DOWN
		case 85:
			return startDownTimer;
	}
	return -1;
}