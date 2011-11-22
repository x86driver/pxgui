//---------------------------------------------------------------------------
#ifndef TButtonH
#define TButtonH

#include "TGui.h"
#include "TGuiElement.h"
#include "TText.h"
#include "lib/functor.h"
#include "lib/tuple.h"

class TButton : public TGuiElement
{
public:
    typedef std::tuple_element<0, std::tuple<void (void*)>>::type CallbackType;

private:
	char * caption;
    int    fontsize;
    SDL_Color fontcolor;
	TColors Col;
    TGuiElement *cmd_widget;
    void *cmd_data, *delay_data;
    NoCommand<CallbackType> nocmd;
    Functor<CallbackType> cmd, delay_cmd;
    TText *txt;

	void  DrawBtnUp();
	void  DrawBtnDown();
    void  render_text();
public:
	TButton(Pages *pages, int x, int y, int width, int height, const char * name, const char * caption);
	 ~TButton();
	void  Draw();
    void  setfontsize(int size);
    void  setfontcolor(uint8_t r, uint8_t g, uint8_t b);
    void  setClicked(Functor<CallbackType> &cmd, void *data = NULL);
    void  setDelayed(Functor<CallbackType> &cmd, void *data = NULL);
	bool  OnMouseDown();
    bool  OnMouseDownDelay();
	bool  OnMouseUp();

private:
    TButton(const TButton &);
    void operator=(const TButton &);
};
#endif
