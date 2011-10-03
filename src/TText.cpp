#include <string.h>
#include "TGui.h"
#include "TGuiElement.h"
#include "TText.h"
#include "utils.h"
#include "font.h"

#define CHAR_SPACING 3
#define LINE_SPACING 3

TText::TText(TGui *Parent, int x, int y, char *name, char *str)
//    : TGuiElement(Parent, x, y, width, height, name)
    : TGuiElement(Parent, x, y, (8+CHAR_SPACING)*strlen(str), (8+LINE_SPACING), name)
{
    this->str = strdup(str);

    Col.Border.r = 0x00; Col.Border.g = 0x00; Col.Border.b = 0x00;
    Col.CapBkg.r = 0xF0; Col.CapBkg.g = 0xA0; Col.CapBkg.b = 0x00;
    Col.CapTxt.r = 0xff; Col.CapTxt.g = 0xff; Col.CapTxt.b = 0xff;
    Col.CliBkg.r = 0xC0; Col.CliBkg.g = 0xC0; Col.CliBkg.b = 0xC0;
    Col.Light3D.r = 0xff; Col.Light3D.g = 0xff; Col.Light3D.b = 0xff;
    Col.Dim3D.r = 0x40; Col.Dim3D.g = 0x40; Col.Dim3D.b = 0x40;

    SDL_SetAlpha(surface, SDL_SRCALPHA, 255);

    Draw();
}

TText::~TText()
{
    free(str);
}

uint32_t get_font(unsigned char ascii)
{
    uint32_t inc = static_cast<uint32_t>(ascii);
    return inc * 8;
}

const struct font_desc *TText::fonts[] = {
    &font_vga_8x8
};

void TText::Draw()
{
    Uint32 yellow = SDL_MapRGB(surface->format, 255, 0, 0);

    if (SDL_MUSTLOCK(surface)) {
        if (SDL_LockSurface(surface) < 0) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

    unsigned char ch;
    const unsigned char *chptr = static_cast<const unsigned char*>(fonts[0]->data);
    chptr += get_font('A');

    int x, y;
    for (y = 0; y < 8; ++y) {
        x = 0;
        ch = *chptr++;
        while (ch) {
            if (ch & 1) {
                putpixel(surface, x, y, yellow);
            }
            ch >>= 1;
            ++x;
        }
    }

    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}
