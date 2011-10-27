//---------------------------------------------------------------------------
#include <cstdlib>
#include <cctype>

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "TGui.h"
#include "sdlw.h"
#include "platform.h"

//---------------------------------------------------------------------------


SDL_Surface *screen, *background;
bool LMB, MMB, RMB;

void show_me_money(TGuiElement *widget, void *data)
{
    static bool visible = true;
    TText *txt = static_cast<TText*>(widget);
    txt->setVisible(visible);
    visible = !visible;
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
	if( -1 == SDL_Init(SDL_INIT_VIDEO) ) {
		printf("Error initializing SDL\n");
		exit(-1);
	}

	atexit(SDL_Quit);

	// get video info
	const SDL_VideoInfo *inf;
	inf = SDL_GetVideoInfo();
	printf("hw_available: %d\n", inf->hw_available);
	printf("wm_available: %d\n", inf->wm_available);
	printf("blit_hw: %d\n", inf->blit_hw);
	printf("blit_hw_CC: %d\n", inf->blit_hw_CC);
	printf("blit_hw_A: %d\n", inf->blit_hw_A);
	printf("blit_sw: %d\n", inf->blit_sw);
	printf("blit_sw_CC: %d\n", inf->blit_sw_CC);
	printf("blit_sw_A: %d\n", inf->blit_sw_A);
	printf("blit_fill: %d\n", inf->blit_fill);
	printf("video_mem: %d\n", inf->video_mem);
	printf("BitsPerPixel: %d\n\n", (int)inf->vfmt->BitsPerPixel);

	screen = SDL_SetVideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_HWACCEL|SDL_PREALLOC);
	if(screen == NULL) {
		printf("Error setting video mode!\n");
		exit(-1);
	}

	background = SDL_LoadBMP("layout.bmp");
	if(background == NULL) {
		printf("Error creating background surfce!\n");
		exit(-1);
	}

	// first time screen drawing
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_Flip(screen);

	// create gui
	Gui = new TGui(screen);

	// add few elements
    TButton *btn1 = new TButton(Gui, 10, 80, 80, 50, "btn1", "CLICK");
    Gui->AddElement(btn1);
//	Gui->AddElement( new TButton(Gui, 10, 80, 80, 50, "btn1", "CLICK") );
//	Gui->AddElement( new TButton(Gui, 75, 571, 60, 18, "btn2", "CLICK") );
//	Gui->AddElement( new TButton(Gui, 140, 571, 60, 18, "btn3", "CLICK") );
//	Gui->AddElement( new TButton(Gui, 205, 571, 60, 18, "btn4", "CLICK") );
//	Gui->AddElement( new TButton(Gui, 270, 571, 60, 18, "btn5", "CLICK") );

	Gui->AddElement( new TWindow(Gui, 10, 10, 50, 50, "wnd1", "Hello!") );
//	Gui->AddElement( new TWindow(Gui, 30, 30, 150, 150, "wnd2", "Hello w2!") );
//	Gui->AddElement( new TWindow(Gui, 0, 0, 480, 272, "wnd3", "Hello w3!") );

    TText *mytext = new TText(Gui, 50, 50, 24, "text1", "Fuck");
    Gui->AddElement(mytext);

    Functor<TButton::CallbackType> cmd1(show_me_money);
    btn1->setClicked(cmd1, mytext, NULL);

	// and show the results
	Gui->Redraw();

	LMB = MMB = RMB = false;
	bool Done = false;
	SDL_Event ev;

#ifdef BUILD_FOR_ANDROID
    SDL_ShowCursor(SDL_DISABLE);
#endif

    SDL_UpdateRect(screen,0,0,0,0);

    Gui->RedrawAll();

	while( !Done  )
	{
		SDL_Delay(1);
		if( SDL_PollEvent(&ev) == 0 ) {
			continue;
		}
		switch(ev.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch(ev.button.button)
				{
					case SDL_BUTTON_LEFT:
						LMB = true;
						Gui->OnMouseDown(ev.motion.x, ev.motion.y);
						//printf << "LMB Down\n";
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
				switch(ev.button.button)
				{
					case SDL_BUTTON_LEFT:
						LMB = false;
						Gui->OnMouseUp(ev.motion.x, ev.motion.y);
						//printf << "LMB Up\n";
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
			   Gui->OnMouseMove(ev.motion.x, ev.motion.y);
				if(LMB) Gui->Drag(ev.motion.xrel, ev.motion.yrel);
				break;
			case SDL_QUIT:
				Done = true;
				break;
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym)
				{
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

    delete Gui;
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);

	return 1;
}


