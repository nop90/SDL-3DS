#ifndef _SDL_ROTATE_H_
#define _SDL_ROTATE_H_

#define FLIP_VERTICAL 1
#define FLIP_HORIZONTAL 2

Uint32 getpixel (SDL_Surface *surface, int x, int y);
void putpixel (SDL_Surface *surface, int x, int y, Uint32 pixel);

SDL_Surface *SDL_RotateSurface (SDL_Surface *Surface, float angle, float zoom);
SDL_Surface *SDL_FlipSurface (SDL_Surface *surface, int flags);

#endif
