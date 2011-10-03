#ifndef TTextH
#define TTextH

class TText : public TGuiElement
{
public:
    TText(TGui *Parent, int x, int y, char *name, char *str);
    ~TText();
    void draw();
private:
    char *str;
};
#endif
