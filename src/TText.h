#ifndef TTEXTH
#define TTEXTH

#include <SDL_ttf.h>
#include <ft2build.h>
#include <freetype2/freetype/freetype.h>

#if defined(DOREMI_USE_USTL)
#  include <umap.h>
using namespace ustl;
#else
#  include <map>
using namespace std;
#endif

class FontManager {
public:
    static FontManager &getInstance();
    TTF_Font *getFont(int ptsize);

private:
    map<int, TTF_Font*> m;

    FontManager();
    ~FontManager();

    FontManager(const FontManager &);
    void operator=(const FontManager &);
};

class TText : public TGuiElement
{
public:
    TText(Pages *pages, int x, int y, int fsize, const char *name, const char *str);
    ~TText();
    void Draw();
    SDL_Surface *render();
    void setbgcolor(uint8_t r, uint8_t g, uint8_t b);
    void setfgcolor(uint8_t r, uint8_t g, uint8_t b);
    void settext(const char *str);
private:
    char *str;
    int fontsize;
    SDL_Color backcolor;
    SDL_Color forecolor;
    SDL_Surface *text;

    void setfontsize(int size);
    TText(const TText &);
    TText &operator=(const TText &);
};

#endif
