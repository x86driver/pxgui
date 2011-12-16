//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>

#include "TGui.h"
#include "TGuiElement.h"
#include "TText.h"
#include "TButton.h"
#include "utils.h"
#include "platform.h"
//---------------------------------------------------------------------------

static const int FONT_SIZE = 16;

TButton::TButton(Pages *pages, int x, int y, int width, int height, const char * name, const char * caption)
    : TGuiElement(pages, x, y, width, height, name),
      caption(strdup(caption)), fontsize(FONT_SIZE),
      fontcolor({0, 0, 0, 0}), Col(),
      cmd_widget(NULL), cmd_data(NULL),
      nocmd(), cmd(nocmd), delay_cmd(nocmd),
      txt(NULL)
{
	// set colors
	Col.Border.r = 0x00; Col.Border.g = 0x00; Col.Border.b = 0x00;
	Col.CapBkg.r = 0x50; Col.CapBkg.g = 0xff; Col.CapBkg.b = 0x30;
	Col.CapTxt.r = 0xff; Col.CapTxt.g = 0xff; Col.CapTxt.b = 0xff;
	Col.CliBkg.r = 0xf0; Col.CliBkg.g = 0xf0; Col.CliBkg.b = 0xe0;
	Col.Light3D.r = 0xff; Col.Light3D.g = 0xff; Col.Light3D.b = 0xff;
	Col.Dim3D.r = 0x40; Col.Dim3D.g = 0x40; Col.Dim3D.b = 0x40;

	SDL_SetAlpha(surface, SDL_SRCALPHA, 255);

    txt = new TText(page, 0, 0, fontsize, "button text", caption);
    txt->setfgcolor(fontcolor.r, fontcolor.g, fontcolor.b);
    txt->setbgcolor(Col.CliBkg.r, Col.CliBkg.g, Col.CliBkg.b);

	Draw(); // draw element graphics on it's surface
}

TButton::~TButton()
{
	free(caption);
    delete txt;
}

void  TButton::render_text()
{
    if (strlen(caption) == 0) {
        printf("We can't handle text with zero length\n");
        exit(-1);
    }

    SDL_Surface *text_surface = txt->render();
    SDL_Rect dst;

    dst.x = (width - text_surface->w) / 2;
    dst.y = (height - text_surface->h) / 2;

    SDL_BlitSurface(text_surface, NULL, surface, &dst);

    SDL_FreeSurface(text_surface);
}

void  TButton::Draw()
{
    gui_dbg("Draw button [%s] up: %p\n", name, __builtin_return_address(0));
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

    txt->setbgcolor(Col.CliBkg.r, Col.CliBkg.g, Col.CliBkg.b);
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
	SDL_FillRect(surface, &bk, GetCol(surface, Col.CapBkg));

    txt->setbgcolor(Col.CapBkg.r, Col.CapBkg.g, Col.CapBkg.b);
    render_text();
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
    cmd(cmd_data);
	return true;
}

bool  TButton::OnMouseDownDelay()
{
    delay_cmd(delay_data);
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

void  TButton::setClicked(Functor<CallbackType> &cmd, void *data)
{
    this->cmd = cmd;
    this->cmd_data = data;
}

void  TButton::setDelayed(Functor<CallbackType> &cmd, void *data)
{
    this->delay_cmd = cmd;
    this->delay_data = data;
}
