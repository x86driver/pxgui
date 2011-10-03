#ifndef TTextH
#define TTextH

class TText : public TGuiElement
{
public:
    TText(TGui *Parent, int x, int y, int width, int height, char *name, char *str);
    ~TText();
    void Draw();
private:
    char *str;
    TColors Col;
};
#endif
