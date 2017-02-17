/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#include <3ds.h>

#include "SDL.h"
#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"

#include "SDL_n3dsvideo.h"
#include "SDL_n3dsevents_c.h"

static SDLKey keymap[N3DS_NUMKEYS];
char keymem[N3DS_NUMKEYS];

void N3DS_PumpEvents(_THIS)
{
	hidScanInput();

	int i;
	SDL_keysym keysym;
	keysym.mod = KMOD_NONE;

	for (i = 0; i < N3DS_NUMKEYS; i++) {
		keysym.scancode = i;
		keysym.sym = keymap[i];

		if (hidKeysHeld() & (1 << i) && !keymem[i]) {
			keymem[i] = 1;

			SDL_PrivateKeyboard (SDL_PRESSED, &keysym);
		}

		if (!(hidKeysHeld() & (1 << i)) && keymem[i]) {
			keymem[i] = 0;

			SDL_PrivateKeyboard (SDL_RELEASED, &keysym);
		}
	}

	if (hidKeysHeld() & KEY_TOUCH) {
		touchPosition touch;

		hidTouchRead (&touch);
		if (touch.px != 0 || touch.py != 0) {
			SDL_PrivateMouseMotion (0, 0, (touch.px * 400) / 320, (touch.py * 240) / 240);
			if (!SDL_GetMouseState (NULL, NULL))
				SDL_PrivateMouseButton (SDL_PRESSED, 1, 0, 0);
		}
	} else {
		if (SDL_GetMouseState (NULL, NULL))
			SDL_PrivateMouseButton (SDL_RELEASED, 1, 0, 0);
	}
}

void N3DS_InitOSKeymap(_THIS)
{
	SDL_memset(keymem,1,N3DS_NUMKEYS);
	keymap[0]=SDLK_a; //KEY_A
	keymap[1]=SDLK_b; // KEY_B
	keymap[2]=SDLK_ESCAPE; //KEY_SELECT
	keymap[3]=SDLK_RETURN; //KEY_START
	keymap[4]=SDLK_RIGHT; //KEY_RIGHT
	keymap[5]=SDLK_LEFT; //KEY_LEFT
	keymap[6]=SDLK_UP; // KEY_UP
	keymap[7]=SDLK_DOWN; //KEY_DOWN
	keymap[8]=SDLK_r; //KEY_R
	keymap[9]=SDLK_l; //KEY_L
	keymap[10]=SDLK_UNKNOWN; 
	keymap[11]=SDLK_UNKNOWN; 
	keymap[12]=SDLK_UNKNOWN; 
	keymap[13]=SDLK_UNKNOWN; 
	keymap[14]=SDLK_UNKNOWN; 
	keymap[15]=SDLK_UNKNOWN; 
	keymap[16]=SDLK_UNKNOWN; 
	keymap[17]=SDLK_UNKNOWN; 
	keymap[18]=SDLK_UNKNOWN; 
	keymap[19]=SDLK_UNKNOWN; 
	keymap[20]=SDLK_UNKNOWN; 
	keymap[21]=SDLK_UNKNOWN; 
	keymap[22]=SDLK_UNKNOWN; 
	keymap[23]=SDLK_UNKNOWN; 
	keymap[24]=SDLK_UNKNOWN; 
	keymap[25]=SDLK_UNKNOWN; 
	keymap[26]=SDLK_UNKNOWN; 
	keymap[27]=SDLK_UNKNOWN; 
	keymap[28]=SDLK_UNKNOWN; 
	keymap[29]=SDLK_UNKNOWN; 
	keymap[30]=SDLK_UNKNOWN; 
	keymap[31]=SDLK_UNKNOWN; 

// init the key state
	int i;
	hidScanInput();
	for (i = 0; i < N3DS_NUMKEYS; i++)
		keymem[i] = (hidKeysHeld() & (1 << i))?1:0;

}

void SDL_N3DSKeyBind(unsigned int hidkey, SDLKey key) {
	int i,pos;
	for (i = 0; i < N3DS_NUMKEYS; i++) {
		pos= 1<<i;
		if(hidkey&pos) keymap[i]=key;
	}
}


/* end of SDL_nullevents.c ... */

