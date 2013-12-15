#include "fish.h"

inline void fish::setIdentifier(const char *p)//����AI��ʶ��������ѧ�ţ�
{
	return p;
}

inline int fish::getPoint() const//���ص�ǰ���ʣ�����
{
	return point;
}

inline int fish::getLevel() const//���ص�ǰ��ҵȼ�
{
	return level;
}

inline int fish::getExp() const//���ص�ǰ��Ҿ���
{
	return exp;
}

inline int fish::getX() const//���ص�ǰ��Һ�����
{
	return x;
}

inline int fish::getY() const//���ص�ǰ���������
{
	return y;
}

inline int fish::getHP() const//���ص�ǰ�������ֵ
{
	return hp;
}
 
inline int fish::getMaxHP() const//���ص�ǰ�����������
{
	return maxhp;
}

inline int fish::getAtt() const//���ص�ǰ��ҹ�����
{
	return att;
}

inline int fish::getSp() const//���ص�ǰ����ٶ�
{
	return sp;
}

inline int fish::getAr() const//���ص�ǰ��һ���
{
	return ar;
}

inline int fish::getID() const//��ȡ���ID
{
	return id;
}

inline int fish::getTotalPlayer() const//��ȡ���������
{
	return host.getTotalPlayer();
}

int fish::askWhat(int cx,int cy) const//���ص�ͼĳ��λ�����ݣ����ID��FOOD��EMPTY��INVALID_VALUE��
{
	return host.getMap(cx,cy);
}

int fish::askHP(int playerID) const//ѯ��ĳ�����ID��ǰѪ��
{
	return host.getHP(playerID);
}
bool fish::move(int mx,int my)//�ƶ���ĳ��λ�ã����ز����ɹ������ͬ��
{
	return host.move(id,mx,my);
}

bool fish::attack(int ax,int ay)//����ĳ��λ��
{
	return host.attack(id,ax,ay);
}

bool fish::increaseHealth()//����Health����
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

bool fish::increaseStrength()//����Strength����
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

bool fish::increaseSpeed()//����Speed����
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

bool fish::increaseArmor() //����Armor����
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
