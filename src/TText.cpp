#include <string.h>
#include <wchar.h>
#include <SDL_ttf.h>
#include "TGui.h"
#include "TGuiElement.h"
#include "TText.h"
#include "utils.h"
#include "sdlw.h"
#include "platform.h"

#ifdef BUILD_FOR_ANDROID
    #define DEFAULT_FONT "/system/fonts/DroidSansFallback.ttf"
#else
    #define DEFAULT_FONT "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc"
#endif

TText::TText(Pages *pages, int x, int y, int fsize, const char *name, const char *str)
    : TGuiElement(pages, x, y, -1, -1, name),
      str(strdup(str)), fontsize(fsize * SCREEN_WIDTH_RATIO),
      backcolor({0xff, 0xff, 0xff, 0xff}),
      forecolor({0x00, 0x00, 0x00, 0x00}),
      text(NULL), font(NULL)
{
    if ( TTF_Init() < 0 ) {
        fprintf(stderr, "Couldn't initialize TTF: %s\n",SDL_GetError());
        SDL_Quit();
        return;
    }

    font = TTF_OpenFont(DEFAULT_FONT, fontsize);
    if ( font == NULL ) {
        fprintf(stderr, "Couldn't load %d pt font from %s: %s\n",
                    fontsize, DEFAULT_FONT, SDL_GetError());
    }

    text = render();

    SDL_SetAlpha(surface, SDL_SRCALPHA, 255);

    Draw();
}

TText::~TText()
{
    free(str);
    SDL_FreeSurface(text);
    TTF_CloseFont(font);
    TTF_Quit();
}

SDL_Surface *TText::render()
{
    if (strlen(str) == 0) {
        setAspect(0, 0);
        return NULL;
    }

    SDL_Surface *t = TTF_RenderUTF8_Shaded(font, str, forecolor, backcolor);

    if ( t == NULL ) {
        fprintf(stderr, "Couldn't render text: %s\n", SDL_GetError());
        TTF_CloseFont(font);
    }

    setAspect(t->w, t->h);

    return t;
}

void TText::Draw()
{
    if (!text)
        return;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = text->w;
    rect.h = text->h;

    if (bVisible == true) {
        if ( SDL_BlitSurface(text, NULL, surface, &rect) < 0 ) {
            fprintf(stderr, "Couldn't blit text to display: %s\n",
                                SDL_GetError());
        }
    } else {
        SDL_FillRect(surface, &rect, GetCol(surface, forecolor));
    }
}

void TText::setfontsize(int size)
{
    fontsize = size;
}

void TText::setbgcolor(uint8_t r, uint8_t g, uint8_t b)
{
    backcolor = {r, g, b, 0};
}

void TText::setfgcolor(uint8_t r, uint8_t g, uint8_t b)
{
    forecolor = {r, g, b, 0};
}

void TText::settext(const char *str)
{
    if (this->str)
        free(this->str);
    this->str = strdup(str);

    if (text)
        SDL_FreeSurface(text);
    text = render();

    Draw();

    bInvalidRect = true;
}

