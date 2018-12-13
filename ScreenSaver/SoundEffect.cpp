#include "SoundEffect.h"



SoundEffect::SoundEffect(std::string soundfxPath)
{
	if (SDL_LoadWAV(soundfxPath.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL)
	{
		return;
	}
	// set the callback function
	//wav_spec.callback = AudioCallback;
	wav_spec.userdata = NULL;

	SDL_OpenAudio(&wav_spec, NULL);
	//deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);

	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length
}

SoundEffect::~SoundEffect()
{
	SDL_FreeWAV(wav_buffer);
}

void SoundEffect::PlaySound()
{
	int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);
	SDL_PauseAudioDevice(deviceId, 0);
}
// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
/*void SoundEffect::AudioCallback(void *userdata, Uint8 * stream,int len);
{

	if (audio_len == 0)
		return;

	len = (len > audio_len ? audio_len : len);
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}*/

