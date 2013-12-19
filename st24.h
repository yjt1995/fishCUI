#ifndef st24_H
#define st24_H

#include "fish.h"
#include "cstdlib"


class st24:public fish{
    public:
    void init();

    void play();

    void revive(int&,int&);

    int chamilton(int x1,int y1,int x2,int y2); //算出(x1,y1)与(x2,y2)之间的哈密顿距离 
	int cnumOfFood(int x,int y); //算出(x,y)周围速度范围内的水草个数 
int cnumOfWeak(int x,int y); //算出(x,y)周围速度范围之内的软柿子个数 
int cnumOfVeryWeak(int x,int y); //算出(x,y)周围速度范围之内的very软柿子个数
int cnumOfDoubleWeak(int x,int y); //算出(x,y)周围速度范围之内的less软柿子个数 
int cnumOfTripleWeak(int x,int y);
bool ccheckWeak(int id); //判断玩家id现在是否为软柿子
bool ccheckDoubleWeak(int id); //判断玩家id现在是否为软柿子
bool ccheckTripleleWeak(int id);
void cwhereIsWeakest(int x,int y);//找出点(x,y)周围速度范围之内最软的柿子，移动并攻击 
								//如果(x,y)周围速度范围内软柿子个数不为0时在调用本函数 
bool ccheckVeryWeak(int id); //判断玩家id现在是否为非常软柿子 
int cnumOfEnermy(int x,int y); //计算点(x,y)速度范围内周围的玩家个数（用于逃跑） 
int cwhoAttackedMe();// 判断自己周围四个点敌人个数,若有一个则返回其ID；若有至少两个返回-2；若没有了返回0；
bool crunAndEat();//到尽可能远、安全的地方吃水草 
bool crunNotEat();//逃跑到尽可能安全、尽可能吃到水草的地方 
bool cjustRun();//逃跑到尽可能远而且安全的地方
bool crunJustSafe();//跑到尽可能安全的地方 
bool ceatFood();//吃水草而且到尽可能吃到更多水草的地方吃 
void cfightBack(int id);//反击攻击自己的人，先移动到玩家少而且水草多的位置 
int cnumOfLittleWeak(int x,int y);//以护甲round/30作为防御，攻击大于HP的 
bool ccheckLittleWeak(int id); //判断玩家id现在是否为little软柿子
void cgetCloseToFood();//吃不到食物时移动到离食物近的地方 
bool ccheckTripleWeak(int id);	
	
	
	st24();

    ~st24();

};


#endif
