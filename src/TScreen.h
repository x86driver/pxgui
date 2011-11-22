#ifndef TScreenH
#define TScreenH

#include <SDL.h>

enum {
    REDRAW = 0,
    REDRAW_ALL
};

class ScreenManager {
public:
    void        run();
    static      ScreenManager &getInstance();
    SDL_Surface *load_background(const char * const filename);
    SDL_Surface *create_background(uint8_t r, uint8_t g, uint8_t b);
    SDL_Surface *get_screen() const;

private:
    ScreenManager();
    ~ScreenManager();

    SDL_Surface *screen;

private:    // not implement
    ScreenManager(const ScreenManager &);
    void operator=(const ScreenManager &);
};

#endif
