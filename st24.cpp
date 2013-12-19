#include "st24.h"

#include <cstdio>
#include <iostream>

using namespace std;

static int round = 0,health = 4 * 3; //分别用来记录回合数以及上一次决策后的血量
static int location[42][42];//用来记录自己行动时的局况，每次在其他函数调用前先对其更新
static int preAttacker;//用于记录上一次是谁打了自己，如果当局没有人打自己则更新为0
static int killer1 = 0,killer2 = 0;



st24::st24()
{
    setIdentifier("st24");
}

st24::~st24() {}

void st24::init()
{
	increaseStrength();
	while (getPoint() >= 6)
		increaseHealth();
	while (getPoint())
		increaseSpeed();
	//初始分配1点攻击，4点血，5点速度
}


void st24::play()
{
int nowHealth;
int id; // 攻击自己的人的id
double hisAttack;//攻击自己的人可以是自己减少血量的百分比
double myAttack;//以round/25作为其护甲换算自己的攻击可以使其损失的生命值点数百分比
double healthRate = (double)getHP()/getMaxHP();//表示自己的当前血量比重
int hisArmor = round / 25;
int flag = 0;
int speed = getSp();
int x = getX(),y = getY();
int i,j;
//初始化
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			location[i][j] = askWhat(i,j);

//加属性
	if (round > 65 && round <= 80 && getAr() <= 1)
		if (getPoint())
			increaseArmor();
	if (round > 185 && round <= 210 && getAr() <= 3)
		if (getPoint())
			increaseArmor();
	if (round > 210 && round <= 240 && getAr() <= 4)
		if (getPoint())
			increaseArmor();
	if (round > 240 && round <= 270 && getAr() <= 5)
		if (getPoint())
			increaseArmor();
	if (round > 270 && round <= 300 && getAr() <= 6)
		if (getPoint())
			increaseArmor();
	if (round > 300 && round <= 350 && getAr() <= 7)
		if (getPoint())
			increaseArmor();
	if (round > 350 && round <= 380 && getAr() <= 8)
		if (getPoint())
			increaseArmor();
	if (round > 420 && round <= 450 && getAr() <= 9)
		if (getPoint())
			increaseArmor();
	if (speed < 20 && getLevel() % 2 != 0)
		while (getPoint()) { increaseSpeed();increaseSpeed(); increaseStrength();}
	if (speed < 20 && getLevel() % 2 == 0)
		while (getPoint()) { increaseSpeed();increaseHealth(); increaseHealth();}
	if (speed >= 20 && speed < 45 && getLevel() % 3 == 0)
		while (getPoint()) {increaseHealth(); increaseHealth();increaseStrength(); }
	if (speed >= 20 && speed < 45 && getLevel() % 3 != 0)
		while (getPoint()) {increaseHealth(); increaseStrength(); increaseSpeed();}
	if (speed >= 45 && getLevel() % 2 != 0)
		while (getPoint()) { increaseStrength();increaseStrength(); increaseHealth();}
	if (speed >= 45 && getLevel() % 4 == 2)
		while (getPoint()) { increaseStrength();increaseHealth(); increaseHealth();}
	if (speed >= 45 && getLevel() % 4 == 0)
		while (getPoint()) { increaseStrength();increaseSpeed(); increaseHealth();}

//被攻击
	nowHealth = getHP();
	if (nowHealth < health && st24::cwhoAttackedMe() > 0)
		{
			health = nowHealth;
			id = st24::cwhoAttackedMe();
			myAttack = (max(1,getAtt() * (10/(10 + hisArmor)))) / askHP(id);
			hisAttack = (health - nowHealth)/getMaxHP();
			if (healthRate > 0.7) { if (!st24::ceatFood()) st24:: cgetCloseToFood(); flag = 1;}
			if (healthRate <= 0.7 && healthRate >= 0.2) { cfightBack(cwhoAttackedMe()); flag = 1;}
			if (healthRate < 0.2) { crunAndEat(); flag = 1;}
			preAttacker = id;
			if (hisAttack > 0.6 && killer1 == 0 && round >= 100) killer1 = id;
			if (hisAttack > 0.6 && killer1 != 0 && round >= 100) killer2 = id;
			round++;
			health = getHP();
			return;
		}

	if (nowHealth < health && st24::cwhoAttackedMe() < 0)
		{
			health = nowHealth;
			if (st24::cjustRun())
				health = min(nowHealth + getMaxHP() / 4,getMaxHP());
			preAttacker = 0;
			health = getHP();
			round++;
			return;
		}



//未被攻击
	//healthRate = getHP()/getMaxHP();
	//if (nowHealth >= health || st24::cwhoAttackedMe() == 0)
{
			preAttacker = 0;
		if (round <= 100)
		{
			if (healthRate >= 0.85)
				{
					if (st24::cnumOfTripleWeak(x,y) == 0) { if (!st24::ceatFood()) st24:: cgetCloseToFood();}
					if (st24::cnumOfTripleWeak(x,y) > 0)  st24::cwhereIsWeakest(x,y);
				}
			if (healthRate < 0.85 && healthRate >= 0.6)
				{
					if (st24::cnumOfWeak(x,y) == 0) { if (!st24::ceatFood()) st24:: cgetCloseToFood();}
					if (st24::cnumOfWeak(x,y) > 0) st24::cwhereIsWeakest(x,y);
				}
			if (healthRate < 0.6)	st24::crunAndEat();
		}
		if (round > 100 && round <= 350)
		{
			if (healthRate >= 0.85)
				{
					if (st24::cnumOfDoubleWeak(x,y) == 0) { if (!st24::ceatFood()) st24:: cgetCloseToFood();}
					if (st24::cnumOfDoubleWeak(x,y) > 0)  st24::cwhereIsWeakest(x,y);

				}
			if (healthRate < 0.85 && healthRate >= 0.65)
				{
					if (st24::cnumOfLittleWeak(x,y) == 0) { if (!st24::ceatFood()) st24:: cgetCloseToFood();}
					if (st24::cnumOfLittleWeak(x,y) > 0) st24::cwhereIsWeakest(x,y);
				}
			if (healthRate < 0.65) st24::crunAndEat();
		}
		if (round > 350)
		{
			if (healthRate >= 0.85)
				{
					if (st24::cnumOfDoubleWeak(x,y) == 0) { if (!st24::ceatFood()) st24:: cgetCloseToFood();}
					if (cnumOfDoubleWeak(x,y) > 0)  st24::cwhereIsWeakest(x,y);
				}
			if (healthRate < 0.85 && healthRate >= 0.65)
				{
					if (st24::cnumOfLittleWeak(x,y) == 0) { if (!st24::ceatFood()) st24:: cgetCloseToFood();}
					if (st24::cnumOfLittleWeak(x,y) > 0) st24::cwhereIsWeakest(x,y);
				}
			if (healthRate < 0.65) st24::crunAndEat();
		}
health = getHP();
round++;
return;
}
}

