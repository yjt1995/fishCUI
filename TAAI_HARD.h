#ifndef TAAI_HARD_H
#define TAAI_HARD_H

#include "fish.h"
#include <cstdlib>

class TAAI_HARD : public fish
{
public:

    TAAI_HARD();
    ~TAAI_HARD();
    void init();
    void play();
    void revive(int&, int&);

private:

    void calcSafe(int, int);
    int evaluate(int, int, int&);
    int eNow(int&, int&, int&);
    int evp(int, int);
    void increasePoint();
    void scan();
    void checkAtt();
    inline int dis(int x1, int y1, int x2, int y2)
    {
        return (std::abs(x1 - x2) + std::abs(y1 - y2));
    }
    inline int dis(int x, int y)
    {
        return dis(x, y, getX(), getY());
    }
    inline int nextLevelExp()
    {
        return (2 + getLevel() + 1) * getLevel() / 2;
    }
    inline bool isEnemy(int target)
    {
        return ((target != EMPTY) && (target != FOOD) && (target != INVALID_VALUE) && (target != getID()));
    }
    static const int MAX = 10000;
    int d[4][2];
    int safe[N+1][M+1];
    int ff[N+1][M+1];

    int fX[MAX_PLAYER+1];
    int fY[MAX_PLAYER+1];
    int fMaxHP[MAX_PLAYER+1];
    int fSp[MAX_PLAYER+1];
    int found[MAX_PLAYER+1];
    int fDie[2000];
};

//�������������躯�����躯�������������豣֤����ÿ��������������ɵ���

//��Ҫʹ��ȫ�ֱ�������

#endif
