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
	TWindow(TGui *Parent, int x, int y, int width, int height, char * name, char * caption);
	bool __fastcall OnMouseUp();
	bool __fastcall OnMouseDown();
	__fastcall ~TWindow();
	void __fastcall Draw();
};
//-----------------------------------------------------------------------------------

#endif
