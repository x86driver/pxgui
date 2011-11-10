#include <stdio.h>
#include <string.h>
#include <time.h>

#include "dstl.h"

#ifdef USE_USTL
#include <uvector.h>
#include <ulist.h>
using namespace ustl;
#else
#include <list>
#include <vector>
using namespace std;
#endif

struct timer_head {
    timer_head(int elapsed)
        : elapsed(elapsed), orig_elapsed(elapsed*3) {}
    int elapsed;
    int orig_elapsed;
};

bool comp(const timer_head *a, const timer_head *b)
{
    return a->elapsed < b->elapsed;
}

bool mycomp(const int &a, const int &b)
{
    return a < b;
}

template <class T, class Compare>
void mysort(T &l, Compare comp)
{
    if (l.size() == 0 || l.size() == 1)
        return;

    list<T> carry;
    list<T> counter[64];
    int fill = 0;

    while (l.empty()) {
        carry.splice(carry.begin(), l, l.begin());
        int i = 0;
        while (i < fill && !counter[i].empty()) {
            counter[i].merge(carry);
            carry.swap(counter[i++]);
        }
        carry.swap(counter[i]);
        if (i == fill) ++fill;
    }

    for (int i = 1; i < fill; ++i)
        counter[i].merge(counter[i-1]);
    swap(counter[fill-1]);
}

template <int N>
void insertion_sort(int (&arr)[N])
{
    for (int i = 1; i < N; ++i) {
        int j = i - 1;
        int value = arr[i];
        while (j >= 0 && arr[j] > value) {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = value;
    }
}

template <typename T, typename Compare>
void doremi_insertion_sort(T arr, Compare comp)
{
    int N = static_cast<int>(arr.size());
    for (int i = 1; i < N; ++i) {
        int j = i - 1;
//        struct timer_head value = *arr[i];
        auto value = *arr[i];
        while (j >= 0 && comp(&value, arr[j])) {
            *arr[j+1] = *arr[j];
            --j;
        }
        *arr[j+1] = value;
    }
}

int main()
{
    srand(time(NULL));
    vector<timer_head*> tlist;

    for (int i = 0; i < 100; ++i) {
        timer_head *th1 = new timer_head(rand()%1000);
        tlist.push_back(th1);
    }

//    doremi_insertion_sort(tlist, comp);
    doremi::__insertion_sort(tlist.begin(), tlist.end(), comp);

    for (auto i = tlist.begin(); i != tlist.end(); ++i) {
        printf("%d %d\n", (*i)->elapsed, (*i)->orig_elapsed);
    }

    return 0;
}
