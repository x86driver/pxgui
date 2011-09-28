//---------------------------------------------------------------------------

#ifndef TGuiElementH
#define TGuiElementH
//---------------------------------------------------------------------------

#include "TGui.h"

class TGuiElement
{
protected:
	unsigned char ActiveAlpha, PassiveAlpha;
	SDL_Surface * surface;
	TGui * Parent;
	// virtuals
	virtual void __fastcall Draw() {};
public:
	// virtuals
	virtual bool __fastcall OnMouseDown() { return false; }
	virtual bool __fastcall OnMouseUp() { return false; }
	virtual void OnMouseMove(int, int) { return; }
	
	int x, y, lastx, lasty;
	int zIndex; // starting at 0, highest value = topmost
	int width;
	int height;
	char * name;
	bool bVisible;
	bool bDragable;
	bool bMouseFocus;
	bool bInvalidRect;
	TGuiElement(TGui *Parent, int x, int y, int width, int height, char *name);
	~TGuiElement();
	void __fastcall Blit();
	void __fastcall Blit(int x, int y);
	bool __fastcall CheckMouse(int mx, int my);
	void __fastcall Drag(int xrel, int yrel);
};
//-----------------------------------------------------------------------------------

#endif
