#ifndef TScreenH
#define TScreenH

#include <SDL.h>

class ScreenManager {
public:
    void        run();
    static      ScreenManager &getInstance();
    SDL_Surface *load_background(const char * const filename);
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
