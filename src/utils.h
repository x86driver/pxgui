#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
int read_sysfs(const char *path, char result[64]);

#ifdef  GUI_DEBUG
#define gui_dbg(format, arg...) LOGD(format, ##arg)
#else
#define gui_dbg(format, arg...) do {} while(0)
#endif


#endif
