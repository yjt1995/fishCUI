#include "fish.h"

inline void fish::setIdentifier(const char *p)//设置AI标识符（作者学号）
{
	return p;
}

inline int fish::getPoint() const//返回当前玩家剩余点数
{
	return point;
}

inline int fish::getLevel() const//返回当前玩家等级
{
	return level;
}

inline int fish::getExp() const//返回当前玩家经验
{
	return exp;
}

inline int fish::getX() const//返回当前玩家横坐标
{
	return x;
}

inline int fish::getY() const//返回当前玩家纵坐标
{
	return y;
}

inline int fish::getHP() const//返回当前玩家生命值
{
	return hp;
}
 
inline int fish::getMaxHP() const//返回当前玩家生命上限
{
	return maxhp;
}

inline int fish::getAtt() const//返回当前玩家攻击力
{
	return att;
}

inline int fish::getSp() const//返回当前玩家速度
{
	return sp;
}

inline int fish::getAr() const//返回当前玩家护甲
{
	return ar;
}

inline int fish::getID() const//获取玩家ID
{
	return id;
}

inline int fish::getTotalPlayer() const//获取玩家总人数
{
	return host.getTotalPlayer();
}

int fish::askWhat(int cx,int cy) const//返回地图某个位置内容（玩家ID或FOOD或EMPTY或INVALID_VALUE）
{
	return host.getMap(cx,cy);
}

int fish::askHP(int playerID) const//询问某个玩家ID当前血量
{
	return host.getHP(playerID);
}
bool fish::move(int mx,int my)//移动到某个位置（返回操作成功与否，下同）
{
	return host.move(id,mx,my);
}

bool fish::attack(int ax,int ay)//攻击某个位置
{
	return host.attack(id,ax,ay);
}

bool fish::increaseHealth()//增加Health属性
{
	if (point==0)
		return false;
		else
		{
			hp+=3;
			maxhp+=3;
			point--;
			return true;
		}
}

bool fish::increaseStrength()//增加Strength属性
{
	if (point==0)
		return false;
		else
		{
			att+=2;
			point--;
			return true;
		}
}

bool fish::increaseSpeed()//增加Speed属性
{
	if (point==0)
		return false;
		else
		{
			sp++;
			point--;
			return true;
		}
}

bool fish::increaseArmor() //增加Armor属性
{
	if (point==0)
		return false;
		else
		{
			ar++;
			point--;
			return true;
		}
}
