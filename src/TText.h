#ifndef TTextH
#define TTextH

class TText : public TGuiElement
{
public:
    TText(TGui *Parent, int x, int y, char *name, char *str);
    ~TText();
    void Draw();
private:
    char *str;
    TColors Col;
    static const struct font_desc *fonts[];
};
#endif
