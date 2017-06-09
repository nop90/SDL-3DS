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

#ifndef _SDL_n3dsvideo_h
#define _SDL_n3dsvideo_h

#include "../SDL_sysvideo.h"

#include <3ds.h>


/* Hidden "this" pointer for the video functions */
#define _THIS	SDL_VideoDevice *this

/* Private display data */

struct SDL_PrivateVideoData {
//GPU drawing specific
	int x1,y1,w1,h1; // drawing window for top screen          width and height of top screen part of the video buffer 
	int x2,y2,w2,h2; //drawing window for bottom screen  and height of bottom part of the video buffer
	float l1,r1,t1,b1; // GPU source window for the top part of the video buffer
	float l2,r2,t2,b2; // GPU source window for the bottom part of the video buffer
	float scalex,scaley; // scaling factors
	float scalex2,scaley2; // scaling factors

// framebuffer data
    int w, h; // width and height of the video buffer
    void *buffer;
	Uint8 *palettedbuffer;
	GSPGPU_FramebufferFormats mode;
	unsigned int flags; // backup of create device flags
	unsigned int screens; // SDL_TOPSCR, SDL_BOTTOMSCR, SDL_DUALSCR
	unsigned int console; // SDL_CONSOLETOP, SDL_CONSOLEBOTTOM
	unsigned int fitscreen; // SDL_TRIMBOTTOMSCR, SDL_FITWIDTH, SDL_FITHEIGHT (SDL_FULLSCREEN sets both SDL_FITWIDTH and SDL_FITHEIGHT)
	int byteperpixel;
	int bpp;
// video surface
	SDL_Surface* currentVideoSurface;	
// Video process flags
	bool blockVideo;  // block video output and events handlings on SDL_QUIT
};

#endif /* _SDL_n3dsvideo_h */
