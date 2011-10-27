//---------------------------------------------------------------------------
#include <string.h>

#include "SDL.h"
#include "TGui.h"
#include "TGuiElement.h"
#include "TWindow.h"

//---------------------------------------------------------------------------

TWindow::TWindow(TGui *Parent, int x, int y, int width, int height, const char * name, const char * caption)
    : TGuiElement(Parent, x, y, width, height, name),
      Col(), caption(strdup(caption)),
      bkg(), cap(), cli()
{
	// set colors
	Col.Border.r = 0x00; Col.Border.g = 0x00; Col.Border.b = 0x00;
	Col.CapBkg.r = 0xF0; Col.CapBkg.g = 0xA0; Col.CapBkg.b = 0x00;
	Col.CapTxt.r = 0xff; Col.CapTxt.g = 0xff; Col.CapTxt.b = 0xff;
	Col.CliBkg.r = 0xff; Col.CliBkg.g = 0xff; Col.CliBkg.b = 0xff;

	PassiveAlpha = 96;

	Draw(); // draw element graphics on it's surface
}

TWindow::~TWindow()
{
    if (caption)
        free(caption);
}

bool  TWindow::OnMouseUp()
{
    bDragable = false;
    return false;
}

bool  TWindow::OnMouseDown()
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    
//    if( (mx>cap.x+x && mx<cap.x+cap.w+x) && (my>cap.y+y && my<cap.y+cap.h+y) )
//        bDragable = true;
    return false;
}

void  TWindow::Draw()
{
	int b = 1;
	int caph = 15;
	bkg.x = 0; bkg.y = 0; bkg.w = width; bkg.h = height;
	cap.x = b; cap.y = b; cap.w = width-2*b; cap.h = caph;
	cli.x = b; cli.y = caph+2*b; cli.w = width-2*b; cli.h = height-(caph+3*b);

	SDL_FillRect(surface, &bkg, GetCol(surface, Col.Border));
	SDL_FillRect(surface, &cap, GetCol(surface, Col.CapBkg));
	SDL_FillRect(surface, &cli, GetCol(surface, Col.CliBkg));
}
