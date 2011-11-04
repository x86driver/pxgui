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
    PageManager();
    void operator()(void *data);
    void insert(Pages *page);
    void remove(int page);
    void set_switch_button(TButton *btn, int target_page);
    void setActivePage(int page);
    int  getActivePage() const;
    TGui *getActive() const;

private:
    int  activePage;
    TGui *activeGui;
    TGui *pages[MAX_PAGE];
//    Functor<TButton::CallbackType> cmd_switch_page;
    Functor<void (void*)> cmd_switch_page;

    void switch_to(int page);
    PageManager(const PageManager &);
    void operator=(const PageManager &);
};

class Pages {
public:
    Pages(int page_number, SDL_Surface *background = NULL);
    int get_page() const;
    TGui *get_gui() const;

    virtual ~Pages();
    virtual void onTimerEvent() = 0;
    virtual int get_next_page() = 0;
    virtual TButton *get_switch_button() = 0;

protected:
    int page;
    TGui *Gui;
private:
    Pages(const Pages &);
    void operator=(const Pages &);
};

#endif
