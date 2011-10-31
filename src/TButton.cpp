//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>

#include "TGui.h"
#include "TGuiElement.h"
#include "TButton.h"
//---------------------------------------------------------------------------

extern TText *mytext;

static const int FONT_SIZE = 16;

TButton::TButton(TGui *Parent, int x, int y, int width, int height, const char * name, const char * caption)
    : TGuiElement(Parent, x, y, width, height, name),
      caption(strdup(caption)), fontsize(FONT_SIZE),
      fontcolor({0, 0, 0, 0}), Col(),
      cmd_widget(NULL), cmd_data(NULL),
      nocmd(), cmd(nocmd)
{
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

void  TButton::render_text()
{
    TText *txt = new TText(Parent, 0, 0, fontsize, "button text", caption);
    txt->setfgcolor(fontcolor.r, fontcolor.g, fontcolor.b);
    SDL_Surface *text_surface = txt->render();
    SDL_Rect dst;
    dst.x = (width - text_surface->w) / 2;
    dst.y = (height - text_surface->h) / 2;
    SDL_BlitSurface(text_surface, NULL, surface, &dst);
    delete txt;
    SDL_FreeSurface(text_surface);
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

    render_text();
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

    render_text();
}

bool  TButton::OnMouseDown()
{
	DrawBtnDown();
    cmd(cmd_widget, cmd_data);
	bInvalidRect = true;
	return true;
}

bool  TButton::OnMouseUp()
{
	DrawBtnUp();
	bInvalidRect = true;
    if (cmd_widget)
        cmd_widget->bInvalidRect = true;    // We redraw the action widget
	return true;
}

void  TButton::setfontsize(int size)
{
    fontsize = size;
}

void  TButton::setfontcolor(uint8_t r, uint8_t g, uint8_t b)
{
    fontcolor = {r, g, b, 0};
}

void  TButton::setClicked(Functor<CallbackType> &cmd, TGuiElement *widget, void *data)
{
    this->cmd = cmd;
    this->cmd_widget = widget;
    this->cmd_data = data;
}
