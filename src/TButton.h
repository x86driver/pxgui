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
	TButton(TGui *Parent, int x, int y, int width, int height, const char * name, const char * caption);
	 ~TButton();
	void  Draw();
	bool  OnMouseDown();
	bool  OnMouseUp();

private:
    TButton(const TButton &);
    void operator=(const TButton &);
};
#endif