void st24::revive(int&x,int&y)//水草个数 - 敌人个数 - 离杀死自己人的距离 - 2*离大杀器的距离
{
int sum = -1000;
int i,j,X = 2,Y = 2;
int killerX1,killerY1,killerX2,killerY2;
int speed = getSp();

	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			{
			if (killer1 != 0 && location[i][j] == killer1)
				{killerX1 = i;killerY1 = j;}
			if (killer2 != 0 && location[i][j] == killer2)
				{killerX2 = i;killerY2 = j;}
			}
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			{
				if (killer1 == 0) {killerX1 = killerX2 = i;killerY1 = killerY2 = j;}
				if (killer2 == 0) {killerX2 = i;killerY2 = j;}
				if (location[i][j] == FOOD && st24::cnumOfFood(i,j) - st24::cnumOfEnermy(i,j) - 2 * st24::chamilton(i,j,killerX1,killerY1) - 2 * st24::chamilton(i,j,killerX2,killerY2) > sum)
					sum = st24::cnumOfFood(i,j) - st24::cnumOfEnermy(i,j) - 2 * st24::chamilton(i,j,killerX1,killerY1) - 2 * st24::chamilton(i,j,killerX2,killerY2);
					X = i; Y = j;
			}
	int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
	for (i = 0;i < 4;i++)
		if (X + dx[i] <= 40 && X + dx[i] > 0 && Y + dy[i] <= 40 && Y + dy[i] > 0)
			{ x = X + dx[i]; y = Y + dy[i];break;}
	round += 3;
}





int st24::chamilton(int x1,int y1,int x2,int y2)//算出(x1,y1)与(x2,y2)之间的哈密顿距离
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

int st24::cnumOfFood(int x,int y) //算出(x,y)周围速度范围内的水草个数
{
int speed = getSp();
int sum = 0;
int i,j;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (location[i][j] == FOOD && st24::chamilton(i,j,x,y) <= speed)
				sum++;
	return sum;
}

bool st24::ccheckWeak(int id) //判断玩家id现在是否为软柿子
{
int attack = getAtt();
int HP = askHP(id);
	if (attack > HP)
		return true;
	else return false;
}


bool st24::ccheckLittleWeak(int id) //判断玩家id现在是否为little软柿子
{
int hisArmor = round/30;
int attack = getAtt() * (10/(10 + hisArmor));
int HP = askHP(id);
	if (attack > HP)
		return true;
	else return false;
}


