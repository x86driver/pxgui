//---------------------------------------------------------------------------

#ifndef TWindowH
#define TWindowH
//---------------------------------------------------------------------------

class TWindow : public TGuiElement
{
private:
	TColors Col;
	char * caption;
	SDL_Rect bkg, cap, cli;
public:
	TWindow(TGui *Parent, int x, int y, int width, int height, const char * name, const char * caption);
	bool  OnMouseUp();
	bool  OnMouseDown();
	 ~TWindow();
	void  Draw();

private:
    TWindow(const TWindow &);
    void operator=(const TWindow &);
};
//-----------------------------------------------------------------------------------

#endif
