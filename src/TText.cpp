#include <string.h>
#include <wchar.h>
#include "TGui.h"
#include "TGuiElement.h"
#include "TText.h"
#include "utils.h"
#include "font.h"

#define CHAR_SPACING 3
#define LINE_SPACING 3

#define FONT_FILE "/usr/share/cups/fonts/Monospace"

TText::TText(TGui *Parent, int x, int y, int fsize, char *name, char *str)
//    : TGuiElement(Parent, x, y, (8+CHAR_SPACING)*strlen(str), (8+LINE_SPACING), name)
    : TGuiElement(Parent, x, y, 100, 30, name)
{
    this->str = strdup(str);

    FT_Init_FreeType( &library );
    FT_New_Face( library, FONT_FILE, 0, &face );
    //FT_Set_Char_Size(face, FONT_SIZE, 0, 400, 0);
    FT_Set_Pixel_Sizes(face, fsize, 0);
    slot = face->glyph;

    pen.x =  0;
    pen.y = 0;

    FT_Error error = FT_Select_Charmap( face, FT_ENCODING_UNICODE);
    if ( error != 0 ) {
        printf("select font error");
        perror("select font");
        exit(1);
    }

    SDL_SetAlpha(surface, SDL_SRCALPHA, 255);

    Draw();
}

TText::~TText()
{
    free(str);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
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

    if (SDL_MUSTLOCK(surface)) {
        if (SDL_LockSurface(surface) < 0) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

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

    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

void TText::drawtext(wchar_t *text)
{
    int num_chars, n;
    int x, y;
    num_chars = wcslen( text );

    for ( n = 0; n < num_chars; ++n ) {
        FT_Set_Transform( face, NULL, &pen );
        FT_Load_Char( face, text[n], FT_LOAD_RENDER );

        x = slot->bitmap_left;
        y = height - slot->bitmap_top - 5;
        printf("draw on (%d, %d)\n", x, y);
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

void TText::Draw()
{
    wchar_t text[] = L"Fucky";
    drawtext(text);
}

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
