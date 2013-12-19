#include "st26.h"
#include <cstdio>
#include <cmath>
using namespace std;
st26::st26()
{
	setIdentifier("yjt");
}
st26::~st26() {}
void st26::init()
{
	gameRound=0;
	increaseStrength();
	for (int i=1;i<=3;++i)
		increaseHealth();
    for (int i=1;i<=6;++i)
		increaseSpeed();
}
void st26::increase()
{
	if (getPoint()&& getLevel()>getSp() && getSp()<20) increaseSpeed();
	increaseHealth();
	increaseStrength();
	if (getPoint()) increaseHealth();
}
void st26::check()
{
	for (int i=1;i<=N;++i)
		for (int j=1;j<=M;++j)
			a[i][j]=askWhat(i,j);
}
bool st26::kexing(int i,int j)
{
	if (a[i][j]!=EMPTY) return false;
	if ((i>1)&&((a[i-1][j]==FOOD)||(a[i-1][j]>0 && getAtt()>15 && askHP(a[i-1][j])<getHP()))) return true;
	if ((j>1)&&((a[i][j-1]==FOOD)||(a[i][j-1]>0 && getAtt()>15 && askHP(a[i][j-1])<getHP()))) return true;
	if ((i<N)&&((a[i+1][j]==FOOD)||(a[i+1][j]>0 && getAtt()>15 && askHP(a[i+1][j])<getHP()))) return true;
	if ((j<M)&&((a[i][j+1]==FOOD)||(a[i][j+1]>0 && getAtt()>15 && askHP(a[i][j+1])<getHP()))) return true;
	return false;
}
void st26::beginAttack(int i,int j)
{
	if ((i>1)&&((a[i-1][j]==FOOD)||(a[i-1][j]>0 && getAtt()>15 && askHP(a[i-1][j])<getHP()))) {attack(i-1,j);return ;}
	if ((j>1)&&((a[i][j-1]==FOOD)||(a[i][j-1]>0 && getAtt()>15 && askHP(a[i][j-1])<getHP()))) {attack(i,j-1);return ;}
	if ((i<N)&&((a[i+1][j]==FOOD)||(a[i+1][j]>0 && getAtt()>15 && askHP(a[i+1][j])<getHP()))) {attack(i+1,j);return ;}
	if ((j<M)&&((a[i][j+1]==FOOD)||(a[i][j+1]>0 && getAtt()>15 && askHP(a[i][j+1])<getHP()))) {attack(i,j+1);return ;}
}
void st26::eatAndAttack()
{
	cout<<1<<endl;int x=getX(),y=getY();
	cout<<1<<endl;
	for (int i=1;i<=N;++i)
		for (int j=1;j<=M;++j)
			if ((abs(x-i)+abs(y-j)<=getSp())&&(kexing(i,j)))
			{
				if (move(i,j)) beginAttack(i,j);
				return ;
			}
}
void st26::play()
{
	gameRound++;
	increase();
	check();
	eatAndAttack();
	increase();
}
void st26::revive(int& x,int& y) {}
