#pragma once
#include "SDL.h"
#include <string>
//http://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/
class SoundEffect
{

	/*static*/ unsigned char *audio_pos; // global pointer to the audio buffer to be played
	/*static*/ unsigned int audio_len; // remaining length of the sample we have to play
								   // local variables
	/*static*/ unsigned int wav_length; // length of our sample
	/*static*/ unsigned char *wav_buffer; // buffer containing our audio file
	/*static*/ SDL_AudioSpec wav_spec; // the specs of our piece of music
	SDL_AudioDeviceID deviceId;
	//void AudioCallback(void *userdata, Uint8 * stream, int len);
public:
	SoundEffect(std::string soundfxPath);
	~SoundEffect();
	void PlaySound();




};