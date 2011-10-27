//---------------------------------------------------------------------------
#ifndef TButtonH
#define TButtonH

class TButton : public TGuiElement
{
private:
	char * caption;
    int    fontsize;
	TColors Col;
	void  DrawBtnUp();
	void  DrawBtnDown();
    void  render_text();
public:
	TButton(TGui *Parent, int x, int y, int width, int height, const char * name, const char * caption);
	 ~TButton();
	void  Draw();
    void  setfontsize(int size);
	bool  OnMouseDown();
	bool  OnMouseUp();

private:
    TButton(const TButton &);
    void operator=(const TButton &);
};
#endif
