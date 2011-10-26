//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>

#include "TGui.h"
#include "TGuiElement.h"
#include "TButton.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern TText *mytext;

TButton::TButton(TGui *Parent, int x, int y, int width, int height, char * name, char * caption) : TGuiElement(Parent, x, y, width, height, name)
{
	this->caption = strdup(caption);

	// set colors
	Col.Border.r = 0x00; Col.Border.g = 0x00; Col.Border.b = 0x00;
	Col.CapBkg.r = 0xF0; Col.CapBkg.g = 0xA0; Col.CapBkg.b = 0x00;
	Col.CapTxt.r = 0xff; Col.CapTxt.g = 0xff; Col.CapTxt.b = 0xff;
	Col.CliBkg.r = 0xC0; Col.CliBkg.g = 0xC0; Col.CliBkg.b = 0xC0;
	Col.Light3D.r = 0xff; Col.Light3D.g = 0xff; Col.Light3D.b = 0xff;
	Col.Dim3D.r = 0x40; Col.Dim3D.g = 0x40; Col.Dim3D.b = 0x40;

	SDL_SetAlpha(surface, SDL_SRCALPHA, 255);

	Draw(); // draw element graphics on it's surface
}

TButton::~TButton()
{
	free(caption);
}

void  TButton::Draw()
{
	DrawBtnUp();
}

void  TButton::DrawBtnUp()
{
    Sint16 b = 1;

    SDL_SetAlpha(surface, SDL_SRCALPHA, 255);

    SDL_Rect tl = {0, 0, static_cast<Uint16>(width), static_cast<Uint16>(height)};
    SDL_Rect br = {b, b, static_cast<Uint16>(width-b), static_cast<Uint16>(height-b)};
    SDL_Rect bk = {b, b, static_cast<Uint16>(width-2*b), static_cast<Uint16>(height-2*b)};

	SDL_FillRect(surface, &tl, GetCol(surface, Col.Light3D));
	SDL_FillRect(surface, &br, GetCol(surface, Col.Dim3D));
	SDL_FillRect(surface, &bk, GetCol(surface, Col.CliBkg));
}

void  TButton::DrawBtnDown()
{
    Sint16 b = 1;

    SDL_Rect tl = {0, 0, static_cast<Uint16>(width), static_cast<Uint16>(height)};
    SDL_Rect br = {b, b, static_cast<Uint16>(width-b), static_cast<Uint16>(height-b)};
    SDL_Rect bk = {b, b, static_cast<Uint16>(width-2*b), static_cast<Uint16>(height-2*b)};

	SDL_FillRect(surface, &tl, GetCol(surface, Col.Dim3D));
	SDL_FillRect(surface, &br, GetCol(surface, Col.Light3D));
	SDL_FillRect(surface, &bk, GetCol(surface, Col.CliBkg));
}

bool  TButton::OnMouseDown()
{
	DrawBtnDown();
	bInvalidRect = true;
	return true;
}

bool  TButton::OnMouseUp()
{
	DrawBtnUp();
	bInvalidRect = true;
    static bool showtext = false;
    mytext->setVisible(showtext);
    showtext -= 1;
	return true;
}
