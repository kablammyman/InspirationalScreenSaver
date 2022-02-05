#include "KeyProxy.h"
#include "SDL.h"

int KeyProxy::pollKeys()
{
	return 0;//AllegroKeys::getKeyByScanCode();
}


int KeyProxy::ConvertKeyCodesToKeyFunction(int keycode)
{
	switch(keycode)
	{
		/*case SDLK_UP:
		case 7:
			return deleteGallery;
		//KEY_I
		case 9:
			return deleteImage;
			*/
		//KEY_SPACE
		case SDLK_d:
			curKey = toggleDebug;
			return toggleDebug;
		
		case SDLK_SPACE:
		//case 75:
			curKey = pauseImage;
			return pauseImage;

		case SDLK_LEFT:
		//case 82:
			curKey = prevImage;
			return prevImage;
		
		case SDLK_UP:
		//case 84:
			curKey = startUpTimer;
			return startUpTimer;

		case SDLK_RIGHT:
		//case 83:
			curKey = nextImage;
			return nextImage;

		case SDLK_DOWN:
		//case 85:
			curKey = startDownTimer;
			return startDownTimer;
	}
	return -1;
}