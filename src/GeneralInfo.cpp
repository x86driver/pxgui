#include "TTimer.h"
#include "GeneralInfo.h"

GeneralInfo::GeneralInfo(int page, SDL_Surface *background)
    : Pages(page, background)
{
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

    text_data1[TIME]->settext(buf);

    refresh();
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
    strncpy(data1[CNO],         "0.0", DATA_LEN);
    strncpy(data1[FREQ],        "0.0Hz", DATA_LEN);
    strncpy(data1[TIME],        "0:0:0", DATA_LEN);
    strncpy(data1[LASTRESET],   "0:0:0", DATA_LEN);
    strncpy(data1[TEMP],        "36.0", DATA_LEN);
    strncpy(data1[BATTERY],     "Li-ion", DATA_LEN);
    strncpy(data1[BATTVOL],     "4000", DATA_LEN);
    strncpy(data1[ILIMITUSB],   "1300", DATA_LEN);
    strncpy(data1[USB],         "Unknown", DATA_LEN);
    strncpy(data1[FLASH],       "SanDisk", DATA_LEN);
}

void GeneralInfo::show_data1()
{
    for (int i = 0; i < DATA1_SIZE; ++i) {
        text_data1[i] = new TText(this, 130, LINESKIP*i, 16, "data1", data1[i]);
        addElement(text_data1[i]);
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
        text_info2[i] = new TText(this, 250, LINESKIP*i, 16, "info2", info2[i]);
        addElement(text_info2[i]);
    }

}

void GeneralInfo::fill_data2()
{
    strncpy(data2[RAMTEST],     "Pass", DATA_LEN);
    strncpy(data2[ROMTEST],     "Pass", DATA_LEN);
    strncpy(data2[VMAX],        "0.0V", DATA_LEN);
    strncpy(data2[POWERSRC],    "USB Type-B", DATA_LEN);
    strncpy(data2[BACKLIGHT],   "100", DATA_LEN);
    strncpy(data2[BATTCUR],     "0", DATA_LEN);
    strncpy(data2[BATTCAP],     "100", DATA_LEN);
    strncpy(data2[USBID],       "1435", DATA_LEN);
    strncpy(data2[CHARGEVOL],   "5097", DATA_LEN);
}

void GeneralInfo::show_data2()
{
    for (int i = 0; i < DATA2_SIZE; ++i) {
        text_data2[i] = new TText(this, 380, 26*i, 16, "data2", data2[i]);
        addElement(text_data2[i]);
    }
}

void GeneralInfo::show_button()
{
    const int x1 = 240;
    const int y1 = 230;
    const int width = 80;
    const int height = 36;

    exitbtn = new TButton(this, x1, y1, width, height, "exit", "Exit");
    backbtn = new TButton(this, x1+width, y1, width, height, "back", "Back");
    nextbtn = new TButton(this, x1+width*2, y1, width, height, "next", "Next");

    upbtn   = new TButton(this, x1+width*2, 100, width, height, "up", "Up");
    downbtn = new TButton(this, x1+width*2, 100+height, width, height, "down", "Down");

    addElement(exitbtn, backbtn, nextbtn);
    addElement(upbtn, downbtn);

}
