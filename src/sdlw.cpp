//---------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>

#include "sdl.h"
#include "TGui.h"
#include "sdlw.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

using std::cout;

SDL_Surface *screen, *background;
bool LMB, MMB, RMB;

int main(int argc, char *argv[])
{
	if( -1 == SDL_Init(SDL_INIT_VIDEO) ) {
		MessageBox(NULL,"Error initializing SDL","Error",MB_OK|MB_ICONERROR);
		exit(-1);
	}

	atexit(SDL_Quit);

	// get video info
	const SDL_VideoInfo *inf;
	inf = SDL_GetVideoInfo();
	cout << "hw_available: " << inf->hw_available << "\n";
	cout << "wm_available: " << inf->wm_available << "\n";
	cout << "blit_hw: " << inf->blit_hw << "\n";
	cout << "blit_hw_CC: " << inf->blit_hw_CC << "\n";
	cout << "blit_hw_A: " << inf->blit_hw_A << "\n";
	cout << "blit_sw: " << inf->blit_sw << "\n";
	cout << "blit_sw_CC: " << inf->blit_sw_CC << "\n";
	cout << "blit_sw_A: " << inf->blit_sw_A << "\n";
	cout << "blit_fill: " << inf->blit_fill << "\n";
	cout << "video_mem: " << inf->video_mem << "\n";
	cout << "BitsPerPixel: " << (int)inf->vfmt->BitsPerPixel << "\n\n";

	screen = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_HWACCEL|SDL_PREALLOC);
	//screen = SDL_SetVideoMode(800, 600, 16, SDL_SWSURFACE|SDL_FULLSCREEN);
	if(screen == NULL) {
		MessageBox(NULL,"Error setting video mode!","Error",MB_OK|MB_ICONERROR);
		exit(-1);
	}

	background = SDL_LoadBMP("layout.bmp");
	if(background == NULL) {
		MessageBox(NULL,"Error creating background surfce!","Error",MB_OK|MB_ICONERROR);
		exit(-1);
	}

	// first time screen drawing
	SDL_BlitSurface(background, NULL, screen, NULL);
	SDL_Flip(screen);

	// create gui
	Gui = new TGui(screen);

	// add few elements
	Gui->AddElement( new TButton(Gui, 10, 571, 60, 18, "btn1", "CLICK") );
	Gui->AddElement( new TButton(Gui, 75, 571, 60, 18, "btn2", "CLICK") );
	Gui->AddElement( new TButton(Gui, 140, 571, 60, 18, "btn3", "CLICK") );
	Gui->AddElement( new TButton(Gui, 205, 571, 60, 18, "btn4", "CLICK") );
	Gui->AddElement( new TButton(Gui, 270, 571, 60, 18, "btn5", "CLICK") );

	Gui->AddElement( new TWindow(Gui, 10, 10, 300, 200, "wnd1", "Hello!") );
	Gui->AddElement( new TWindow(Gui, 30, 30, 400, 250, "wnd2", "Hello w2!") );
	Gui->AddElement( new TWindow(Gui, 50, 50, 500, 100, "wnd3", "Hello w3!") );

	// and show the results
	Gui->Redraw();

	LMB = MMB = RMB = false;
	bool Done = false;
	SDL_Event ev;

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
						//cout << "LMB Down\n";
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
						//cout << "LMB Up\n";
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
	return 1;
}


