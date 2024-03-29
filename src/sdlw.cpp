//---------------------------------------------------------------------------
#include <cstdlib>
#include <cctype>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "SDL.h"
#include "TGui.h"
#include "TPage.h"
#include "TText.h"
#include "TWindow.h"
#include "TButton.h"
#include "TTimer.h"
#include "TScreen.h"
#include "sdlw.h"
#include "platform.h"
#include "RGBPage.h"
#include "GeneralInfo.h"

//---------------------------------------------------------------------------

void show_me_money(void *widget)
{
    static bool visible = true;
    TText *txt = static_cast<TText*>(widget);
    txt->setVisible(visible);
    visible = !visible;
}

void *thread_update_text(void *widget)
{
    char buf[64];
    static int count = 0;
    SDL_Event user_event;
    TText *txt = static_cast<TText*>(widget);

    user_event.type = SDL_USEREVENT;
    user_event.user.code = REDRAW_ALL;

    auto &pm = PageManager::getInstance();

    while (1) {
        if (pm.getActivePage() != 2) {
            sleep(1);
            continue;
        }
        time_t t = time(NULL);
        snprintf(buf, sizeof(buf), "%s", ctime(&t));
        buf[strlen(buf)-1] = '\0';
        txt->settext(buf);
        SDL_PushEvent(&user_event);
        sleep(1);
    }

    return NULL;
}

class Page0 : public Pages {
public:
    Page0(int page, SDL_Surface *background = NULL) : Pages(page, background)
    {
        btn1 = new TButton(this, 100, 80, 80, 50, "btn1", "Next");
        btn2 = new TButton(this, 10, 80, 80, 50, "btn2", "上一頁");
        wnd1 = new TWindow(this, 10, 10, 50, 50, "wnd1", "Hello!");
        text1 = new TText(this, 50, 50, 24, "text1", "Fuck ^_^");

        addElement(btn1, btn2, wnd1, text1);

//        Functor<TButton::CallbackType> cmd1(show_me_money);
//        btn1->setClicked(cmd1, text1);
    }
    virtual int get_prev_page() const
    {
        return 3;
    }
    virtual TButton *get_switch_next_button() const
    {
        return btn1;
    }
    virtual TButton *get_switch_prev_button() const
    {
        return btn2;
    }
    virtual void onTimerEvent()
    {
        text1->settext("abc");
    }
private:
    TButton *btn1;
    TButton *btn2;
    TWindow *wnd1;
    TText   *text1;
};

class Page1 : public Pages
{
public:
    Page1(int page, SDL_Surface *background = NULL) : Pages(page, background)
    {
        backlight = 0;

        timer_control = new TButton(this, 30, 150, 80, 50, "btn_update", "Timer!幹");
        btn2 = new TButton(this, 300, 150, 100, 70, "btn2", "FUCK");
        mytext2 = new TText(this, 10, 10, 24, "text2", "Shit!");

        counter = new TText(this, 150, 10, 16, "counter", "Backlight:   0");

        up_btn = new TButton(this, 270, 10, 60, 40, "up", "UP");
        down_btn = new TButton(this, 270, 50, 60, 40, "down", "Down");

        mytext2->setfgcolor(200, 255, 200);
        mytext2->setbgcolor(50, 50, 255);

        addElement(btn2, mytext2, timer_control);
        addElement(up_btn, down_btn, counter);

        Functor<TButton::CallbackType> tcmd(this, &Page1::btn_clicked);
        timer_control->setClicked(tcmd, NULL);

        Functor<TButton::CallbackType> upcmd(this, &Page1::up_clicked);
        Functor<TButton::CallbackType> updelay(this, &Page1::up_delayed);
        Functor<TButton::CallbackType> downcmd(this, &Page1::down_clicked);
        Functor<TButton::CallbackType> downdelay(this, &Page1::down_delayed);

        up_btn->setClicked(upcmd);
        up_btn->setDelayed(updelay);
        down_btn->setClicked(downcmd);
        down_btn->setDelayed(downdelay);

        Functor<TimerCallback> cmd(this, &Page1::onTimerEvent);
        t = new TTimer(this, 1000, cmd);
    }
   virtual TButton *get_switch_next_button() const
    {
        return btn2;
    }
    virtual void onTimerEvent()
    {
        char buf[64];
        static int count = 0;
        snprintf(buf, sizeof(buf), "fuck me %d", count++);
        mytext2->settext(buf);
        refresh_all();
    }

private:
    void btn_clicked(void *data)
    {
        bool status = t->isRun();
        if (status == true)
            t->stop();
        else
            t->start();
    }

    void show_backlight()
    {
        char buf[64];
        snprintf(buf, sizeof(buf), "Backlight:   %d", backlight);
        counter->settext(buf);
        mytext2->bInvalidRect = true;
        refresh_all();
    }

    void up_clicked(void *data)
    {
        ++backlight;
        if (backlight > 100)
            backlight = 100;
        show_backlight();
    }

    void up_delayed(void *data)
    {
        backlight += 10;
        if (backlight > 100)
            backlight = 100;
        up_btn->bInvalidRect = true;
        show_backlight();
    }

    void down_clicked(void *data)
    {
        --backlight;
        if (backlight < 0)
            backlight = 0;
        show_backlight();
    }

    void down_delayed(void *data)
    {
        backlight -= 10;
        if (backlight < 0)
            backlight = 0;
        down_btn->bInvalidRect = true;
        show_backlight();
    }

private:
    int backlight;

private:
    TButton *btn2;
    TButton *timer_control;
    TButton *up_btn, *down_btn;
    TText   *counter;
    TText   *mytext2;
    TTimer  *t;
};

