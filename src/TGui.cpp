//---------------------------------------------------------------------------
#include <stdlib.h>
#include "TGui.h"
#include "sdlw.h"
#include "platform.h"
//---------------------------------------------------------------------------

TGui::TGui(SDL_Surface * screen, SDL_Surface * background)
    : zList(NULL), Count(0), dirty(),
      screen(screen), background(background),
      surface(NULL),
      active(false)
{
	SDL_PixelFormat *fmt = screen->format;
	surface = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_HWACCEL|SDL_PREALLOC, screen->w, screen->h, fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);
	if(surface == NULL) {
		printf("Error creating main GUI surface\n");
		exit(-1);
	}

	// zindex ordered list
	zList = (TGuiElement **)calloc(256, sizeof(TGuiElement *));

	dirty.x = 0;
    dirty.y = 0;
	dirty.w = DEFAULT_SCREEN_WIDTH;
    dirty.h = DEFAULT_SCREEN_HEIGHT;
}

TGui::~TGui()
{
    for (int i = 0; i < Count; ++i)
        delete zList[i];
    SDL_FreeSurface(surface);
    free(zList);
}

void  TGui::RedrawElements()
{
	//TODO: Add your source code here
}

void  TGui::AddElement(TGuiElement * Element)
{
	if(Element == NULL) return;

	for(int i=0; i<Count; i++) {
		zList[i]->bMouseFocus = false;
		zList[i]->bInvalidRect = true;
	}

	Element->zIndex = Count; // assign zIndex
	zList[Count] = Element;  // add element to the zList
	Element->bMouseFocus = true;
	Element->bInvalidRect = true;
	Count++; // increase the Elements counter
	//Redraw(); FIXME
}

void  TGui::RemoveElement(TGuiElement * Element)
{
	int i = 0;

	if(Element == NULL) return;

	// first find our element in the list
	while( zList[i] ) {
		if( zList[i] == Element ) {
			// then delete it and shift all remaining Elements down
			// and re-zIndex them
			delete Element;
			while( zList[i+1] != NULL ) {
				zList[i+1]->zIndex = i;
				zList[i] = zList[i+1];
				i++;
			}
			zList[i] = NULL;
			Count--;
			break;
		} else {
			i++;
		}
	}
}

void  TGui::BlitAll()
{
	int i = 0;
	while(zList[i]) {
		zList[i]->Blit();
		i++;
	}
}

void  TGui::Blit(__attribute__((unused)) char * name)
{
	//TODO: Add your source code here
}

// Redraw iterates through elements list looking for bInvalidRect flag
// and computes one global dirty rectangle for updating changes 
void  TGui::Redraw()
{
	// find the smallest possible update rectangle
	//   [sx,sy]----+
	//    |         |
	//    |         |
	//    |         |
	//    +-----[dx,dy]

    if (!active) {
        SDL_Flip(screen);
        return;
    }

	int i = 0;
	int sx, sy, dx, dy, xl, xh, yl, yh;
	xl = xh = yl = yh = 0;
	sx = 480; // set dirty to max
	sy = 272;
	dx = 0;
	dy = 0;

#if 1
	while(zList[i]) {
        printf("Checking \033[1;33m%s\033[0;38m ...\n", zList[i]->name);
		if(zList[i]->bInvalidRect) {
            printf("\033[1;31m%s\033[0;38m will redraw\n", zList[i]->name);
			xl = zList[i]->x < zList[i]->lastx ? zList[i]->x : zList[i]->lastx;
			xh = zList[i]->x > zList[i]->lastx ? zList[i]->x+zList[i]->width : zList[i]->lastx+zList[i]->width;
			sx = sx > xl ? xl : sx;
			dx = dx < xh ? xh : dx;

			yl = zList[i]->y < zList[i]->lasty ? zList[i]->y : zList[i]->lasty;
			yh = zList[i]->y > zList[i]->lasty ? zList[i]->y+zList[i]->height : zList[i]->lasty+zList[i]->height;
			sy = sy > yl ? yl : sy;
			dy = dy < yh ? yh : dy;

			// add invalid rectangle into the dirty list
			zList[i]->bInvalidRect = false;
		}
		i++;
	}
	// compute the global dirty rectangle

    if (sx == 480 && sy == 272) {
        dirty.x = dirty.y = 0;
        dirty.w = 480;
        dirty.h = 272;
    } else {
	dirty.x = sx;
	dirty.y = sy;
	dirty.w = dx-sx;
	dirty.h = dy-sy;
    }
#endif
#if 0
    dirty.x = dirty.y = 0;
    dirty.w = 480;
    dirty.h = 272;
#endif

	//cout << "DRCT: " << dirty.x << ", " << dirty.y << ", " << dirty.w << ", " << dirty.h << "\n";
    printf("DRCT: %d, %d, %d, %d\n", dirty.x, dirty.y, dirty.w, dirty.h);

	// restore background
	SDL_BlitSurface( background, &dirty, surface, &dirty );

	// draw all elements
	BlitAll();

	// update main screen area
	SDL_BlitSurface( surface, &dirty, screen, &dirty );

	// and flip it
    SDL_Flip(screen);
}

