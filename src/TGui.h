//---------------------------------------------------------------------------

#ifndef TGuiH
#define TGuiH
//-----------------------------------------------------------------------------------

#include <sdl.h>

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
	void __fastcall RedrawElements();
	void __fastcall AddElement(TGuiElement * Element);
	void __fastcall RemoveElement(TGuiElement * Element);
	void __fastcall BlitAll();
	void __fastcall Blit(char * name);
	void __fastcall SetFocus(char * name);
	void __fastcall Redraw();
	void __fastcall OnMouseDown(int x, int y);
	void __fastcall OnMouseUp(int x, int y);
	void __fastcall Drag(int xrel, int yrel);
	// No description
	void OnMouseMove(int x, int y);
};
//-----------------------------------------------------------------------------------

extern TGui *Gui;
//-----------------------------------------------------------------------------------
#endif
