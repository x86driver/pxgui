#ifndef PLATFORM_H
#define PLATFORM_H

#define TARGET_PLATFORM_LEO

#ifdef TARGET_PLATFORM_LEO

const int DEFAULT_SCREEN_WIDTH = 480;
const int DEFAULT_SCREEN_HEIGHT = 272;

#else
#error "No platform define"
#endif

#endif

