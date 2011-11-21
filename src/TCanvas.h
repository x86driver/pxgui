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

    void draw_HLine(Sint16 x1, Sint16 x2, Sint16 y, Uint32 Color);
    void draw_VLine(Sint16 x, Sint16 y1, Sint16 y2, Uint32 Color);
    void draw_Pixel(int x, int y, Uint32 color);

    virtual void Draw();
    virtual bool OnMouseUp();

private:
    NoCommand<CallbackType> nocmd;
    Functor<CallbackType> draw_cmd;
    Functor<CallbackType> click_cmd;
};

#endif
