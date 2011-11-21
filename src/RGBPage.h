#ifndef RGBPAGE_H
#define RGBPAGE_H

#include "SDL.h"
#include "TPage.h"
#include "TButton.h"
#include "TCanvas.h"

class RGBPage : public Pages {
public:
    RGBPage(int page, SDL_Surface *background = NULL);
    virtual int get_next_page() const;
private:
    TCanvas *canvas;

    void onDraw(SDL_Surface *surface);
    void onClick(SDL_Surface *surface);

    bool change_color(SDL_Surface *surface);
    void rgb_clicked(void *data);
    virtual void onTimerEvent() {}
    virtual TButton *get_switch_next_button() const { return NULL; }

    enum {
        PAGE_RED = 0,
        PAGE_GREEN = 1,
        PAGE_BLUE = 2,
        PAGE_WHITE = 3,
        PAGE_BLACK = 4,
        PAGE_FLICKER_HORIZONTAL = 5,
        PAGE_FLICKER_VERTICAL = 6,
        PAGE_PATTERN_RECT = 7,
        PAGE_PATTERN_SOLID = 8,
        PAGE_PATTERN_CHECKER = 9,
        PAGE_LAST = PAGE_PATTERN_CHECKER
    };
};

#endif
