#include <string.h>
#include <wchar.h>
#include <SDL_ttf.h>
#include "TGui.h"
#include "TGuiElement.h"
#include "TText.h"
#include "utils.h"
#include "font.h"
#include "sdlw.h"

#define CHAR_SPACING 3
#define LINE_SPACING 3

#define DEFAULT_FONT "/usr/share/cups/fonts/Monospace"

TText::TText(TGui *Parent, int x, int y, int fsize, char *name, char *str)
//    : TGuiElement(Parent, x, y, (8+CHAR_SPACING)*strlen(str), (8+LINE_SPACING), name)
    : TGuiElement(Parent, x, y, 100, 30, name)
{
    this->str = strdup(str);

    if ( TTF_Init() < 0 ) {
        fprintf(stderr, "Couldn't initialize TTF: %s\n",SDL_GetError());
        SDL_Quit();
        return;
    }

    font = TTF_OpenFont(DEFAULT_FONT, 24);
    if ( font == NULL ) {
        fprintf(stderr, "Couldn't load %d pt font from %s: %s\n",
                    24, DEFAULT_FONT, SDL_GetError());
//        cleanup(2);
    }

    SDL_SetAlpha(surface, SDL_SRCALPHA, 255);

    Draw();
}

TText::~TText()
{
    free(str);
    SDL_FreeSurface(text);
}

void TText::Draw()
{
    SDL_Color backcolor = {0xff, 0, 0, 0};
    SDL_Color forecolor = {0, 0, 0xff, 0};
    SDL_Rect dstrect;

    text = TTF_RenderText_Shaded(font, str, forecolor, backcolor);
    if ( text == NULL ) {
        fprintf(stderr, "Couldn't render text: %s\n", SDL_GetError());
        TTF_CloseFont(font);
    }

    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = text->w;
    dstrect.h = text->h;

    if ( SDL_BlitSurface(text, NULL, surface, &dstrect) < 0 ) {
        fprintf(stderr, "Couldn't blit text to display: %s\n", 
                                SDL_GetError());
        TTF_CloseFont(font);
    }
}

uint32_t get_font(unsigned char ascii)
{
    uint32_t inc = static_cast<uint32_t>(ascii);
    return inc * 8;
}

const struct font_desc *TText::fonts[] = {
    &font_vga_8x8
};

void TText::draw_bitmap( FT_Bitmap *bitmap, FT_Int x, FT_Int y)
{
    Uint32 color;
    FT_Int  i, j, p, q;
    FT_Int  x_max = x + bitmap->width;
    FT_Int  y_max = y + bitmap->rows;
    int row, pixel;

    if (SDL_MUSTLOCK(surface)) {
        if (SDL_LockSurface(surface) < 0) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

#if 0
    for (j = y, row = 0; row < face->glyph->bitmap.rows; ++j, ++row) {
        for (i = x, pixel = 0; pixel < face->glyph->bitmap.width; ++i, ++pixel){
            if (face->glyph->bitmap.buffer
                    [row * face->glyph->bitmap.pitch +
                     pixel / 8] & (0xC0 >> (pixel % 8))) {
                color = SDL_MapRGB(surface->format, 255, 0, 0);
                putpixel(surface, i, j, color);
            }
        }
    }
#endif

#if 1
    for ( i = x, p = 0; i < x_max; i++, p++ ) {
        for ( j = y, q = 0; j < y_max; j++, q++ ) {
            if ( i >= width || j >= height )
                continue;
            if (bitmap->buffer[q * bitmap->width + p]) {
                color = SDL_MapRGB(surface->format, bitmap->buffer[q * bitmap->width + p], 0, 0);
                putpixel(surface, i, j, color);
            }
        }
    }
#endif

    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

#if 0
void TText::drawtext(wchar_t *text)
{
    int num_chars, n;
    int x, y;
    num_chars = wcslen( text );
    FT_UInt glyph_index;

    for ( n = 0; n < num_chars; ++n ) {
        FT_Set_Transform( face, NULL, &pen );
//        glyph_index = FT_Get_Char_Index(face, text[n]);
//        FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
        FT_Load_Char( face, text[n], FT_LOAD_RENDER );

        x = slot->bitmap_left;
        y = height - slot->bitmap_top - 5;
        printf("orignal draw on (%d, %d)\n", slot->bitmap_left, slot->bitmap_top);
        draw_bitmap( &slot->bitmap, x, y);
//                 slot->bitmap_left,
//                 height - slot->bitmap_top );

        pen.x += slot->advance.x;
        pen.y += slot->advance.y;
    }

    // move to new line
    // FIXME: We don't support multi-line yet, thus we comment it.
    // pen.y -= FONT_SIZE *2 * 64;
    // pen.x  = 50 * 64;

}
#endif

#if 0
void TText::Draw()
{
    wchar_t text[] = L"Fucky";
    SDL_Rect r;

    r.x = x;
    r.y = y;
    r.w = width;
    r.h = height;
//    SDL_BlitSurface(background, &r, surface, NULL);
    r.x = r.y = 0;
    SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 0, 255, 0));
    drawtext(text);
}
#endif

#if 0
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
#endif
