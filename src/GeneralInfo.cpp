#include "GeneralInfo.h"
#include "TText.h"

GeneralInfo::GeneralInfo(int page, SDL_Surface *background)
    : Pages(page, background)
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
        text_info1[i] = new TText(this, 2, 27*i, 16, "text", info1[i]);
        addElement(text_info1[i]);
    }

}
