/* 
 * Triplane Classic - a side-scrolling dogfighting game.
 * Copyright (C) 1996,1997,2009  Dodekaedron Software Creations Oy
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * tjt@users.sourceforge.net
 */

/*******************************************************************************

   Purpose: 
   	Mouse handling part of Wsystem 2.0 for DJGPP v.2.0á5

*******************************************************************************/

#include "io/mouse.h"
#include "io/video.h"
#include <SDL.h>

#if defined(FAKE_MOUSE)
bool fake_left, fake_middle, fake_right;
#endif

void hiiri_to(int x, int y) {
    SDL_WarpMouse(x * pixel_multiplier, y * pixel_multiplier);
}

void koords(int *x, int *y, int *n1, int *n2) {
    Uint8 ret;

    SDL_PumpEvents();
    ret = SDL_GetMouseState(x, y);
    *n1 = !!(ret & SDL_BUTTON(1));
    *n2 = !!(ret & SDL_BUTTON(3));

#if defined(FAKE_MOUSE)
    if(fake_left)
    {
	*n1 = SDL_BUTTON(1);
	fake_left = false;
    }
    if(fake_right)
    {
	*n2 = SDL_BUTTON(3);
	fake_right = false;
    }
#endif

    *x /= pixel_multiplier;
    *y /= pixel_multiplier;

}

/**
 * Fake mouse events with keyboard
**/

#if defined(FAKE_MOUSE)
void fake_mouse(void) {
	SDL_Event e;
	int x;
	int y;
	static bool dirPressed[4];
	static bool slow_mouse;
	static int mouse_speed;

	SDL_GetMouseState(&x, &y);

	/* If the user wants to slow down the mouse cursor speed */
	if(slow_mouse)
	{
		mouse_speed = 1;			/* moves 1 pixel at a time */
	}
	else
	{
		mouse_speed = 5 * pixel_multiplier;	/* default mouse cursor speed */
	}

	//SDL_PumpEvents();
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT:
						dirPressed[0] = true;
					break;
					case SDLK_RIGHT:
						dirPressed[1] = true;
					break;
					case SDLK_UP:
						dirPressed[2] = true;
					break;
					case SDLK_DOWN:
						dirPressed[3] = true;
					break;
					case SDLK_LCTRL:
						fake_left = true;
					break;
					case SDLK_LALT:
						fake_right = true;
					break;
					case SDLK_TAB:
						slow_mouse = true;
					break;
					default:
					break;
				}
			break;
			case SDL_KEYUP:
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT:
						dirPressed[0] = false;
					break;
					case SDLK_RIGHT:
						dirPressed[1] = false;
					break;
					case SDLK_UP:
						dirPressed[2] = false;
					break;
					case SDLK_DOWN:
						dirPressed[3] = false;
					break;
					case SDLK_LCTRL:
						fake_left = false;
					break;
					case SDLK_LALT:
						fake_right = false;
					break;
					case SDLK_TAB:
						slow_mouse = false;
					break;
					default:
					break;
				}
			default:
			break;
		}
	}

	if(dirPressed[0])
	{
		x-=mouse_speed;
	}
	if(dirPressed[1])
	{
		x+=mouse_speed;
	}
	if(dirPressed[2])
	{
		y-=mouse_speed;
	}
	if(dirPressed[3])
	{
		y+=mouse_speed;
	}


	if(x < 0)
	{
		x = 0;
	}
	if(y < 0)
	{
		y = 0;
	}
	if(x > 320 * pixel_multiplier)
	{
		x = 320 * pixel_multiplier;
	}
	if(y > 200 * pixel_multiplier)
	{
		y = 200 * pixel_multiplier;
	}

	if(dirPressed[0] || dirPressed[1] || dirPressed[2] || dirPressed[3])
	{
		SDL_WarpMouse(x, y);
	}

}
#endif
