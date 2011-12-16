#include <stdio.h>
#include "TGui.h"
#include "TText.h"
#include "TWindow.h"
#include "TTimer.h"
#include "TScreen.h"
#include "platform.h"
#include "RGBPage.h"


RGBPage::RGBPage(int page, SDL_Surface *background)
    : Pages(page, background),
      canvas(NULL)
{
    Functor<TCanvas::CallbackType> draw_cmd(this, &RGBPage::onDraw);
    Functor<TCanvas::CallbackType> click_cmd(this, &RGBPage::onClick);

    canvas = new TCanvas(this, 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, draw_cmd);
    canvas->setClicked(click_cmd);

    addElement(canvas);
}

void RGBPage::onClick(SDL_Surface *surface)
{
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
    static const Uint32 black = SDL_MapRGBA(surface->format, 0x00, 0x00, 0x00, 0x00);
    static const SDL_Color color[] = {
        {0xff, 0x00, 0x00, 0x00},
        {0x00, 0xff, 0x00, 0x00},
        {0x00, 0x00, 0xff, 0x00},
        {0xff, 0xff, 0xff, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x80, 0x80, 0x80, 0x00}
    };

    if (index <= PAGE_BLACK) {
        SDL_FillRect(surface, NULL, GetCol(surface, color[index]));
    } else {
        SDL_FillRect(surface, NULL, GetCol(surface, color[5]));
    }

    switch (index) {
        case PAGE_FLICKER_HORIZONTAL:
            for (int i = 0; i < height; ++i) {
                if ((i % 2) != 0) {
                    canvas->draw_HLine(0, width, i, black);
                }
            }
            break;

        case PAGE_FLICKER_VERTICAL:
            for (int i = 0; i < width; ++i) {
                if ((i % 2) != 0) {
                    canvas->draw_VLine(i, 0, height, black);
                }
            }
            break;

        case PAGE_PATTERN_RECT:
            SDL_Rect rect;
            rect.x = width / 4;
            rect.y = height / 4;
            rect.w = width / 2;
            rect.h = height / 2;
            SDL_FillRect(surface, &rect, black);
            break;

        case PAGE_PATTERN_CHECKER:
            int x, y, count;
            Uint32 color1, color2, color3, white;

            count = 0;
            color1 = SDL_MapRGBA(surface->format, 0x55, 0x55, 0x55, 0x55);
            color2 = SDL_MapRGBA(surface->format, 0xaa, 0xaa, 0xaa, 0xaa);
            color3 = SDL_MapRGBA(surface->format, 0xff, 0xff, 0xff, 0xaa);
            white  = SDL_MapRGBA(surface->format, 0xff, 0xff, 0xff, 0xff);

            for (x = 0; x < width; ++x) {
                for (y = 0; y < height; ++y) {
                    if ((count % 2) == 0) {
                        canvas->draw_Pixel(x, y, color1);
                    } else {
                        canvas->draw_Pixel(x, y, color2);
                    }
                }
                ++count;
            }

            x = (width / 2) - 1;
            y = (height / 2) - 1;
            canvas->draw_VLine(x, 0, height, color3);
            canvas->draw_VLine(x + 1, 0, height, color3);
            canvas->draw_HLine(0, width, y, color3);
            canvas->draw_HLine(0, width, y + 1, color3);

            canvas->draw_Rect(0, 0, width, height, white);
            canvas->draw_Rect(1, 1, width - 1, height - 1, black);
            canvas->draw_Rect(2, 2, width - 2, height - 2, white);
            canvas->draw_Rect(3, 3, width - 3, height - 3, black);

            break;

        default:
            break;
    }

    if (index > PAGE_LAST) {
        index = 1;
        SDL_FillRect(surface, NULL, GetCol(surface, color[0]));
        return true;
    }

    ++index;
    return false;
}
