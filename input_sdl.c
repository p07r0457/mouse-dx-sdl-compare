#include "main.h"

void grab_mouse( BOOL grab )
{
	SDL_WM_GrabInput( grab==1 ? SDL_GRAB_ON : SDL_GRAB_OFF );
	p("input state: %s\n",(grab==1?"grabbed":"free"));
}

px_timer_t sdl_mouse_timer;

void sdl_timer_init( void )
{
	timer_clear( &sdl_mouse_timer );
}

BOOL sdl_handle_events( void )
{
	static float runs = 0.0f;
	SDL_Event _event;

	runs++;

	while( SDL_PollEvent( &_event ) )
	{
		switch( _event.type )
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			{
				SDL_KeyboardEvent key = _event.key;
				if( key.keysym.sym == SDLK_ESCAPE )
					return FALSE;
			}
			break;

		case SDL_MOUSEMOTION:
			{
				//SDL_MouseMotionEvent motion = _event.motion;
				//p("x %d y %d\n", motion.xrel, motion.yrel);
				{
					//float seconds = timer_run( &sdl_mouse_timer );
					//float ms = seconds * 1000.0f;
					//float per_second = runs / seconds;
					//p("sdl/s: %f s:%f ms:%f r:%f\n",per_second,seconds,ms,runs);
					p("sdl runs: %f\n",runs);
					runs = 0.0f;
				}
			}
			break;

		case SDL_ACTIVEEVENT:
			{
				SDL_ActiveEvent active = _event.active;
				p("window active: %s\n", (active.gain?"true":"false"));
				grab_mouse( active.gain );
			}
			break;

		case SDL_QUIT:
			grab_mouse( FALSE );
			break;
		}
	}

	return TRUE;
}
