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
    Page0(SDL_Surface *background = NULL) : Pages(get_page(), background)
    {
        btn1 = new TButton(this, 10, 80, 80, 50, "btn1", "CLICK");
        wnd1 = new TWindow(this, 10, 10, 50, 50, "wnd1", "Hello!");
        text1 = new TText(this, 50, 50, 24, "text1", "Fuck ^_^");

        Gui->AddElement(btn1);
        Gui->AddElement(wnd1);
        Gui->AddElement(text1);

//        Functor<TButton::CallbackType> cmd1(show_me_money);
//        btn1->setClicked(cmd1, text1);
    }

    virtual int get_page()
    {
        return 0;
    }
    virtual int get_next_page()
    {
        return 1;
    }
   virtual TButton *get_switch_button()
    {
        return btn1;
    }
    virtual void onTimerEvent()
    {
        text1->settext("abc");
    }
private:
    TButton *btn1;
    TWindow *wnd1;
    TText   *text1;
};

class Page1 : public Pages
{
public:
    Page1(SDL_Surface *background = NULL) : Pages(get_page(), background)
    {
        timer_control = new TButton(this, 30, 150, 80, 50, "btn_update", "Timer!");
        btn2 = new TButton(this, 300, 150, 100, 70, "btn2", "FUCK");
        mytext2 = new TText(this, 10, 10, 24, "text2", "Shit!");

        mytext2->setfgcolor(200, 255, 200);
        mytext2->setbgcolor(50, 50, 255);

        Gui->AddElement(btn2);
        Gui->AddElement(mytext2);
        Gui->AddElement(timer_control);

        Functor<TButton::CallbackType> tcmd(this, &Page1::btn_clicked);
        timer_control->setClicked(tcmd, NULL);

        Functor<TimerCallback> cmd(this, &Page1::onTimerEvent);
        t = new TTimer(this, 500, cmd);
    }
    virtual int get_page()
    {
        return 1;
    }
    virtual int get_next_page()
    {
        return 2;
    }
   virtual TButton *get_switch_button()
    {
        return btn2;
    }
    virtual void onTimerEvent()
    {
        char buf[64];
        static int count = 0;
        snprintf(buf, sizeof(buf), "fuck me %d", count++);
        mytext2->settext(buf);
        refresh();
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

private:
    TButton *btn2;
    TButton *timer_control;
    TText   *mytext2;
    TTimer  *t;
};

class Page2 : public Pages {
public:
    Page2(SDL_Surface *background = NULL) : Pages(get_page(), background)
    {
        btn3 = new TButton(this, 30, 200, 100, 50, "btn3", "BULLSHIT");
        mytext3 = new TText(this, 10, 140, 16, "text3", "I'm bull shit");
        count = new TText(this, 130, 70, 20, "count", "count: ");

        Gui->AddElement(btn3);
        Gui->AddElement(mytext3);
        Gui->AddElement(count);

        Functor<TimerCallback> cmd(this, &Page2::onTimerEvent);
        TTimer t(this, 1000, cmd);

//        Functor<void (void*)> btn_cmd(this, &Page2::onTimerEvent2);
//        btn_update->setClicked(btn_cmd, NULL);

    }
    virtual int get_page()
    {
        return 2;
    }
    virtual int get_next_page()
    {
        return 0;
    }
   virtual TButton *get_switch_button()
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

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
    ScreenManager &sm = ScreenManager::getInstance();
    SDL_Surface *background, *linuxback, *snoopy;

    background = sm.load_background("layout.bmp");
    linuxback  = sm.load_background("linux.bmp");
    snoopy     = sm.load_background("snoopy.bmp");

    Page0 page0(background);
    Page1 page1(linuxback);
    Page2 page2(snoopy);

    PageManager &pm = PageManager::getInstance();
    pm.insert(&page0);
    pm.insert(&page1);
    pm.insert(&page2);
    pm.setActivePage(0);

#ifdef BUILD_FOR_ANDROID
    SDL_ShowCursor(SDL_DISABLE);
#endif

//    SDL_UpdateRect(screen,0,0,0,0);

    pm.getActive()->RedrawAll();

    (TimerManager::getInstance()).start();

    sm.run();
}
