#ifndef GeneralInfoH
#define GeneralInfoH

#include <SDL.h>
#include "TGui.h"
#include "TPage.h"
#include "TButton.h"
#include "TText.h"

class GeneralInfo : public Pages {
public:
    GeneralInfo(int page, SDL_Surface *background = NULL);

private:
    void show_info1();
    void show_info2();
    void show_data1();
    void show_data2();

    void fill_data1();
    void fill_data2();

    void show_button();

    virtual int get_next_page() const;
    virtual TButton *get_switch_next_button() const;
    virtual void onTimerEvent();

private:
    enum {
        CNO,
        FREQ,
        TIME,
        LASTRESET,
        TEMP,
        BATTERY,
        BATTVOL,
        ILIMITUSB,
        USB,
        FLASH,
        DATA1_SIZE
    };

    enum {
        RAMTEST,
        ROMTEST,
        VMAX,
        POWERSRC,
        BACKLIGHT,
        BATTCUR,
        BATTCAP,
        USBID,
        CHARGEVOL,
        DATA2_SIZE
    };

    enum { LINESKIP = 26 };
    enum { DATA_LEN = 32 };

    char  data1[DATA1_SIZE][DATA_LEN];
    char  data2[DATA2_SIZE][DATA_LEN];
    TText *text_data1[DATA1_SIZE];
    TText *text_data2[DATA2_SIZE];

    TButton *exitbtn;
    TButton *backbtn;
    TButton *nextbtn;
    TButton *upbtn;
    TButton *downbtn;
};

#endif
