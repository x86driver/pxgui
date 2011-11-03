#ifndef TPAGEH
#define TPAGEH

#include "TGui.h"
#include "TButton.h"
#include "lib/functor.h"

const int MAX_PAGE = 256;

class PageManager {
public:
    PageManager();
    void operator()(void *data);
    void insert(TGui *gui, int page);
    void remove(int page);
    void set_switch_button(TButton *btn, int target_page);
    void setActivePage(int page);
    int  getActivePage() const;
    TGui *getActive() const;

private:
    int  activePage;
    TGui *activeGui;
    TGui *pages[MAX_PAGE];
    Functor<TButton::CallbackType> cmd_switch_page;

    void switch_to(int page);
    PageManager(const PageManager &);
    void operator=(const PageManager &);
};

#endif
