//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>

#include "TGui.h"
#include "TGuiElement.h"
#include "TButton.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


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

void __fastcall TButton::Draw()
{
	DrawBtnUp();
}

void __fastcall TButton::DrawBtnUp()
{
	int b = 1;

	SDL_Rect tl = {0, 0, width, height};
	SDL_Rect br = {b, b, width-b, height-b};
	SDL_Rect bk = {b, b, width-2*b, height-2*b};

	SDL_FillRect(surface, &tl, GetCol(surface, Col.Light3D));
	SDL_FillRect(surface, &br, GetCol(surface, Col.Dim3D));
	SDL_FillRect(surface, &bk, GetCol(surface, Col.CliBkg));
}

void __fastcall TButton::DrawBtnDown()
{
	int b = 1;

	SDL_Rect tl = {0, 0, width, height};
	SDL_Rect br = {b, b, width-b, height-b};
	SDL_Rect bk = {b, b, width-2*b, height-2*b};

	SDL_FillRect(surface, &tl, GetCol(surface, Col.Dim3D));
	SDL_FillRect(surface, &br, GetCol(surface, Col.Light3D));
	SDL_FillRect(surface, &bk, GetCol(surface, Col.CliBkg));
}

bool __fastcall TButton::OnMouseDown()
{
	DrawBtnDown();
	bInvalidRect = true;
	return true;
}

bool __fastcall TButton::OnMouseUp()
{
	DrawBtnUp();
	bInvalidRect = true;
	return true;
}
