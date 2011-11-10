#include <stdlib.h>
#include "platform.h"
#include "TGui.h"
#include "TScreen.h"
#include "TPage.h"

ScreenManager &ScreenManager::getInstance()
{
    static ScreenManager obj;
    return obj;
}

ScreenManager::ScreenManager()
    : screen(NULL)
{
    if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
    	printf("Error initializing SDL\n");
	    exit(-1);
    }

    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_HWACCEL|SDL_PREALLOC);
    if(screen == NULL) {
	    printf("Error setting video mode!\n");
		exit(-1);
	}

}

ScreenManager::~ScreenManager()
{
    if (screen)
        SDL_FreeSurface(screen);
}

SDL_Surface *ScreenManager::load_background(const char * const filename)
{
    SDL_Surface *s = SDL_LoadBMP(filename);
    if (s == NULL) {
        printf("Error creating background surfce: %s\n", SDL_GetError());
        exit(-1);
    }

    return s;
}

SDL_Surface *ScreenManager::get_screen() const
{
    return screen;
}

void ScreenManager::run()
{
    bool LMB, MMB, RMB;
    PageManager &pm = PageManager::getInstance();

    pm.getActive()->RedrawAll();

#ifdef BUILD_FOR_ANDROID
    SDL_ShowCursor(SDL_DISABLE);
#endif

    SDL_UpdateRect(screen, 0, 0, 0, 0);

    LMB = MMB = RMB = false;
    bool Done = false;
    SDL_Event ev;

    while( !Done  ) {
    	SDL_Delay(1);
	    if( SDL_PollEvent(&ev) == 0 ) {
	        continue;
    	}

    	switch(ev.type) {
    		case SDL_USEREVENT:
	            switch (ev.user.code) {
                    case REDRAW_ALL:
                    printf("redraw event!\n");
                    pm.getActive()->RedrawAll();
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch(ev.button.button) {
                    case SDL_BUTTON_LEFT:
                        LMB = true;
                        pm.getActive()->OnMouseDown(ev.motion.x, ev.motion.y);
                        break;

                    case SDL_BUTTON_MIDDLE:
                        MMB = true;
                        break;

                    case SDL_BUTTON_RIGHT:
                        RMB = true;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch(ev.button.button) {
                    case SDL_BUTTON_LEFT:
                        LMB = false;
                        pm.getActive()->OnMouseUp(ev.motion.x, ev.motion.y);
                        break;

                    case SDL_BUTTON_MIDDLE:
                        MMB = false;
                        break;

                    case SDL_BUTTON_RIGHT:
                        RMB = false;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                // Gui->OnMouseMove(ev.motion.x, ev.motion.y);
	            // if(LMB) Gui->Drag(ev.motion.xrel, ev.motion.yrel);
                break;

            case SDL_QUIT:
                Done = true;
                break;

            case SDL_KEYDOWN:
                switch(ev.key.keysym.sym) {
                    case SDLK_SPACE:
                        Done = true;
                        break;

                    default:
                    break;
                    }

            default:
                break;
        }
    }
}
