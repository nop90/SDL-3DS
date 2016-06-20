/*
	SDL_rotate: for SDL coded by Rikku2000

	Version: 0.2
*/

#include <math.h>
#include <SDL/SDL.h>

#include "SDL_rotate.h"

Uint32 getpixel (SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;
	}
}

void putpixel (SDL_Surface *surface, int x, int y, Uint32 pixel) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

SDL_Surface *SDL_RotateSurface (SDL_Surface *Surface, float angle, float zoom) {
	SDL_Surface *rotate;
	int mx, my, mxdest, mydest;
	int bx, by, i, j, w, h;
	float tcos, tsin;

	tcos = cos (angle * M_PI / 180.0f);
	tsin = sin (angle * M_PI / 180.0f);

	w = (int)ceil ((Surface->w * fabs (tcos) + Surface->h * fabs (tsin)) * zoom);
	h = (int)ceil ((Surface->w * fabs (tsin) + Surface->h * fabs (tcos)) * zoom);

	if (Surface->flags & SDL_SRCCOLORKEY)
		rotate = SDL_CreateRGBSurface (SDL_SWSURFACE, w, h, Surface->format->BitsPerPixel, Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, 0);
	else
		rotate = SDL_CreateRGBSurface (SDL_SWSURFACE, w, h, Surface->format->BitsPerPixel, Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
	if (rotate == NULL)
		return NULL;

	mxdest = (int)rotate->w / 2;
	mydest = (int)rotate->h / 2;
	mx = (int)Surface->w / 2;
	my = (int)Surface->h / 2;

	if (SDL_MUSTLOCK (Surface))
		SDL_LockSurface (Surface);

	for (j = 0; j < rotate->h; j++) {
		for (i = 0; i < rotate->w; i++) {
			bx = mx + (int)((tcos * (i - mxdest) + tsin * (j - mydest)) / zoom);
			by = my + (int)((-tsin * (i - mxdest) + tcos * (j - mydest)) / zoom);

			Uint32 pixel = getpixel (Surface, bx, by);
			if (bx >= 0 && bx < Surface->w && by >= 0 && by < Surface->h)
				putpixel (rotate, i, j, pixel);
		}
	}

	if (SDL_MUSTLOCK (Surface))
		SDL_UnlockSurface (Surface);

	if (Surface->flags & SDL_SRCCOLORKEY)
		SDL_SetColorKey (rotate, SDL_RLEACCEL | SDL_SRCCOLORKEY, Surface->format->colorkey);

	return rotate;
}

SDL_Surface *SDL_FlipSurface (SDL_Surface *Surface, int flags) {
	SDL_Surface *flip = NULL;
	int rx, x, ry, y;

	if (Surface->flags & SDL_SRCCOLORKEY)
		flip = SDL_CreateRGBSurface (SDL_SWSURFACE, Surface->w, Surface->h, Surface->format->BitsPerPixel, Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, 0);
	else
		flip = SDL_CreateRGBSurface (SDL_SWSURFACE, Surface->w, Surface->h, Surface->format->BitsPerPixel, Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

	if (SDL_MUSTLOCK (Surface))
		SDL_LockSurface (Surface);

	for (x = 0, rx = flip->w - 1; x < flip->w; x++, rx--) {
		for (y = 0, ry = flip->h - 1; y < flip->h; y++, ry--) {
			Uint32 pixel = getpixel (Surface, x, y);

			if ((flags & FLIP_VERTICAL) && (flags & FLIP_HORIZONTAL)) {
				putpixel (flip, rx, ry, pixel);
			} else if (flags & FLIP_HORIZONTAL) {
				putpixel (flip, rx, y, pixel);
			} else if (flags & FLIP_VERTICAL) {
				putpixel (flip, x, ry, pixel);
			}
		}
	}

	if (SDL_MUSTLOCK (Surface))
		SDL_UnlockSurface (Surface);

	if (Surface->flags & SDL_SRCCOLORKEY)
		SDL_SetColorKey (flip, SDL_RLEACCEL | SDL_SRCCOLORKEY, Surface->format->colorkey);

	return flip;
}
