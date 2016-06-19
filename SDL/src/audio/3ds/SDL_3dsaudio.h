#include "SDL_config.h"

#ifndef _SDL_3dsaudio_h
#define _SDL_3dsaudio_h

#include "../SDL_sysaudio.h"

#include <3ds.h>

#define _THIS SDL_AudioDevice *this

struct SDL_PrivateAudioData {
};

unsigned short SDL_DSAudio_mutex = 0; 

#endif
