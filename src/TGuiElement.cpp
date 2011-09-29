//---------------------------------------------------------------------------
#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "TGui.h"
#include "TGuiElement.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TGuiElement::TGuiElement(TGui *Parent, int x, int y, int width, int height, char * name)
{
	SDL_PixelFormat *fmt = Parent->surface->format;
	surface = SDL_CreateRGBSurface( SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_SRCALPHA|SDL_HWACCEL|SDL_PREALLOC, width, height, fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);
	if(surface == NULL) {
		printf("Error creating GuiElement surface\n");
		exit(-1);
	}

	ActiveAlpha = 255;
	PassiveAlpha = 255;

	//SDL_SetAlpha(surface, SDL_SRCALPHA, Active);

	this->x = x;
	this->y = y;
	this->lastx = x;
	this->lasty = y;
	this->width = width;
	this->height = height;
	this->name = strdup(name);
	this->Parent = Parent;
	bMouseFocus = false;
	bDragable = false; // non-dragable by default
	bInvalidRect = true;
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
		printf("Error BlitSurface Element > Gui\n");
	}
}

void  TGuiElement::Blit(int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if( -1 == SDL_BlitSurface( surface, NULL, Parent->surface, &dst ) ) {
		printf("Error BlitSurface Element > Gui\n");
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

