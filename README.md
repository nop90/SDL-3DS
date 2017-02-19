# SDL-3DS
SDL 1.2 for 3DS

   Simple DirectMedia Layer

												(SDL)

                                Version 1.2.15 Nintendo 3DS port
---

TOC
============

- Credits
- Video
- Key input
- Joystick
- Mousepointer
- Audio

VIDEO
============

This port of the SDL 1.2 lib to 3ds was made with the help of several coders of the 3ds scene: Xerpi, Rikku2000, Nop90, Wenting


VIDEO
============

the video device will be rendered centered on the HW screen (default screen is the TOP one) 

five bpp modes supported : 32 (RGBA8), 24 (RGB8), 16 (RGB565), 15 (RGB555_A1), 8 (paletted) 

With these video sizes can be used the following options:

- SDL_FULLSCREEN option stretchs the video device on the HW screen.
- SDL_TOPSCR: select the top screen for rendering the video device (it's the default option, so you don't really need to set this flag)
- SDL_BOTTOMSCR: select the bottom screen for rendering the video device
- SDL_DUALSCR: draws the upper half of the video device on the top screeen and the lower half on the bottom screen
- SDL_FITWIDTH: resizes the video device to fit the selected screen width (if SDL_DUALSCR is set, its' resized to 400 pixel width)
- SDL_FITHEIGHT: resizes the video device to fit the screen/screens height
- SDL_CONSOLETOP: enables console output on the top screen (only if SDL_TOPSCR or SDL_FULLSCREEN are not set)  
- SDL_CONSOLEBOTTOM: enables console output on the bottom screen (only if SDL_BOTTOMSCR or SDL_FULLSCREEN are not set)

Note: using the SDL_FULLSCREEN flag is the same of using (SDL_TOPSCR | SDL_BOTTOMSCR) 

KEY INPUT
============

Default key bindings are:

	KEY_A -> SDLK_a
	KEY_B -> SDLK_b
	KEY_X -> SDLK_x
	KEY_Y -> SDLK-y
	KEY_L -> SDLK_l
	KEY_R -> SDLK_r
	KEY_START -> SDLK_RETURN
	KEY_SELECT -> SDLK_ESCAPE
	KEY_RIGHT -> SDLK_RIGHT
	KEY_LEFT -> SDLK_LEFT
	SDLK_UP -> KEY_UP
	KEY_DOWN -> SDLK_DOWN
 
there is a custom function to bind one or more N3DS keys to a SDL key value:

 void SDL_N3DSKeyBind(unsigned int hidkey, SDLKey key)

NOTE: circle pad and C-Stick are not mapped to the direction key by default( circle pad is mapped to the default Joystick) but if someone wants to make this mapping he can use the following code:
	
	SDL_N3DSKeyBind(KEY_CPAD_UP|KEY_CSTICK_UP, SDLK_UP);
	SDL_N3DSKeyBind(KEY_CPAD_DOWN|KEY_CSTICK_DOWN, SDLK_DOWN);
	SDL_N3DSKeyBind(KEY_CPAD_LEFT|KEY_CSTICK_LEFT, SDLK_LEFT);
	SDL_N3DSKeyBind(KEY_CPAD_DOWN|KEY_CSTICK_DOWN, SDLK_DOWN);

It's not possible to bind a N3DS key to two or more SDL Key values.

JOYSTICK
============

Joystick support is enabled


MOUSEPOINTER
============

Mouse pointer is controlled with the touchpad. Touching the bottom screen controls the pointer position and trigger a left button click.


AUDIO
============

Audio uses the DSP, so to use it with a homebrew compiled as a CIA you need to dump the DSp Firm in the 3ds folder. 
Audio thread would have a higher priority than the main thread, but it would give main thread a fixed time to process the audio. If you are experiencing problems with the audio, try using a larger sample buffer or change the delay time in SDL_n3dsaudio.c

MULTITHREAD
============

Multithread is supported. But please bear in mind that due to the design of 3DS' OS, thread won't evenly share CPU time. You would have to use SDL_Delay to give other threads CPU time to run. All threads would be created with a higher priority than the main thread, and they would start running as soon as you create them.

TIMER
============

Working in progress.

---
http://www.libsdl.org/
