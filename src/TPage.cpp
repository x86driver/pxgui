#include "TPage.h"
#include "TGui.h"
#include "TButton.h"
#include "TScreen.h"
#include <string.h>

PageManager::PageManager()
    : activePage(-1), activeGui(NULL), cmd_switch_page(this)
{
    memset(&pages[0], 0, sizeof(pages));
}

PageManager &PageManager::getInstance()
{
    static PageManager obj;
    return obj;
}

void PageManager::operator()(void *data)
{
    switch_to(reinterpret_cast<intptr_t>(data));
}

void PageManager::insert(Pages *page)
{
    int n = page->get_page();
    if (n >= 0 && n < MAX_PAGE)   // 0~255
        pages[n] = page->get_gui();

    set_switch_button(page->get_switch_next_button(), page->get_next_page());
    set_switch_button(page->get_switch_prev_button(), page->get_prev_page());
}

void PageManager::switch_to(int page)
{
    printf("switch from %d to %d\n", activePage, page);
    if (pages[page]) {
        printf("do switch page!\n");
        activePage = page;
        activeGui->active = false;
        activeGui = pages[page];
        activeGui->active = true;
        activeGui->RedrawAll();
    } else
        printf("don't switch page!\n");
}

void PageManager::set_switch_button(TButton *btn, int target_page)
{
    if (btn)
        btn->setClicked(cmd_switch_page, (void*)target_page);
}

void PageManager::setActivePage(int page)
{
    if (pages[page]) {
        activePage = page;
        activeGui = pages[page];
        activeGui->active = true;
    }
}

extern SDL_Surface *screen;
Pages::Pages(int page_number, SDL_Surface *background)
        : page(page_number),
          Gui(new TGui(ScreenManager::getInstance().get_screen(), background))
{
}

Pages::~Pages()
{
}

TGui *Pages::get_gui() const
{
    return Gui;
}

void Pages::refresh()
{
    SDL_Event user_event;
    user_event.type = SDL_USEREVENT;
    user_event.user.code = REDRAW;
    SDL_PushEvent(&user_event);
}

void Pages::refresh_all()
{
    SDL_Event user_event;
    user_event.type = SDL_USEREVENT;
    user_event.user.code = REDRAW_ALL;
    SDL_PushEvent(&user_event);
}
