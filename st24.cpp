#include "st24.h"

#include <cstdio>
#include <iostream>

using namespace std;

static int round = 0,health = 4 * 3; //�ֱ�������¼�غ����Լ���һ�ξ��ߺ��Ѫ��
static int location[42][42];//������¼�Լ��ж�ʱ�ľֿ���ÿ����������������ǰ�ȶ������
static int preAttacker;//���ڼ�¼��һ����˭�����Լ����������û���˴��Լ������Ϊ0
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
	//��ʼ����1�㹥����4��Ѫ��5���ٶ�
}


void st24::play()
{
int nowHealth;
int id; // �����Լ����˵�id
double hisAttack;//�����Լ����˿������Լ�����Ѫ���İٷֱ�
double myAttack;//��round/25��Ϊ�令�׻����Լ��Ĺ�������ʹ����ʧ������ֵ�����ٷֱ�
double healthRate = (double)getHP()/getMaxHP();//��ʾ�Լ��ĵ�ǰѪ������
int hisArmor = round / 25;
int flag = 0;
int speed = getSp();
int x = getX(),y = getY();
int i,j;
//��ʼ��
	for (i = 1;i <= 40;i++)
		for (j = 1;j <= 40;j++)
			location[i][j] = askWhat(i,j);

//������
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

//������
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



//δ������
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

void st24::revive(int&x,int&y)//ˮ�ݸ��� - ���˸��� - ��ɱ���Լ��˵ľ��� - 2*���ɱ���ľ���
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





int st24::chamilton(int x1,int y1,int x2,int y2)//���(x1,y1)��(x2,y2)֮��Ĺ��ܶپ���
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

int st24::cnumOfFood(int x,int y) //���(x,y)��Χ�ٶȷ�Χ�ڵ�ˮ�ݸ���
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

bool st24::ccheckWeak(int id) //�ж����id�����Ƿ�Ϊ������
{
int attack = getAtt();
int HP = askHP(id);
	if (attack > HP)
		return true;
	else return false;
}


bool st24::ccheckLittleWeak(int id) //�ж����id�����Ƿ�Ϊlittle������
{
int hisArmor = round/30;
int attack = getAtt() * (10/(10 + hisArmor));
int HP = askHP(id);
	if (attack > HP)
		return true;
	else return false;
}


bool st24::ccheckDoubleWeak(int id) //�ж����id�����Ƿ�Ϊ������
{
int hisArmor = round/30;
int attack = getAtt() ;
int HP = askHP(id);
	if (2 * attack > HP)
		return true;
	else return false;
}

bool st24::ccheckTripleWeak(int id) //�ж����id�����Ƿ�Ϊ������
{
int hisArmor = round/30;
int attack = getAtt() ;
int HP = askHP(id);
	if (3 * attack > HP)
		return true;
	else return false;
}

int st24::cnumOfWeak(int x,int y) //���(x,y)��Χ�ٶȷ�Χ֮�ڵ������Ӹ���
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfDoubleWeak(int x,int y) //���(x,y)��Χ�ٶȷ�Χ֮�ڵ�less�����Ӹ���
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckDoubleWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfTripleWeak(int x,int y) //���(x,y)��Χ�ٶȷ�Χ֮�ڵ�less�����Ӹ���
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckTripleWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfLittleWeak(int x,int y) //���(x,y)��Χ�ٶȷ�Χ֮�ڵ�little�����Ӹ���
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckLittleWeak(location[i][j]))
				sum++;
	return sum;
}

int st24::cnumOfVeryWeak(int x,int y) //���(x,y)��Χ�ٶȷ�Χ֮�ڵ�very�����Ӹ���
{
int speed = getSp();
int sum = 0;
	for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID() && st24::ccheckVeryWeak(location[i][j]))
				sum++;
	return sum;
}

void st24::cwhereIsWeakest(int x,int y)//�ҳ���(x,y)��Χ�ٶȷ�Χ֮����������ӣ��ƶ�������
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

bool st24::ccheckVeryWeak(int id) //�ж����id�����Ƿ�Ϊ�ǳ�������
{
int attack = getAtt();
int HP = askHP(id);
	if (attack * 2 >5 *  HP)
		return true;
	else return false;
}

int st24::cnumOfEnermy(int x,int y) // �����(x,y)�ٶȷ�Χ����Χ����Ҹ������������ܣ�
{
int speed = getSp();
int sum = 0;
	 for (int i = 1;i <= 40;i++)
		for (int j = 1;j <= 40;j++)
			if (st24::chamilton(i,j,x,y) <= speed && location[i][j] != FOOD && location[i][j] != EMPTY && location[i][j] != getID())
				sum++;
	return sum;
}


int st24::cwhoAttackedMe()// �ж��Լ���Χ�ĸ�����˸���,����һ���򷵻���ID������������������-2����û���˷���0��
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

bool st24::crunAndEat()//��������Զ����ȫ�ĵط���ˮ�� (��ȫָ��(���˸���) + ����ָ��(5*����))
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


bool st24::cjustRun()//���ܵ�������Զ�Ұ�ȫ�ĵط�(��ȫָ��(���˸���) + ����ָ��(5*����))
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

bool st24::crunJustSafe()//�ܵ������ܰ�ȫ�ĵط�
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

void st24::cfightBack(int id)//���������Լ����ˣ����ƶ�����ȫ(������)����ˮ�ݶ�(5*ˮ����)��λ��
{
int x = getX(),y = getY();
int speed = getSp();
int value = 0;
int safety = 0;
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
int i,j;
int X,Y;//id��λ��

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

bool st24::ceatFood()//��ˮ�ݶ��ҵ������ܳԵ�����ˮ�ݵĵط��� (��˰�ȫ��)
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
