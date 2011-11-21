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
};

#endif
