#include <3ds.h>
#include "SDL_config.h"

#include "SDL_rwops.h"
#include "SDL_timer.h"
#include "SDL_audio.h"
#include "../SDL_audiomem.h"
#include "../SDL_audio_c.h"
#include "../SDL_audiodev_c.h"

#include "SDL_3dsaudio.h"

#define DSAUD_DRIVER_NAME "3ds"

static int DSAUD_OpenAudio (_THIS, SDL_AudioSpec *spec);
static void DSAUD_WaitAudio (_THIS);
static void DSAUD_PlayAudio (_THIS);
static Uint8 *DSAUD_GetAudioBuf (_THIS);
static void DSAUD_CloseAudio (_THIS);

static SDL_AudioDevice *sdl_ds_audiodevice; 

int audio_3ds = 0;

static int DSAUD_Available (void) {
	return 1;
}

static void DSAUD_DeleteDevice (SDL_AudioDevice *device) {
}

static SDL_AudioDevice *DSAUD_CreateDevice (int devindex) {
	SDL_AudioDevice *this;

	this = (SDL_AudioDevice *)malloc(sizeof(SDL_AudioDevice));
	if (this) {
		SDL_memset (this, 0, (sizeof *this));
		this->hidden = (struct SDL_PrivateAudioData *)
		SDL_malloc ((sizeof *this->hidden));
	}

	if ((this == NULL) || (this->hidden == NULL)) {
		SDL_OutOfMemory();
		if (this)
			SDL_free (this);

		return(0);
	}

	SDL_memset (this->hidden, 0, (sizeof *this->hidden));

	this->OpenAudio = DSAUD_OpenAudio;
	this->WaitAudio = DSAUD_WaitAudio;
	this->PlayAudio = DSAUD_PlayAudio;
	this->GetAudioBuf = DSAUD_GetAudioBuf;
	this->CloseAudio = DSAUD_CloseAudio;

	this->free = DSAUD_DeleteDevice;

	audio_3ds = 1;

	return this;
}

AudioBootStrap DSAUD_bootstrap = {
	DSAUD_DRIVER_NAME, "3DS Audio", DSAUD_Available, DSAUD_CreateDevice
};

void static DSAUD_WaitAudio (_THIS) {
}

static void DSAUD_PlayAudio (_THIS) {
	if (this->paused)
		return;
}

static Uint8 *DSAUD_GetAudioBuf (_THIS) {
	return NULL;
}

static void DSAUD_CloseAudio (_THIS) {
	if (audio_3ds == 1)
		csndExit();
}

static int DSAUD_OpenAudio (_THIS, SDL_AudioSpec *spec) {
	int format = 0;

	switch (spec->format & ~0x1000) {
		case AUDIO_S8:
			format = 8;
			break;
		case AUDIO_U8:
			spec->format ^= 0x80;
			format = 8;
			break;
		case AUDIO_U16:
			spec->format ^= 0x8000;
			format = 16;
		case AUDIO_S16:
			format = 16;
			break;
	}

	SDL_CalculateAudioSpec(spec);

	SDL_DSAudio_mutex = 0; 
	sdl_ds_audiodevice = this;

	if (audio_3ds == 1)
		csndInit();

	return 1;
}
