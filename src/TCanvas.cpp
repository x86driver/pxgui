#include "TCanvas.h"

TCanvas::TCanvas(Pages *pages, int x, int y, int width, int height, Functor<CallbackType> &draw_cmd)
    : TGuiElement(pages, x, y, width, height, "Canvas"),
      nocmd(),
      draw_cmd(draw_cmd),
      click_cmd(nocmd)
{
    Draw();
}

TCanvas::~TCanvas()
{
}

void TCanvas::setClicked(Functor<CallbackType> &cmd)
{
    click_cmd = cmd;
}

void TCanvas::setDrawed(Functor<CallbackType> &cmd)
{
    draw_cmd = cmd;
}

void TCanvas::Draw()
{
    draw_cmd(surface);
}

bool TCanvas::OnMouseUp()
{
    click_cmd(surface);
    return true;
}

void TCanvas::draw_HLine(Sint16 x1, Sint16 x2, Sint16 y, Uint32 Color)
{
    if(x1>x2){Sint16 tmp=x1; x1=x2; x2=tmp;}

    SDL_Rect l;
    l.x=x1; l.y=y; l.w=x2-x1+1; l.h=1;

    SDL_FillRect(surface, &l, Color);
}

void TCanvas::draw_VLine(Sint16 x, Sint16 y1, Sint16 y2, Uint32 Color)
{
    if(y1>y2){Sint16 tmp=y1; y1=y2; y2=tmp;}

    SDL_Rect l;
    l.x=x; l.y=y1; l.w=1; l.h=y2-y1+1;

    SDL_FillRect(surface, &l, Color);
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void TCanvas::draw_Pixel(int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        *p = color;
        break;

    case 2:
        *(Uint16 *)p = color;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        }
        else {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = color;
        break;

   default:
        break;           /* shouldn't happen, but avoids warnings */
    } // switch
}
