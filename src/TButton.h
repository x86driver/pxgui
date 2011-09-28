//---------------------------------------------------------------------------
#ifndef TButtonH
#define TButtonH

class TButton : public TGuiElement
{
private:
	char * caption;
	TColors Col;
	void __fastcall DrawBtnUp();
	void __fastcall DrawBtnDown();
public:
	TButton(TGui *Parent, int x, int y, int width, int height, char * name, char * caption);
	__fastcall ~TButton();
	void __fastcall Draw();
	bool __fastcall OnMouseDown();
	bool __fastcall OnMouseUp();
};
#endif