class Page2 : public Pages {
public:
    Page2(int page, SDL_Surface *background = NULL) : Pages(page, background)
    {
        btn3 = new TButton(this, 30, 200, 100, 50, "btn3", "BULLSHIT");
        mytext3 = new TText(this, 10, 140, 16, "text3", "我是帥哥宇");
        count = new TText(this, 130, 70, 20, "count", "count: ");

        addElement(btn3, mytext3, count);

        Functor<TimerCallback> cmd(this, &Page2::onTimerEvent);
        TTimer t(this, 1000, cmd);

//        Functor<void (void*)> btn_cmd(this, &Page2::onTimerEvent2);
//        btn_update->setClicked(btn_cmd, NULL);

    }
   virtual TButton *get_switch_next_button() const
    {
        return btn3;
    }
    virtual void onTimerEvent()
    {
        char buf[64];
        time_t t = time(NULL);

        printf("%s got timer event!\n", __FUNCTION__);
        snprintf(buf, sizeof(buf), "%s", ctime(&t));
        buf[strlen(buf)-1] = '\0';
        count->settext(buf);

        refresh();
    }

private:
    TButton *btn3;
    TText *mytext3;
    TText *count;
};

class Page3 : public Pages {
public:
    Page3(int page, SDL_Surface *background = NULL) : Pages(page, background)
    {
        btn = new TButton(this, 350, 210, 100, 50, "btn", "COW");

        Gui->AddElement(btn);

        Functor<TimerCallback> cmd(this, &Page3::onTimerEvent);
        TTimer t(this, 20, cmd);
    }
    virtual TButton *get_switch_next_button() const
    {
        return btn;
    }
    virtual void onTimerEvent()
    {
        draw();
        refresh();
    }

void _HLine(SDL_Surface *Surface, Sint16 x1, Sint16 x2, Sint16 y, Uint32 Color)
{
    if(x1>x2){Sint16 tmp=x1; x1=x2; x2=tmp;}

    SDL_Rect l;
    l.x=x1; l.y=y; l.w=x2-x1+1; l.h=1;

    SDL_FillRect(Surface, &l, Color);
}

void _VLine(SDL_Surface *Surface, Sint16 x, Sint16 y1, Sint16 y2, Uint32 Color)
{
    if(y1>y2){Sint16 tmp=y1; y1=y2; y2=tmp;}

    SDL_Rect l;
    l.x=x; l.y=y1; l.w=1; l.h=y2-y1+1;

    SDL_FillRect(Surface, &l, Color);
}

void sge_Rect(SDL_Surface *Surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
{
    _HLine(Surface,x1,x2,y1,color);
    _HLine(Surface,x1,x2,y2,color);
    _VLine(Surface,x1,y1,y2,color);
    _VLine(Surface,x2,y1,y2,color);
}

void draw()
{
    Uint32 halfHeight;
    Uint32 color;
    Uint32 target_color;

    Uint32 sBaseColor = 0xff000000;
    Uint32 sColors[] = {0x0000ff, 0x00ff00, 0xff0000};
    Uint32 sIntervals[] = {0x000001, 0x000100, 0x010000};

    static Uint32 mCount = DEFAULT_SCREEN_HEIGHT / 2;
    static Uint32 mColorSelect = 0;

    Uint32 i;

    color = sColors[mColorSelect];
    Uint32 interval = sIntervals[mColorSelect];

    halfHeight = DEFAULT_SCREEN_HEIGHT / 2;

    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = DEFAULT_SCREEN_WIDTH;
    rect.h = DEFAULT_SCREEN_HEIGHT;

    for (i = 0; i < halfHeight; ++i) {
        Uint32 diff = (((mCount - i) * 4) * interval) % color;

        Uint32 mycolor = sBaseColor+diff;
        target_color = SDL_MapRGBA(Gui->surface->format,
            (mycolor >> 16) & 0xff,
            (mycolor >> 8)  & 0xff,
            (mycolor)       & 0xff,
            (mycolor >> 24) & 0xff);

        sge_Rect(Gui->surface, halfHeight - i, (halfHeight - 1) - i,
             (DEFAULT_SCREEN_WIDTH - halfHeight) + i, halfHeight + i, target_color);

    }

//    SDL_Flip(screen);

    ++mCount;
    mCount = mCount % 0xff;
    if (mCount < halfHeight) {
        mCount = halfHeight;

        mColorSelect++;
        if (mColorSelect > 2) {
            mColorSelect = 0;
        }
    }
}

private:
    TButton *btn;
};

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
    ScreenManager &sm = ScreenManager::getInstance();
    SDL_Surface *background, *linuxback, *snoopy;
    SDL_Surface *white;

    background = sm.load_background("layout.bmp");
    linuxback  = sm.load_background("linux.bmp");
    snoopy     = sm.load_background("snoopy.bmp");
    white      = sm.create_background(0xff, 0xff, 0xff);

    Page0 page0(0, background);
    Page1 page1(1, linuxback);
    Page2 page2(2, snoopy);
    Page3 page3(3);
    RGBPage rgbpage(4);
    GeneralInfo general(5, white);

    PageManager &pm = PageManager::getInstance();

    pm.insert(&page0);
    pm.insert(&page1);
    pm.insert(&page2);
    pm.insert(&page3);
    pm.insert(&rgbpage);
    pm.insert(&general);

    pm.setActivePage(5);

    TimerManager::getInstance().start();

    sm.run();

    SDL_FreeSurface(background);
    SDL_FreeSurface(linuxback);
    SDL_FreeSurface(snoopy);

    return 0;
}
