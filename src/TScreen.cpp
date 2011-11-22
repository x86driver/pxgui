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

SDL_Surface *ScreenManager::create_background(uint8_t r, uint8_t g, uint8_t b)
{
    SDL_PixelFormat *fmt = screen->format;
    SDL_Surface *surface = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_HWACCEL|SDL_PREALLOC, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);

    if (surface == NULL) {
	    printf("Error creating main GUI surface\n");
    	exit(-1);
    }

    Uint32 color = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, NULL, color);

    return surface;
}

SDL_Surface *ScreenManager::get_screen() const
{
    return screen;
}

void ScreenManager::run()
{
    static int button_timer = 0;
    const int delay = 1;
    bool LMB, MMB, RMB;
    PageManager &pm = PageManager::getInstance();

#ifdef BUILD_FOR_ANDROID
    SDL_ShowCursor(SDL_DISABLE);
#endif

    pm.getActive()->RedrawAll();

    SDL_UpdateRect(screen, 0, 0, 0, 0);

    LMB = MMB = RMB = false;
    bool Done = false;
    SDL_Event ev;
    SDL_Event old_ev;

    while( !Done  ) {
        SDL_Delay(delay);

#define THRESHOLD 200
        if (LMB == true) {
            button_timer += delay;
            if (button_timer > THRESHOLD) {
                pm.getActive()->OnMouseDown(old_ev.motion.x, old_ev.motion.y, true);
                button_timer = 0;
            }
        } else {
            button_timer = 0;
        }

	    if( SDL_PollEvent(&ev) == 0 ) {
	        continue;
    	}

    	switch(ev.type) {
    		case SDL_USEREVENT:
	            switch (ev.user.code) {
                    case REDRAW:
                        pm.getActive()->Redraw();
                        break;
                    case REDRAW_ALL:
                        pm.getActive()->RedrawAll();
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch(ev.button.button) {
                    case SDL_BUTTON_LEFT:
                        LMB = true;
                        old_ev = ev;
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
