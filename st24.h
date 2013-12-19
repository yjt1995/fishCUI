#ifndef st24_H
#define st24_H

#include "fish.h"
#include "cstdlib"


class st24:public fish{
    public:
    void init();

    void play();

    void revive(int&,int&);

    int chamilton(int x1,int y1,int x2,int y2); //���(x1,y1)��(x2,y2)֮��Ĺ��ܶپ��� 
	int cnumOfFood(int x,int y); //���(x,y)��Χ�ٶȷ�Χ�ڵ�ˮ�ݸ��� 
int cnumOfWeak(int x,int y); //���(x,y)��Χ�ٶȷ�Χ֮�ڵ������Ӹ��� 
int cnumOfVeryWeak(int x,int y); //���(x,y)��Χ�ٶȷ�Χ֮�ڵ�very�����Ӹ���
int cnumOfDoubleWeak(int x,int y); //���(x,y)��Χ�ٶȷ�Χ֮�ڵ�less�����Ӹ��� 
int cnumOfTripleWeak(int x,int y);
bool ccheckWeak(int id); //�ж����id�����Ƿ�Ϊ������
bool ccheckDoubleWeak(int id); //�ж����id�����Ƿ�Ϊ������
bool ccheckTripleleWeak(int id);
void cwhereIsWeakest(int x,int y);//�ҳ���(x,y)��Χ�ٶȷ�Χ֮����������ӣ��ƶ������� 
								//���(x,y)��Χ�ٶȷ�Χ�������Ӹ�����Ϊ0ʱ�ڵ��ñ����� 
bool ccheckVeryWeak(int id); //�ж����id�����Ƿ�Ϊ�ǳ������� 
int cnumOfEnermy(int x,int y); //�����(x,y)�ٶȷ�Χ����Χ����Ҹ������������ܣ� 
int cwhoAttackedMe();// �ж��Լ���Χ�ĸ�����˸���,����һ���򷵻���ID������������������-2����û���˷���0��
bool crunAndEat();//��������Զ����ȫ�ĵط���ˮ�� 
bool crunNotEat();//���ܵ������ܰ�ȫ�������ܳԵ�ˮ�ݵĵط� 
bool cjustRun();//���ܵ�������Զ���Ұ�ȫ�ĵط�
bool crunJustSafe();//�ܵ������ܰ�ȫ�ĵط� 
bool ceatFood();//��ˮ�ݶ��ҵ������ܳԵ�����ˮ�ݵĵط��� 
void cfightBack(int id);//���������Լ����ˣ����ƶ�������ٶ���ˮ�ݶ��λ�� 
int cnumOfLittleWeak(int x,int y);//�Ի���round/30��Ϊ��������������HP�� 
bool ccheckLittleWeak(int id); //�ж����id�����Ƿ�Ϊlittle������
void cgetCloseToFood();//�Բ���ʳ��ʱ�ƶ�����ʳ����ĵط� 
bool ccheckTripleWeak(int id);	
	
	
	st24();

    ~st24();

};


#endif
