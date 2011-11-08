#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <pthread.h>
#include "TTimer.h"

class Pred {
public:
    Pred(int elapsed) : elapsed(elapsed)  {}
    bool operator()(const timer_head *th) {
        return (th->elapsed == elapsed);
    }
private:
    int elapsed;
};

bool comp(const timer_head *a, const timer_head *b)
{
    return a->elapsed < b->elapsed;
}

static void *timer_thread(void *data)
{
    TimerManager &tm = TimerManager::getInstance();
    tm.run();

    return NULL;
}

TimerManager::TimerManager()
    : gcd(1000), time_index(0), tid(0), tlist(), m()
{
}

int TimerManager::insert(int elapsed, const Functor<TimerCallback> &cmd)
{
    if (elapsed != gcd) {
        int m = elapsed;
        int n = gcd;
        while (n != 0) {
            int r = m % n;
            m = n;
            n = r;
        }
        gcd = m;
    }

    timer_struct *ts = new timer_struct(TIMER_START, cmd);

    auto it = find_if(tlist.begin(), tlist.end(), Pred(elapsed));

    if (it != tlist.end()) {
        (*it)->tslist.push_back(ts);
    } else {                    // not found
        timer_head *th = new timer_head(elapsed);
        th->tslist.push_back(ts);
        tlist.push_back(th);
        tlist.sort(comp);
    }

    m[time_index] = ts;

    return time_index++;
}

void TimerManager::set_flag(int id, timer_flags flag)
{
    auto it = m.find(id);
    if (it != m.end())
        it->second->flag = flag;
}

void TimerManager::dispatch(int period)
{
    for (auto t = tlist.begin(); t != tlist.end(); ++t) {
        struct timer_head *th = *t;
        if (period >= th->elapsed) {
            for (auto it = th->tslist.begin(); it!= th->tslist.end(); ++it) {
                if ((*it)->flag == TIMER_START)
                    (*it)->cmd();
            }
            th->elapsed = th->orig_elapsed;
        } else {
            th->elapsed -= period;
        }
    }

    tlist.sort(comp);
}

void TimerManager::run()
{
    for (auto i = tlist.begin(); i != tlist.end(); ++i) {
        printf("%d\n", (*i)->elapsed);
    }

    printf("Timer interval: %d\n", gcd);

//    int total_time = 0;
    while (1) {
//        total_time += gcd;
//        printf("\033[1;31m===== elapsed %05d =====\033[0;38m\n", total_time);
        usleep(gcd * 1000);
        dispatch(gcd);
//        printf("\033[0;31m========== end ===== =====\033[0;38m\n\n\n");
    }
}

void TimerManager::start()
{
    pthread_create(&tid, NULL, timer_thread, NULL);
//    pthread_join(tid, NULL); FIXME 這裡不應該做 join
}

TTimer::TTimer(int elapsed, const Functor<TimerCallback> &cmd)
    : timer(TimerManager::getInstance()),
      id(timer.insert(elapsed, cmd))
{
}

TTimer::~TTimer()
{
}

void TTimer::start()
{
    timer.set_flag(id, TIMER_START);
}

void TTimer::stop()
{
    timer.set_flag(id, TIMER_STOP);
}

#if USE_FOR_DEBUG
class Pageabc {
public:
    Pageabc();
    void onTimerEvent()
    {
        printf("Timer1\n");
    }
    void onTimer2()
    {
        static int count2 = 0;
        printf("Timer2\n");
    }
    void onTimer3()
    {
        static int count3 = 0;
        printf("Timer3\n");
    }
private:
    int count;
};

Pageabc::Pageabc()
    : count(0)
{
    Functor<TimerCallback> cmd3(this, &Pageabc::onTimer3);
    TTimer t3(1000, cmd3);
    t3.start();
}

int main()
{
    Pageabc p;

/*
    Functor<TimerCallback> cmd(&p, &Pageabc::onTimerEvent);
    Functor<TimerCallback> cmd2(&p, &Pageabc::onTimer2);
    TTimer t(500, cmd);
    t.start();

    TTimer t2(1000, cmd2);
    t2.start();
*/
//    Functor<TimerCallback> cmd3(&p, &Pageabc::onTimer3);
//    TTimer t3(1000, cmd3);
//    t3.start();

    auto &t = TimerManager::getInstance();
    t.start();
//    timer_thread(NULL);

    return 0;
}
#endif
