#ifndef GeneralInfoH
#define GeneralInfoH

#include <SDL.h>
#include "TGui.h"
#include "TPage.h"
#include "TButton.h"

class GeneralInfo : public Pages {
public:
    GeneralInfo(int page, SDL_Surface *background = NULL);

private:
    virtual TButton *get_switch_next_button() const { return NULL; }
    virtual void onTimerEvent() {}

private:
};

#endif
