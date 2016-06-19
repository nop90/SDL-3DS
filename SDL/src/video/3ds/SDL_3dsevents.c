#include "SDL_config.h"

#include <3ds.h>

#include "SDL.h"
#include "SDL_mouse.h"
#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"

#include "SDL_3dsevents_c.h"

static SDLKey keymap[DS_NUMKEYS];
char keymem[DS_NUMKEYS];

void DS_PumpEvents (_THIS) {
	scanKeys();

	int i;
	SDL_keysym keysym;
	keysym.mod = KMOD_NONE;

	for (i = 0; i < DS_NUMKEYS; i++) {
		keysym.scancode = i;
		keysym.sym = keymap[i];

		if (keysHeld() & (1 << i) && !keymem[i]) {
			keymem[i] = 1;

			SDL_PrivateKeyboard (SDL_PRESSED, &keysym);
		}

		if (!(keysHeld() & (1 << i)) && keymem[i]) {
			keymem[i] = 0;

			SDL_PrivateKeyboard (SDL_RELEASED, &keysym);
		}
	}

	if (keysHeld() & KEY_TOUCH) {
		touchPosition touch;

		hidTouchRead (&touch);
		if (touch.px != 0 || touch.py != 0) {
			SDL_PrivateMouseMotion (0, 0, touch.py * this->hidden->w / 320, touch.px * this->hidden->h / 240);
			if (!SDL_GetMouseState (NULL, NULL))
				SDL_PrivateMouseButton (SDL_PRESSED, 1, 0, 0);
		}
	} else {
		if (SDL_GetMouseState (NULL, NULL))
			SDL_PrivateMouseButton (SDL_RELEASED, 1, 0, 0);
	}
}

void DS_InitOSKeymap (_THIS) {
	memset (keymem, 0, DS_NUMKEYS);

	keymap[0] = SDLK_d;	
	keymap[1] = SDLK_s;	
	keymap[2] = SDLK_ESCAPE;
	keymap[3] = SDLK_RETURN;
	keymap[4] = SDLK_UP;
	keymap[5] = SDLK_DOWN;
	keymap[6] = SDLK_RIGHT;
	keymap[7] = SDLK_LEFT;
	keymap[8] = SDLK_e;
	keymap[9] = SDLK_q;
	keymap[10] = SDLK_w;
	keymap[11] = SDLK_a;
}
