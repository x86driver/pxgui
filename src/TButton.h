//---------------------------------------------------------------------------
#ifndef TButtonH
#define TButtonH

class TButton : public TGuiElement
{
private:
	char * caption;
    int    fontsize;
    SDL_Color fontcolor;
	TColors Col;
	void  DrawBtnUp();
	void  DrawBtnDown();
    void  render_text();
public:
	TButton(TGui *Parent, int x, int y, int width, int height, const char * name, const char * caption);
	 ~TButton();
	void  Draw();
    void  setfontsize(int size);
    void  setfontcolor(uint8_t r, uint8_t g, uint8_t b);
	bool  OnMouseDown();
	bool  OnMouseUp();

private:
    TButton(const TButton &);
    void operator=(const TButton &);
};
#endif
