#ifndef TTEXTH
#define TTEXTH

#include <SDL_ttf.h>
#include <ft2build.h>
#include <freetype2/freetype/freetype.h>

class TText : public TGuiElement
{
public:
    TText(TGui *Parent, int x, int y, int fsize, char *name, char *str);
    ~TText();
    void Draw();
    SDL_Surface *render();
    void setfontsize(int size);
    void setbgcolor(uint8_t r, uint8_t g, uint8_t b);
    void setfgcolor(uint8_t r, uint8_t g, uint8_t b);
    void settext(const char *str);
private:
    char *str;
    int fontsize;
    SDL_Color backcolor;
    SDL_Color forecolor;
    SDL_Surface *text;
    TTF_Font *font;

    TText(const TText &);
    TText &operator=(const TText &);
};

#endif
