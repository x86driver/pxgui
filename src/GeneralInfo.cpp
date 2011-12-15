#include "TTimer.h"
#include "GeneralInfo.h"
#include "utils.h"

#ifdef BUILD_FOR_ANDROID
#include <framework/switch_blade.h>
#include "sysfs.h"
#endif

GeneralInfo::GeneralInfo(int page, SDL_Surface *background)
    : Pages(page, background)
{
    backlight = 100;

    fill_data1();
    fill_data2();

    show_info1();
    show_data1();
    show_info2();
    show_data2();

    show_button();

    Functor<TimerCallback> cmd(this, &GeneralInfo::onTimerEvent);
    TTimer t(this, 1000, cmd);
}

void GeneralInfo::onTimerEvent()
{
    time_t t;
    char buf[32];
    struct tm *tm;

    t = time(NULL);
    tm = localtime(&t);

    snprintf(buf, sizeof(buf), "%s%02d:%02d:%02d",
        (tm->tm_hour < 12 ? "上午" : "下午"),
        (tm->tm_hour < 12 ? tm->tm_hour : tm->tm_hour - 12),
        tm->tm_min, tm->tm_sec);

    text_data[TIME]->settext(buf);

#ifdef BUILD_FOR_ANDROID
    update_temp();

    update_sysfs(SB_SYSFS_PATH_BATTERY_VOLTAGE, BATTVOL);
    update_sysfs(USB_LIMIT_CURRENT, ILIMITUSB);
    update_sysfs(SB_SYSFS_PATH_BATTERY_CURRENT, BATTCUR);
#endif

    refresh_all();
}

void GeneralInfo::show_info1()
{
    const char *info1[] = {
        "C/NO",
        "Freq",
        "Time",
        "Last Reset",
        "Temp",
        "Battery",
        "Batt Voltage",
        "I Limit USB",
        "USB Device",
        "Internal Flash"
    };

    const int nr_info1 = sizeof(info1) / sizeof(info1[0]);
    TText *text_info1[nr_info1];

    for (int i = 0; i < nr_info1; ++i) {
        text_info1[i] = new TText(this, 2, LINESKIP*i, 16, "info1", info1[i]);
        addElement(text_info1[i]);
    }

}

void GeneralInfo::fill_data1()
{
    strncpy(data[CNO],         "0.0", DATA_LEN);
    strncpy(data[FREQ],        "0.0Hz", DATA_LEN);
    strncpy(data[TIME],        "0:0:0", DATA_LEN);
    strncpy(data[LASTRESET],   "0:0:0", DATA_LEN);
    strncpy(data[TEMP],        "36.0", DATA_LEN);
    strncpy(data[BATTERY],     "Li-ion", DATA_LEN);
    strncpy(data[BATTVOL],     "4000", DATA_LEN);
    strncpy(data[ILIMITUSB],   "1300", DATA_LEN);
    strncpy(data[USB],         "Unknown", DATA_LEN);
    strncpy(data[FLASH],       "SanDisk", DATA_LEN);
}

void GeneralInfo::show_data1()
{
    for (int i = 0; i < DATA1_SIZE; ++i) {
        text_data[i] = new TText(this, 120, LINESKIP*i, 16, "data1", data[i]);
        addElement(text_data[i]);
    }
}

void GeneralInfo::show_info2()
{
    const char *info2[] = {
        "RAM Test",
        "ROM Test",
        "VMAX",
        "Power Src",
        "Backlight",
        "Batt Current",
        "Batt Capacity",
        "USB ID Volts",
        "Charge Volts"
    };

    const int nr_info2 = sizeof(info2) / sizeof(info2[0]);
    TText *text_info2[nr_info2];

    for (int i = 0; i < nr_info2; ++i) {
        text_info2[i] = new TText(this, 240, LINESKIP*i, 16, "info2", info2[i]);
        addElement(text_info2[i]);
    }

}

