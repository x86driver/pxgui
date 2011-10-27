//---------------------------------------------------------------------------

#ifndef TGuiElementH
#define TGuiElementH
//---------------------------------------------------------------------------

#include "TGui.h"

class TGuiElement
{
public:
	// virtuals
	virtual bool  OnMouseDown() { return false; }
	virtual bool  OnMouseUp() { return false; }
	virtual void OnMouseMove(int, int) { return; }

	TGuiElement(class TGui *Parent, int x, int y, int width, int height, const char *name);
	virtual ~TGuiElement();
	void  Blit();
	void  Blit(int x, int y);
	bool  CheckMouse(int mx, int my);
	void  Drag(int xrel, int yrel);
    void  setVisible(bool visible);
    void  setAspect(int width, int height);

    int x, y, lastx, lasty;
    int zIndex; // starting at 0, highest value = topmost
    int width;
    int height;
    char * name;
    bool bVisible;
    bool bDragable;
    bool bMouseFocus;
    bool bInvalidRect;

protected:
    unsigned char ActiveAlpha, PassiveAlpha;
    SDL_Surface * surface;
    class TGui * Parent;
    // virtuals
    virtual void  Draw() = 0;

private:
    TGuiElement(const TGuiElement &);
    void operator=(const TGuiElement &);
};
//-----------------------------------------------------------------------------------

#endif
