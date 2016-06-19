#include "SDL_config.h"

#ifndef _SDL_3dsvideo_h
#define _SDL_3dsvideo_h

#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"

#define _THIS SDL_VideoDevice *this

struct SDL_PrivateVideoData {
	int w, h;
	void *buffer;
	short secondbufferallocd;
};

#define DS_NUMKEYS 12

extern void DS_InitOSKeymap (_THIS);
extern void DS_PumpEvents (_THIS);

#endif
