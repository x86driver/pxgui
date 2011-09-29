//---------------------------------------------------------------------------

#ifndef TGuiH
#define TGuiH
//-----------------------------------------------------------------------------------

#include <SDL.h>

typedef class TGui;

typedef struct {
	SDL_Color Border;
	SDL_Color CapBkg;
	SDL_Color CapTxt;
	SDL_Color CliBkg;
	SDL_Color Light3D;
	SDL_Color Dim3D;
} TColors;
#define GetCol(s, col) (SDL_MapRGB(s->format, col.r, col.g, col.b))
//-----------------------------------------------------------------------------------

#include "TGuiElement.h"
#include "TButton.h"
#include "TWindow.h"

class TGui
{
private:
	TGuiElement **zList;
	int Count;
	SDL_Rect dirty;
public:
	SDL_Surface *surface;
	TGui(SDL_Surface * screen);
	~TGui();
	void  RedrawElements();
	void  AddElement(TGuiElement * Element);
	void  RemoveElement(TGuiElement * Element);
	void  BlitAll();
	void  Blit(char * name);
	void  SetFocus(char * name);
	void  Redraw();
	void  OnMouseDown(int x, int y);
	void  OnMouseUp(int x, int y);
	void  Drag(int xrel, int yrel);
	// No description
	void OnMouseMove(int x, int y);
};
//-----------------------------------------------------------------------------------

extern TGui *Gui;
//-----------------------------------------------------------------------------------
#endif