bool st24::ccheckDoubleWeak(int id) //判断玩家id现在是否为软柿子
{
int hisArmor = round/30;
int attack = getAtt() ;
int HP = askHP(id);
	if (2 * attack > HP)
		return true;
	else return false;
}

bool st24::ccheckTripleWeak(int id) //判断玩家id现在是否为软柿子
{
int hisArmor = round/30;
int attack = getAtt() ;
int HP = askHP(id);
	if (3 * attack > HP)
		return true;
	else return false;
}

int st24::cnumOfWeak(int x,int y) //算出(x,y)周围速度范围之内的软柿子个数
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfDoubleWeak(int x,int y) //算出(x,y)周围速度范围之内的less软柿子个数
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckDoubleWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfTripleWeak(int x,int y) //算出(x,y)周围速度范围之内的less软柿子个数
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckTripleWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfLittleWeak(int x,int y) //算出(x,y)周围速度范围之内的little软柿子个数
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckLittleWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfVeryWeak(int x,int y) //算出(x,y)周围速度范围之内的very软柿子个数
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckVeryWeak(location[i][j]))
				sum++;
	return sum;
}

void st24::cwhereIsWeakest(int x,int y)//找出点(x,y)周围速度范围之内最软的柿子，移动并攻击
{
int speed = getSp();
int HP = 4 * getAtt();
int X,Y;
int id;
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) < speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckTripleWeak(location[i][j]) && askHP(location[i][j]) < HP)
				{
					HP = askHP(location[i][j]);
					X = i; Y = j;
					id = location[i][j];
				}
	for (int i = 0;i < 4;i++)
				if (X + dx[i] <= 40 && X + dx[i] > 0 && Y + dy[i] <= 40 && Y + dy[i] > 0 && location[X + dx[i]][Y + dy[i]] == EMPTY)
					{
						move(X + dx[i],Y + dy[i]);
						attack(X,Y);
						return;
					}
	return;
}

bool st24::ccheckVeryWeak(int id) //判断玩家id现在是否为非常软柿子
{
int attack = getAtt();
int HP = askHP(id);
	if (attack * 2 >5 *  HP)
		return true;
	else return false;
}

int st24::cnumOfEnermy(int x,int y) // 计算点(x,y)速度范围内周围的玩家个数（用于逃跑）
{
int speed = getSp();
int sum = 0;
	 for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID())
				sum++;
	return sum;
}


int st24::cwhoAttackedMe()// 判断自己周围四个点敌人个数,若有一个则返回其ID；若有至少两个返回-2；若没有了返回0；
{
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
int sum = 0;
int x = getX(),y = getY();
int id = 0;
	for (int i = 0;i < 4;i++)
		if (x + dx[i] <= 40 && location[x + dx[i]][y + dy[i]] > 0 && x + dx[i] > 0 && y + dy[i] <= 40 && y + dy[i] > 0)
			{
				sum++;
				id = location[x + dx[i]][y + dy[i]];
			}
	if (sum >= 2) return -2;
	if (sum == 1) return id;
	if (sum == 0) return 0;
}

bool st24::crunAndEat()//到尽可能远、安全的地方吃水草 (安全指数(敌人个数) + 距离指数(5*距离))
{
int x = getX(),y = getY(),X,Y;
int speed = getSp();
int value = -100;
int distance = 0,safety = 0,danger = 0;
bool eat = 1;
int i,j,killerX,killerY,killerx,killery;
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
	if (killer1 != 0)
		for (i = 1;i <= 40;i++)
			for (j = 1;j <= 40;j++)
				if (location[i][j] == killer1)
					{killerX = i;killerY = j;}
	if (killer2 != 0)
		for (i = 1;i <= 40;i++)
			for (j = 1;j <= 40;j++)
				if (location[i][j] == killer2)
					{killerx = i;killery = j;}
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			if (location[i][j] == EMPTY && (location[i + 1][j] == FOOD || location[i - 1][j] == FOOD || location[i][j + 1] == FOOD || location[i][j - 1] == FOOD) && st24::chamilton(i,j,x,y) <= speed )
				{
					if (killer1 == 0) {killerX = i;killerY = j;}
					if (killer2 == 0) {killerx = i;killery = j;}
					distance = st24::chamilton(i,j,x,y);
					safety = st24::cnumOfEnermy(i,j);
					danger = st24::chamilton(i,j,killerx,killery) + st24::chamilton(i,j,x,y);;
				if (value < 2 * distance - safety - 2 * danger)
					{ X = i; Y = j; value = 2 * distance - safety - 2 * danger;}
				}
	if (value == -100)	{ st24::cjustRun(); eat = 0;}
		 else
		 	{
			 	move(X,Y);
			 	if (location[min(40,X + 1)][Y] == FOOD) attack(min(40,X + 1),Y);
				 	else if (location[max(1,X - 1)][Y] == FOOD) attack(max(1,X - 1),Y);
					 	else if (location[X][min(40,Y + 1)] == FOOD) attack(X,min(40,Y + 1));
					 		else if (location[X][max(1,Y - 1)] == FOOD) attack(X,max(1,Y - 1));
								else eat = 0;
}
	if (!eat) cjustRun();

}


