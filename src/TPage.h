#ifndef TPAGEH
#define TPAGEH

#include "TGui.h"

const int MAX_PAGE = 256;

class PageManager {
public:
    PageManager(TGui *active);
    void operator()();
    void operator()(void *data);
    void insert(TGui *gui, int page);
    void remove(int page);
    void switch_to(int page);
    TGui *getActive() const;

private:
    TGui *activeGui;
    TGui *pages[MAX_PAGE];
};

#endif
