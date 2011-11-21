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
    void switch_to(int page);
    inline int  getActivePage() const;
    inline TGui *getActive() const;

private:
    int  activePage;
    TGui *activeGui;
    TGui *pages[MAX_PAGE];
    Functor<void (void*)> cmd_switch_page;

    PageManager();
//    void switch_to(int page);
    PageManager(const PageManager &);
    void operator=(const PageManager &);
};

class Pages {
public:
    Pages(int page_number, SDL_Surface *background = NULL);
    TGui *get_gui() const;

    void refresh();
    void refresh_all();
    template <typename T, typename... Args> void addElement(T &&t, Args&& ... args);
    inline  int get_page() const;
    virtual ~Pages();
    virtual void onTimerEvent() = 0;
    inline  virtual int get_next_page() const;
    inline  virtual int get_prev_page() const;
    virtual TButton *get_switch_next_button() const = 0;
    virtual TButton *get_switch_prev_button() const { return NULL; }

protected:
    int page;
    TGui *Gui;
private:
    void addElement();
    void addOneElement(TGuiElement *element);

    Pages(const Pages &);
    void operator=(const Pages &);
};

// PageManager inline implementations

TGui *PageManager::getActive() const
{
    return this->activeGui;
}

int PageManager::getActivePage() const
{
    return activePage;
}


// Pages inline implementations

int Pages::get_page() const
{
    return page;
}

int Pages::get_next_page() const
{
    return page+1;
}

int Pages::get_prev_page() const
{
    return ((page-1) < 0 ? 0 : page-1);
}

template <typename T, typename... Args>
void Pages::addElement(T &&widget, Args&&... args)
{
    addOneElement(widget);
    addElement(args...);
}

#endif
