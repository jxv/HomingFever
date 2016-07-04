#include "input.h"

#include <SDL.h>
#include "states.h"

SDL_Event event;
int keys[2048];
int enableJoystick = 0;

void input()
{
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				quit = 1;
			break;
			case SDL_KEYDOWN:			/* Button press. */
				keys[event.key.keysym.sym] = 1;
			break;
			case SDL_KEYUP:				/* Button release. */
				keys[event.key.keysym.sym] = 0;
			break;
			case SDL_JOYAXISMOTION:			/* Analog joystick movement. */
				if (!enableJoystick)
					break;

				switch(event.jaxis.axis)
				{
					case 0:		/* Axis 0 (left-right). */
						if(event.jaxis.value < -JOY_DEADZONE)
						{
							/* Left movement. */
							keys[SDLK_LEFT] = 1;
							keys[SDLK_RIGHT] = 0;
						}
						else if(event.jaxis.value > JOY_DEADZONE)
						{
							/* Right movement. */
							keys[SDLK_LEFT] = 0;
							keys[SDLK_RIGHT] = 1;
						}
						else
						{
							keys[SDLK_LEFT] = 0;
							keys[SDLK_RIGHT] = 0;
						}
					break;
					case 1:		/* Axis 1 (up-down). */
						if(event.jaxis.value < -JOY_DEADZONE)
						{
							/* Up movement. */
							keys[SDLK_UP] = 1;
							keys[SDLK_DOWN] = 0;
						}
						else if(event.jaxis.value > JOY_DEADZONE)
						{
							/* Down movement. */
							keys[SDLK_UP] = 0;
							keys[SDLK_DOWN] = 1;
						}
						else
						{
							keys[SDLK_UP] = 0;
							keys[SDLK_DOWN] = 0;
						}
					break;

					default:
					break;
				}
			break;

			default:
			break;
		}
	}
}