bool st24::cjustRun()//逃跑到尽可能远且安全的地方(安全指数(敌人个数) + 距离指数(5*距离))
{
int x = getX(),y = getY(),X,Y;
int speed = getSp();
int value = 0;
int distance = 0,safety = 0;
bool eat = 1;
int i,j;
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			if (location[i][j] == EMPTY &&  st24::chamilton(i,j,x,y) <= speed )
				{
					distance = st24::chamilton(i,j,x,y);
					safety = st24::cnumOfEnermy(i,j);
					if (value < 5 * distance + safety)
						{ X = i; Y = j; value = 5 * distance + safety;}
				}
	move(X,Y);
		if (location[min(40,X + 1)][Y] == FOOD) attack(min(40,X + 1),Y);
			else if (location[max(1,X - 1)][Y] == FOOD) attack(max(1,X - 1),Y);
			 	else if (location[X][min(40,Y + 1)] == FOOD) attack(X,min(40,Y + 1));
						else if (location[X][max(1,Y - 1)] == FOOD) attack(X,max(1,Y - 1));
							else eat = 0;
	return eat;
}

bool st24::crunJustSafe()//跑到尽可能安全的地方
{
int x = getX(),y = getY(),X,Y;
int speed = getSp();
int safety = 0;
int value = 0;
bool eat = 1;
int i,j;
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			if (location[i][j] == EMPTY &&  st24::chamilton(i,j,x,y) <= speed )
				{
					safety = st24::cnumOfEnermy(i,j);
					if (value < safety)
						{ X = i; Y = j; value = safety;}
				}
	move(X,Y);
	if (location[min(40,X + 1)][Y] == FOOD) attack(min(40,X + 1),Y);
			else if (location[max(1,X - 1)][Y] == FOOD) attack(max(1,X - 1),Y);
			 	else if (location[X][min(40,Y + 1)] == FOOD) attack(X,min(40,Y + 1));
						else if (location[X][max(1,Y - 1)] == FOOD) attack(X,max(1,Y - 1));
							else eat = 0;
	return eat;
}

void st24::cfightBack(int id)//反击攻击自己的人，先移动到安全(敌人数)而且水草多(5*水草数)的位置
{
int x = getX(),y = getY();
int speed = getSp();
int value = 0;
int safety = 0;
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
int i,j;
int X,Y;//id的位置

	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
				if (location[i][j] == id)
					{ X = i; Y = j;}
	for (i = 0;i < 4;i++)
		if (X + dx[i] <= 40 && X + dx[i] > 0 && Y + dy[i] <= 40 && Y + dy[i] > 0)
			{
				move(X + dx[i],Y + dy[i]);
				attack(X,Y);
			}
	return;
}

bool st24::ceatFood()//吃水草而且到尽可能吃到更多水草的地方吃 (兼顾安全性)
{
int speed = getSp();
int x = getX(),y = getY(),X,Y;
int  num = 0;
int i,j,killerX,killerY;
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			if (location[i][j] == FOOD &&  st24::chamilton(i,j,x,y) < speed && num < st24::cnumOfFood(i,j) + cnumOfTripleWeak(i,j))
				{
					num = st24::cnumOfFood(i,j) + cnumOfTripleWeak(i,j);
					X = i; Y = j;
				}
	if (num == 0) return false;
	if (num != 00)
		{
			for (i = 0;i < 4;i++)
				if (X + dx[i] <= 40 && X + dx[i] > 0 && Y + dy[i] <= 40 && Y + dy[i] > 0)
					{
						move(X + dx[i],Y + dy[i]);
						attack(X,Y);
						return true;
					}
		}
}

void st24::cgetCloseToFood()
{
int speed = getSp();
int x = getX(),y = getY();
int X,Y;
int num = 0;
int i,j;
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			{
				if (location[i][j] == EMPTY && cnumOfFood(i,j) >= num && st24::chamilton(i,j,x,y) <= speed)
					{
						X = i; Y = j;
					}
			}
	move(X,Y);
	return;
}