void  TGui::RedrawAll()
{
    dirty.x = dirty.y = 0;
    dirty.w = 480;
    dirty.h = 272;

    printf("I will redraw all!\n");
    SDL_FillRect(surface, &dirty, 0);
    SDL_FillRect(screen, &dirty, 0);

    SDL_BlitSurface( background, &dirty, surface, &dirty );

    // draw all elements
    BlitAll();

    // update main screen area
    SDL_BlitSurface( surface, &dirty, screen, &dirty );

    // and flip it
    SDL_Flip(screen);
}

void  TGui::SetFocus(__attribute__((unused)) char * name)
{
	//TODO: Add your source code here
}

// Looks up the first topmost clicked Element end brings it to front
void  TGui::OnMouseDown(int x, int y)
{
	int i;
	TGuiElement *e;

	// start with topmost element
	i = Count;
	while( i ) {
		i--;

		// fetch hittest status
		bool hittest = zList[i]->CheckMouse(x, y);

		/////////////////////////////////
		// check for mouse focus change
		/////////////////////////////////

		// already has focus = break;
		if( hittest && zList[i]->bMouseFocus ) {
			if( zList[i]->OnMouseDown() )
				Redraw();
			return;
		}

		// else set it for the topmost element only
		if( hittest ) {
			// clear all MouseFocus flags
			for(int j=0; j<Count; j++)
				zList[j]->bMouseFocus = false;

			zList[i]->bMouseFocus = true;
			printf("%s got mouse focus.\n", zList[i]->name);
			// shift elements by one to free the last z-slot for this one
			e = zList[i];
			while( zList[i+1] != NULL )	{
				zList[i] = zList[i+1];
				zList[i]->zIndex = i;
				i++;
			}
			zList[i] = e;
			zList[i]->zIndex = i;
			zList[i]->OnMouseDown();
			
			// on mouse focus change invalidate all elements
			for(i=0; i<Count; i++)
				zList[i]->bInvalidRect = true;

			Redraw(); // eflect changes
			return;
		}
	} // elements loop

	// no hittest - clear any Focus flag and redraw the scene
	for(i=0; i<Count; i++)
		if( zList[i]->bMouseFocus ) {
			zList[i]->bMouseFocus = false;
			zList[i]->bInvalidRect = true;
		}
	Redraw();
}

void  TGui::OnMouseUp(__attribute__((unused)) int x, __attribute__((unused)) int y)
{
	int i=0;

	while( zList[i] ) {
		if( zList[i]->bMouseFocus )
			if( zList[i]->OnMouseUp() == true )
				Redraw();
		i++;
	}
}

void  TGui::Drag(int xrel, int yrel)
{
	if( zList[Count-1]->bDragable ) {
		zList[Count-1]->Drag(xrel, yrel);
		zList[Count-1]->bInvalidRect = true;
		Redraw();
	}
}

// No description
void TGui::OnMouseMove(int x, int y)
{
	int i=0;

	while( zList[i] ) {
		if( zList[i]->bMouseFocus ) {
			zList[i]->OnMouseMove(x, y); // on mouse moving fire the OnMouseMove. User can override the method to perform specific actions.
		}
		i++;
	}
}
