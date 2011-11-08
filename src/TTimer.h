#ifndef TTimerH
#define TTimerH

#include <stdlib.h>
#include "lib/functor.h"
#include "lib/tuple.h"
#include <list>
#include <map>
using namespace std;

const int MAX_TIMER = 256;

enum timer_flags {
    TIMER_STOP = 0,
    TIMER_START
};

typedef std::tuple_element<0, std::tuple<void (void)>>::type TimerCallback;

struct timer_struct {
    timer_struct(enum timer_flags flag, const Functor<TimerCallback> cmd)
        : flag(flag), cmd(cmd) {}
    enum timer_flags flag;
    Functor<TimerCallback> cmd;
};

struct timer_head {
    timer_head(int elapsed)
        : elapsed(elapsed), orig_elapsed(elapsed), tslist() {}
    int elapsed;
    int orig_elapsed;
    list<timer_struct*> tslist;
};

class TimerManager {
public:
    static TimerManager &getInstance() {
        static TimerManager obj;
        return obj;
    }
    int insert(int elapsed, const Functor<TimerCallback> &cmd);
    void set_flag(int id, timer_flags flag);
    void start();
    void run();

private:
    TimerManager();
    TimerManager(const TimerManager &);
    TimerManager &operator=(const TimerManager &);
    ~TimerManager() {}
    void dispatch(int period);

    int gcd;
    int time_index;
    pthread_t tid;
    list<timer_head*> tlist;
    map<int, struct timer_struct*> m;
};

class TTimer {
public:
    TTimer(int elapsed, const Functor<TimerCallback> &cmd);
    ~TTimer();
    void start();
    void stop();

private:
    TimerManager &timer;
    int id;
};

#endif