void GeneralInfo::fill_data2()
{
    strncpy(data[RAMTEST],     "Pass", DATA_LEN);
    strncpy(data[ROMTEST],     "Pass", DATA_LEN);
    strncpy(data[VMAX],        "0.0V", DATA_LEN);
    strncpy(data[POWERSRC],    "USB Type-B", DATA_LEN);
    snprintf(data[BACKLIGHT], sizeof(data[BACKLIGHT]), "%d", backlight);
    strncpy(data[BATTCUR],     "0", DATA_LEN);
    strncpy(data[BATTCAP],     "100", DATA_LEN);
    strncpy(data[USBID],       "1435", DATA_LEN);
    strncpy(data[CHARGEVOL],   "5097", DATA_LEN);
}

void GeneralInfo::show_data2()
{
    for (int i = DATA1_SIZE; i < DATA_SIZE; ++i) {
        text_data[i] = new TText(this, 360, LINESKIP*(i-DATA1_SIZE), 16, "data2", data[i]);
        addElement(text_data[i]);
    }
}

void GeneralInfo::show_button()
{
    const int x1 = 252;
    const int y1 = 236;
    const int width = 76;
    const int height = 36;

    exitbtn = new TButton(this, x1, y1, width, height, "exit", "Exit");
    backbtn = new TButton(this, x1+width, y1, width, height, "back", "Back");
    nextbtn = new TButton(this, x1+width*2, y1, width, height, "next", "Next");

    upbtn   = new TButton(this, x1+width*2, 110, width, height, "up", "Up");
    downbtn = new TButton(this, x1+width*2, 110+height, width, height, "down", "Down");

    Functor<TButton::CallbackType> upcmd(this, &GeneralInfo::up_backlight_clicked);
    Functor<TButton::CallbackType> downcmd(this, &GeneralInfo::down_backlight_clicked);
    Functor<TButton::CallbackType> updelay(this, &GeneralInfo::up_backlight_delayed);
    Functor<TButton::CallbackType> downdelay(this, &GeneralInfo::down_backlight_delayed);

    upbtn->setClicked(upcmd);
    upbtn->setDelayed(updelay);
    downbtn->setClicked(downcmd);
    downbtn->setDelayed(downdelay);

    addElement(exitbtn, backbtn, nextbtn);
    addElement(upbtn, downbtn);

}

void GeneralInfo::refresh_backlight()
{
    if (backlight < 5)
        backlight = 5;
    else if (backlight > 100)
        backlight = 100;

    snprintf(data[BACKLIGHT], sizeof(data[BACKLIGHT]), "%d", backlight);
    text_data[BACKLIGHT]->settext(data[BACKLIGHT]);
    refresh_all();
}

void GeneralInfo::down_backlight_clicked(void *data)
{
    --backlight;
    refresh_backlight();
}

void GeneralInfo::up_backlight_clicked(void *data)
{
    ++backlight;
    refresh_backlight();
}

void GeneralInfo::up_backlight_delayed(void *data)
{
    backlight += 10;
    upbtn->bInvalidRect = true;
    refresh_backlight();
}

void GeneralInfo::down_backlight_delayed(void *data)
{
    backlight -= 10;
    downbtn->bInvalidRect = true;
    refresh_backlight();
}

TButton *GeneralInfo::get_switch_next_button() const
{
    return nextbtn;
}

int GeneralInfo::get_next_page() const
{
    return 0;
}


#ifdef BUILD_FOR_ANDROID

void GeneralInfo::update_sysfs(const char *sysfs, int col)
{
    char result[64];

    memset(&result[0], 0, sizeof(result));
    read_sysfs(sysfs, result);
    result[strlen(result)-1] = '\0';

    text_data[col]->settext(result);
}

void GeneralInfo::update_temp()
{
    char result[64];
    char *p;
    read_sysfs(SB_SYSFS_PATH_BATTERY_TEMPERATURE, result);
    p = &result[strlen(result)-1];
    *p++ = '.';
    *p++ = '0';
    *p++ = '\0';
    text_data[TEMP]->settext(result);
}

#endif

