#include "TPage.h"
#include <string.h>

PageManager::PageManager(TGui *active)
    : activeGui(active)
{
    memset(&pages[0], 0, sizeof(pages));
    activeGui->active = true;
}

/*
void PageManager::operator()()
{
    prev->active = false;
    next->active = true;
    next->RedrawAll();
    next->RedrawAll();
}
*/

void PageManager::operator()(void *data)
{
    switch_to(reinterpret_cast<intptr_t>(data));
}

void PageManager::insert(TGui *gui, int page)
{
    if (page >= 0 && page < MAX_PAGE)   // 0~255
        pages[page] = gui;
}

void PageManager::switch_to(int page)
{
    printf("switch page to %d, active: %p\n", page, activeGui);
    if (pages[page]) {
        activeGui->active = false;
        activeGui = pages[page];
        activeGui->active = true;
        activeGui->RedrawAll();
        activeGui->RedrawAll();
    }
    printf("now activeGui: %p\n", activeGui);
}

TGui *PageManager::getActive() const
{
    printf("getActive return: %p\n", activeGui);
    return this->activeGui;
}
