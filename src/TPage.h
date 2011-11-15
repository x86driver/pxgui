#ifndef TPAGEH
#define TPAGEH

//#include "TGui.h"
//#include "TButton.h"
#include <stddef.h>
#include <SDL.h>
#include "lib/functor.h"

const int MAX_PAGE = 256;

class TGui;
class TGuiElement;
class TButton;
class Pages;

class PageManager {
public:
    static PageManager &getInstance();
    void operator()(void *data);
    void insert(Pages *page);
    void remove(int page);
    void set_switch_button(TButton *btn, int target_page);
    void setActivePage(int page);
    inline int  getActivePage() const;
    inline TGui *getActive() const;

private:
    int  activePage;
    TGui *activeGui;
    TGui *pages[MAX_PAGE];
//    Functor<TButton::CallbackType> cmd_switch_page;
    Functor<void (void*)> cmd_switch_page;

    PageManager();
    void switch_to(int page);
    PageManager(const PageManager &);
    void operator=(const PageManager &);
};

class Pages {
public:
    Pages(int page_number, SDL_Surface *background = NULL);
    TGui *get_gui() const;

    void refresh();
    void refresh_all();
    inline  int get_page() const;
    virtual ~Pages();
    virtual void onTimerEvent() = 0;
    virtual int get_next_page() const = 0;
    virtual int get_prev_page() const { return 0; }
    virtual TButton *get_switch_next_button() const = 0;
    virtual TButton *get_switch_prev_button() const { return NULL; }

protected:
    int page;
    TGui *Gui;
private:
    Pages(const Pages &);
    void operator=(const Pages &);
};

TGui *PageManager::getActive() const
{
    return this->activeGui;
}

int PageManager::getActivePage() const
{
    return activePage;
}

int Pages::get_page() const
{
    return page;
}

#endif
