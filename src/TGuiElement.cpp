//---------------------------------------------------------------------------
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "TGui.h"
#include "TGuiElement.h"

//---------------------------------------------------------------------------

TGuiElement::TGuiElement(TGui *Parent, int x, int y, int width, int height, const char * name)
    : x(x), y(y), lastx(x), lasty(y), zIndex(0),
      width(width), height(height), name(strdup(name)),
      bVisible(true), bDragable(false), bMouseFocus(false),
      bInvalidRect(true), ActiveAlpha(255), PassiveAlpha(255),
      surface(NULL), Parent(Parent)
{
    if (width < 0 || height < 0) {
        return;     // Do nothing, create surface later
    }

	SDL_PixelFormat *fmt = Parent->surface->format;
	surface = SDL_CreateRGBSurface( SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_SRCALPHA|SDL_HWACCEL|SDL_PREALLOC, width, height, fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);
	if(surface == NULL) {
		printf("Error creating GuiElement surface\n");
		exit(-1);
	}
}

TGuiElement::~TGuiElement()
{
	free(name);
	SDL_FreeSurface(surface);
}

void  TGuiElement::Blit()
{
	if(bMouseFocus)
		SDL_SetAlpha(surface, SDL_SRCALPHA, ActiveAlpha);
	else
		SDL_SetAlpha(surface, SDL_SRCALPHA, PassiveAlpha);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	if( -1 == SDL_BlitSurface( surface, NULL, Parent->surface, &dst ) ) {
		printf("Error on 1: %s\n", SDL_GetError());
	}
}

void  TGuiElement::Blit(int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if( -1 == SDL_BlitSurface( surface, NULL, Parent->surface, &dst ) ) {
        printf("Error on 2: %s\n", SDL_GetError());
	}
}

bool  TGuiElement::CheckMouse(int mx, int my)
{
	if( (mx >= x && mx <= x+width) && (my >= y && my <= y+height) ) {
		return true;
	}
	else {
		return false;
	}
}

void  TGuiElement::Drag(int xrel, int yrel)
{
	lastx = x;
	lasty = y;
	x += xrel;
	y += yrel;
}

void  TGuiElement::setVisible(bool visible)
{
    bVisible = visible;
    bInvalidRect = true;
    Draw();
}

void  TGuiElement::setAspect(int width, int height)
{
    this->width = width;
    this->height = height;

    if (surface)
        SDL_FreeSurface(surface);

    SDL_PixelFormat *fmt = Parent->surface->format;
    surface = SDL_CreateRGBSurface( SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_SRCALPHA|SDL_HWACCEL|SDL_PREALLOC, width, height, fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);
    if (surface == NULL) {
        printf("Error creating GuiElement surface\n");
        exit(-1);
    }

}

int   TGuiElement::getWidth() const
{
    return width;
}

int   TGuiElement::getHeight() const
{
    return height;
}
