#ifndef TPAGEH
#define TPAGEH

#include "TGui.h"
#include "TButton.h"
#include "lib/functor.h"

const int MAX_PAGE = 256;

class PageManager {
public:
    PageManager(TGui *active);
    void operator()(void *data);
    void insert(TGui *gui, int page);
    void remove(int page);
    void set_switch_button(TButton *btn, int target_page);
    TGui *getActive() const;

private:
    TGui *activeGui;
    TGui *pages[MAX_PAGE];
    Functor<TButton::CallbackType> cmd_switch_page;

    void switch_to(int page);
    PageManager(const PageManager &);
    void operator=(const PageManager &);
};

#endif
