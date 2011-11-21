#include <stdio.h>
#include "TGui.h"
#include "TText.h"
#include "TWindow.h"
#include "TTimer.h"
#include "TScreen.h"
#include "platform.h"
#include "RGBPage.h"


RGBPage::RGBPage(int page, SDL_Surface *background)
    : Pages(page, background)
{
//    rgb_button = new TButton(this, 0, 0, 480, 272, "rgb-btn", "");
//    rgb_button->setClicked(switch_rgb);
//    rgb_button->setVisible(false);

    Functor<TCanvas::CallbackType> draw_cmd(this, &RGBPage::onDraw);
    Functor<TCanvas::CallbackType> click_cmd(this, &RGBPage::onClick);

    canvas = new TCanvas(this, 0, 0, 480, 272, draw_cmd);
//    canvas->setDrawed(draw_cmd);
    canvas->setClicked(click_cmd);

//    change_color();

    addElement(canvas);
}

int RGBPage::get_next_page() const
{
    return 0;
}

void RGBPage::onClick(SDL_Surface *surface)
{
//    if (change_color() == true) {
//        PageManager::getInstance().set_switch_button(rgb_button, get_next_page());
//    }

    if (change_color(surface) == true) {
        PageManager::getInstance().switch_to(get_next_page());
    }
}

void RGBPage::onDraw(SDL_Surface *surface)
{
    change_color(surface);
}

bool RGBPage::change_color(SDL_Surface *surface)
{
    static uint32_t i = 0;
    static const SDL_Color color[] = {
        {0xff, 0x00, 0x00, 0x00},
        {0x00, 0xff, 0x00, 0x00},
        {0x00, 0x00, 0xff, 0x00},
        {0xff, 0xff, 0xff, 0x00},
        {0x00, 0x00, 0x00, 0x00}
    };

    if (i >= (sizeof(color)/sizeof(color[1]))) {
        i = 1;
        SDL_FillRect(surface, NULL, GetCol(surface, color[0]));
        return true;
    }

    SDL_FillRect(surface, NULL, GetCol(surface, color[i]));

    ++i;

    return false;
}
