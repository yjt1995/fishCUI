#ifndef fish_h
#define fish_h

#include <cstring>
#include "constants.h"
#include "syst.h"

class fish
{
	private:
		char* Identifier;
		int point=10,level=1,exp=0,x=0,y=0,hp=0,maxhp=0,att=0,sp=0,ar=0,id=0;
	public:
		void setIdentifier(const char*);//����AI��ʶ��������ѧ�ţ�
	    const char* getIdentifier() const;//��ȡAI��ʶ��
    	int getPoint() const;//���ص�ǰ���ʣ�����
	    int getLevel() const;//���ص�ǰ��ҵȼ�
    	int getExp() const;//���ص�ǰ��Ҿ���
	    int getX() const;//���ص�ǰ��Һ�����
	    int getY() const;//���ص�ǰ���������
	    int getHP() const;//���ص�ǰ�������ֵ
	    int getMaxHP() const;//���ص�ǰ�����������
	    int getAtt() const;//���ص�ǰ��ҹ�����
	    int getSp() const;//���ص�ǰ����ٶ�
	    int getAr() const;//���ص�ǰ��һ���
	    int getID() const;//��ȡ���ID
	    int getTotalPlayer() const;//��ȡ���������
	    int askWhat(int,int) const;//���ص�ͼĳ��λ�����ݣ����ID��FOOD��EMPTY��INVALID_VALUE��
	    int askHP(int) const;//ѯ��ĳ�����ID��ǰѪ��
	    bool move(int,int);//�ƶ���ĳ��λ�ã����ز����ɹ������ͬ��
	    bool attack(int,int);//����ĳ��λ��
	    bool increaseHealth();//����Health����
	    bool increaseStrength();//����Strength����
	    bool increaseSpeed();//����Speed����
	    bool increaseArmor(); //����Armor����
	    //���Ϻ�����ϵͳʵ�֣���AI���ý��о���

	    fish():identifier(0) {}
	    virtual ~fish(){delete _identifier;}//AI��������
	    virtual void init() = 0;//��ʼ��������ÿһ�����¿�ʼ������
	    virtual void play() = 0;//�ж�������ÿ�غ��ж�������
	    virtual void revive(int&,int&) = 0;//����ʱ���ã���������ѡ�񸴻�λ�ã������Ϸ��������
	    //���Ϻ�����AI�̳к�ʵ��
};

#endif 