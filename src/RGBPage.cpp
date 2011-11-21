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
    const int width = DEFAULT_SCREEN_WIDTH;
    const int height = DEFAULT_SCREEN_HEIGHT;

    static uint32_t index = 0;
    static const SDL_Color color[] = {
        {0xff, 0x00, 0x00, 0x00},
        {0x00, 0xff, 0x00, 0x00},
        {0x00, 0x00, 0xff, 0x00},
        {0xff, 0xff, 0xff, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x80, 0x80, 0x80, 0x00}
    };

#if 0
    if (i >= (sizeof(color)/sizeof(color[1]))) {
        i = 1;
        SDL_FillRect(surface, NULL, GetCol(surface, color[0]));
        return true;
    }
#endif

    switch (index) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            SDL_FillRect(surface, NULL, GetCol(surface, color[index]));
            break;
        default:
            SDL_FillRect(surface, NULL, GetCol(surface, color[5]));
            break;
    }

    SDL_Color black = {0, 0, 0, 0};

    switch (index) {
        case PAGE_FLICKER_HORIZONTAL:
            for (int i = 0; i < height; ++i) {
                if ((i % 2) != 0) {
                    canvas->draw_HLine(0, width, i, GetCol(surface, black));
                }
            }
            break;

        case PAGE_FLICKER_VERTICAL:
            for (int i = 0; i < width; ++i) {
                if ((i % 2) != 0) {
                    canvas->draw_VLine(i, 0, height, GetCol(surface, black));
                }
            }
            break;

        case PAGE_PATTERN_RECT:
            SDL_Rect rect;
            rect.x = width / 4;
            rect.y = height / 4;
            rect.w = width / 2;
            rect.h = height / 2;
            SDL_FillRect(surface, &rect, GetCol(surface, black));
            break;

        case PAGE_PATTERN_CHECKER:
            SDL_Color color1 = {0x55, 0x55, 0x55, 0x55};
            SDL_Color color2 = {0xaa, 0xaa, 0xaa, 0xaa};
            SDL_Color color3 = {0xff, 0xff, 0xff, 0xaa};
            int count = 0;
            int x, y;

            for (x = 0; x < width; ++x) {
                for (y = 0; y < height; ++y) {
                    if ((count % 2) == 0) {
                        canvas->draw_Pixel(x, y, GetCol(surface, color1));
                    } else {
                        canvas->draw_Pixel(x, y, GetCol(surface, color2));
                    }
                }
            }

            x = (width / 2) - 1;
            y = (height / 2) - 1;
            canvas->draw_VLine(x, 0, height, GetCol(surface, color3));
            canvas->draw_VLine(x + 1, 0, height, GetCol(surface, color3));
            canvas->draw_HLine(0, width, y, GetCol(surface, color3));
            canvas->draw_HLine(0, width, y + 1, GetCol(surface, color3));

            break;
    }

    ++index;
    return false;
}
