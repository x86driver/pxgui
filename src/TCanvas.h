#ifndef TCanvasH
#define TCanvasH

#include <SDL.h>
#include "TGui.h"
#include "TGuiElement.h"
#include "TPage.h"
#include "lib/functor.h"
#include "lib/tuple.h"

class TCanvas : public TGuiElement {
public:
    typedef std::tuple_element<0, std::tuple<void (SDL_Surface*)>>::type CallbackType;

    TCanvas(Pages *pages, int x, int y, int width, int height, Functor<CallbackType> &draw_cmd);
    ~TCanvas();

    void setClicked(Functor<CallbackType> &cmd);
    void setDrawed(Functor<CallbackType> &cmd);

    virtual void Draw();
    virtual bool OnMouseUp();

private:
    NoCommand<CallbackType> nocmd;
    Functor<CallbackType> draw_cmd;
    Functor<CallbackType> click_cmd;
};

#endif
