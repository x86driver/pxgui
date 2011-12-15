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

#ifdef BUILD_FOR_ANDROID
    void update_temp();
    void update_battvol();
    void update_usblimit();
    void update_usbcurr();
    void update_sysfs(const char *sysfs, int col);
#endif

    void refresh_backlight();
    void up_backlight_clicked(void *data);
    void up_backlight_delayed(void *data);
    void down_backlight_clicked(void *data);
    void down_backlight_delayed(void *data);

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
        DATA1_SIZE,

        RAMTEST = DATA1_SIZE,
        ROMTEST,
        VMAX,
        POWERSRC,
        BACKLIGHT,
        BATTCUR,
        BATTCAP,
        USBID,
        CHARGEVOL,
        DATA2_SIZE = (CHARGEVOL+1)-DATA1_SIZE,
        DATA_SIZE = CHARGEVOL+1
    };

    enum { LINESKIP = 26 };
    enum { DATA_LEN = 32 };

    char  data[DATA_SIZE][DATA_LEN];
    TText *text_data[DATA_SIZE];

    TButton *exitbtn;
    TButton *backbtn;
    TButton *nextbtn;
    TButton *upbtn;
    TButton *downbtn;

    int backlight;
};

#endif
