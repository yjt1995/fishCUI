#ifndef TAAI_CRAZY_H
#define TAAI_CRAZY_H

#include "fish.h"
#include <cstdlib>

class TAAI_CRAZY : public fish
{
public:

    TAAI_CRAZY();
    ~TAAI_CRAZY();
    void init();
    void play();
    void revive(int&, int&);

private:

    int check(int, int, int&, int&);
    int d[4][2];
    double ar[MAX_PLAYER+1];
};

//可自行增加所需函数所需函数及变量，但需保证上面每个函数的完整与可调用

//不要使用全局变量！！

#endif
