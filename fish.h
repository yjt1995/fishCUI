#ifndef fish_h
#define fish_h

#include <cstring>
#include "constants.h"
#include "env.h"

class fish
{
	friend env;
	private:
		static env& host;
		char* Identifier;
		int point,level,exp,x,y,hp,maxhp,att,sp,ar,id,cd,kill,killed;
		bool survive;
	public:
		void setIdentifier(const char*);//设置AI标识符（作者学号）
    	int getPoint() const;//返回当前玩家剩余点数
	    int getLevel() const;//返回当前玩家等级
    	int getExp() const;//返回当前玩家经验
	    int getX() const;//返回当前玩家横坐标
	    int getY() const;//返回当前玩家纵坐标
	    int getHP() const;//返回当前玩家生命值
	    int getMaxHP() const;//返回当前玩家生命上限
	    int getAtt() const;//返回当前玩家攻击力
	    int getSp() const;//返回当前玩家速度
	    int getAr() const;//返回当前玩家护甲
	    int getID() const;//获取玩家ID
	    int getTotalPlayer() const;//获取玩家总人数
	    int askWhat(int,int) const;//返回地图某个位置内容（玩家ID或FOOD或EMPTY或INVALID_VALUE）
	    int askHP(int) const;//询问某个玩家ID当前血量
	    bool move(int,int);//移动到某个位置（返回操作成功与否，下同）
	    bool attack(int,int);//攻击某个位置
	    bool increaseHealth();//增加Health属性
	    bool increaseStrength();//增加Strength属性
	    bool increaseSpeed();//增加Speed属性
	    bool increaseArmor(); //增加Armor属性
	    //以上函数由系统实现，供AI调用进行决策

	    fish():Identifier(0) {point=10;level=1;exp=0;x=0;y=0;hp=0;maxhp=0;att=0;sp=0;ar=0;id=0;cd=0;kill=0;killed=0;survive=true;}
	    virtual ~fish(){delete Identifier;}//AI析构函数
	    virtual void init() = 0;//初始化函数，每一局重新开始将调用
	    virtual void play() = 0;//行动函数，每回合行动将调用
	    virtual void revive(int&,int&) = 0;//复活时调用，参数传回选择复活位置（若不合法则随机）
	    //以上函数由AI继承后实现
};

#endif 
