#include "TPage.h"
#include "TGui.h"
#include "TButton.h"
#include <string.h>

PageManager::PageManager()
    : activePage(0), activeGui(NULL), cmd_switch_page(this)
{
    memset(&pages[0], 0, sizeof(pages));
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
}

void PageManager::switch_to(int page)
{
    if (pages[page]) {
        activePage = page;
        activeGui->active = false;
        activeGui = pages[page];
        activeGui->active = true;
        activeGui->RedrawAll();
    }
}

TGui *PageManager::getActive() const
{
    return this->activeGui;
}

void PageManager::set_switch_button(TButton *btn, int target_page)
{
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

int PageManager::getActivePage() const
{
    return activePage;
}

extern SDL_Surface *screen;
Pages::Pages(int page_number, SDL_Surface *background)
        : page(page_number),
          Gui(new TGui(screen, background))
{
}

Pages::~Pages()
{
}

int Pages::get_page() const
{
    return page;
}

TGui *Pages::get_gui() const
{
    return Gui;
}
