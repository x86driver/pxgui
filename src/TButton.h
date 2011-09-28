//---------------------------------------------------------------------------
#ifndef TButtonH
#define TButtonH

class TButton : public TGuiElement
{
private:
	char * caption;
	TColors Col;
	void  DrawBtnUp();
	void  DrawBtnDown();
public:
	TButton(TGui *Parent, int x, int y, int width, int height, char * name, char * caption);
	 ~TButton();
	void  Draw();
	bool  OnMouseDown();
	bool  OnMouseUp();
};
#endif
