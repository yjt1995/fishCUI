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

//�������������躯�����躯�������������豣֤����ÿ��������������ɵ���

//��Ҫʹ��ȫ�ֱ�������

#endif
