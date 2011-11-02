//---------------------------------------------------------------------------
#ifndef TButtonH
#define TButtonH

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
    void *cmd_data;
    NoCommand<CallbackType> nocmd;
    Functor<CallbackType> cmd;

	void  DrawBtnUp();
	void  DrawBtnDown();
    void  render_text();
public:
	TButton(TGui *Parent, int x, int y, int width, int height, const char * name, const char * caption);
	 ~TButton();
	void  Draw();
    void  setfontsize(int size);
    void  setfontcolor(uint8_t r, uint8_t g, uint8_t b);
    void  setClicked(Functor<CallbackType> &cmd, void *data);
	bool  OnMouseDown();
	bool  OnMouseUp();

private:
    TButton(const TButton &);
    void operator=(const TButton &);
};
#endif
