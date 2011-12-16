#ifndef PLATFORM_H
#define PLATFORM_H

//#define TARGET_PLATFORM_LEO
#define TARGET_PLATFORM_SCORPIO

#if defined(TARGET_PLATFORM_LEO)

const int DEFAULT_SCREEN_WIDTH = 480;
const int DEFAULT_SCREEN_HEIGHT = 272;

const double SCREEN_WIDTH_RATIO = 1;
const double SCREEN_HEIGHT_RATIO = 1;

#define USE_DOUBLE_BUFFER       1

#elif defined(TARGET_PLATFORM_SCORPIO)

const int DEFAULT_SCREEN_WIDTH = 800;
const int DEFAULT_SCREEN_HEIGHT = 480;

const double SCREEN_WIDTH_RATIO = 1.7;
const double SCREEN_HEIGHT_RATIO = 1.8;

//#define USE_DOUBLE_BUFFER       1

#else
#error "No platform define"
#endif

#endif

