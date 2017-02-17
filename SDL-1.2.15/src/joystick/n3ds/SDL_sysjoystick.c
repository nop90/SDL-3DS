#include "SDL_config.h"

#include <3ds.h>

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_joystick.h"
#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"

#include "../../video/n3ds/SDL_n3dsvideo.h"

//int old_button = 0, old_key = 0;
u32 key_press, key_release = 0;

int SDL_SYS_JoystickInit (void) {
	SDL_numjoysticks = 1;

	return 1;
}

const char *SDL_SYS_JoystickName (int index) {
	if(!index)
		return "3DS builtin joypad";

	SDL_SetError ("No joystick available with that index");

	return (NULL);
}

int SDL_SYS_JoystickOpen(SDL_Joystick *joystick) {
	joystick->nbuttons = 8;
	joystick->nhats = 0;
	joystick->nballs = 0;
	joystick->naxes = 2;

	return 0;
}

void SDL_SYS_JoystickUpdate (SDL_Joystick *joystick) {
	short ax = 0, v = 0, h = 0;

	key_press = hidKeysDown ();
	if((key_press & KEY_UP)) {
		ax = 1, v = -10;
		SDL_PrivateJoystickAxis (joystick, ax, v);
//		old_key = KEY_UP;
	}
	if((key_press & KEY_DOWN)) {
		ax = 1, v = 10;
		SDL_PrivateJoystickAxis (joystick, ax, v);
//		old_key = KEY_DOWN;
	}
	if((key_press & KEY_LEFT)) {
		ax = 0, h = -10;
		SDL_PrivateJoystickAxis (joystick, ax, h);
//		old_key = KEY_LEFT;
	}
	if((key_press & KEY_RIGHT)) {
		ax = 0, h = 10;
		SDL_PrivateJoystickAxis (joystick, ax, h);
//		old_key = KEY_RIGHT;
	}
	if ((key_press & KEY_A)) {
		SDL_PrivateJoystickButton (joystick, 0, SDL_PRESSED);
//		old_button = KEY_A;
	}
	if ((key_press & KEY_B)) {
		SDL_PrivateJoystickButton (joystick, 1, SDL_PRESSED);
//		old_button = KEY_B;
	}
	if ((key_press & KEY_X)) {
		SDL_PrivateJoystickButton (joystick, 2, SDL_PRESSED);
//		old_button = KEY_X;
	}
	if ((key_press & KEY_Y)) {
		SDL_PrivateJoystickButton (joystick, 3, SDL_PRESSED);
//		old_button = KEY_Y;
	}
	if ((key_press & KEY_SELECT)) {
		SDL_PrivateJoystickButton (joystick, 6, SDL_PRESSED);
//		old_button = KEY_SELECT;
	}
	if ((key_press & KEY_START)) {
		SDL_PrivateJoystickButton (joystick, 7, SDL_PRESSED);
//		old_button = KEY_START;
	}
	if ((key_press & KEY_L)) {
		SDL_PrivateJoystickButton (joystick, 4, SDL_PRESSED);
//		old_button = KEY_L;
	}
	if ((key_press&KEY_R)) {
		SDL_PrivateJoystickButton(joystick,5,SDL_PRESSED);
//		old_button = KEY_R;
	}

	key_release = hidKeysUp ();
	if ((key_release & KEY_UP)) {
		ax = 1, v = 0;
		SDL_PrivateJoystickAxis (joystick, ax, v);
//		old_key = 0;
	}
	if ((key_release & KEY_DOWN)) {
		ax = 1, v = 0;
		SDL_PrivateJoystickAxis (joystick, ax, v);
//		old_key = 0;
	}
	if ((key_release & KEY_LEFT)) {
		ax = 0, h = 0;
		SDL_PrivateJoystickAxis (joystick, ax, h);
//		old_key = 0;
	}
	if ((key_release & KEY_RIGHT)) {
		ax = 0, h = 0;
		SDL_PrivateJoystickAxis (joystick, ax, h);
//		old_key = 0;
	}
	if ((key_release & KEY_A)) {
		SDL_PrivateJoystickButton (joystick, 0, SDL_RELEASED);
//		old_button = 0;
	}
	if ((key_release & KEY_B)) {
		SDL_PrivateJoystickButton (joystick, 1, SDL_RELEASED);
//		old_button = 0;
	}
	if ((key_release & KEY_X)) {
		SDL_PrivateJoystickButton (joystick, 2, SDL_RELEASED);
//		old_button = 0;
	}
	if ((key_release & KEY_Y)) {
		SDL_PrivateJoystickButton (joystick, 3, SDL_RELEASED);
//		old_button = 0;
	}
	if ((key_release & KEY_SELECT)) {
		SDL_PrivateJoystickButton (joystick, 6, SDL_RELEASED);
//		old_button = 0;
	}
	if ((key_release & KEY_START)) {
		SDL_PrivateJoystickButton (joystick, 7, SDL_RELEASED);
//		old_button = 0;
	}
	if ((key_release & KEY_L)) {
		SDL_PrivateJoystickButton (joystick, 4, SDL_RELEASED);
//		old_button = 0;
	}
	if ((key_release & KEY_R)) {
		SDL_PrivateJoystickButton (joystick, 5, SDL_RELEASED);
//		old_button = 0;
	}
}

void SDL_SYS_JoystickClose (SDL_Joystick *joystick) {
}

void SDL_SYS_JoystickQuit (void) {
}
