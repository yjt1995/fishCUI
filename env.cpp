#include "env.h"
#include "fish.h"
using namespace std;

env::env()
{
	totalplayer=0;
	for (int i=0;i<=N;++i)
		for (int j=0;j<=M;++j)
			tankmap[i][j]=EMPTY;
	for (int i=0;i<=MAX_PLAYER;i++)
		sequence[i]=0;
}

env::~env()
{
	for (int i=1;i<=totalplayer;++i)
		{delete player[i];}
}

bool env::addAI(fish* newplayer)
{
	totalplayer++;
	if (totalplayer>MAX_PLAYER)
	{
		totalplayer--;
		return false;
	}
	else
	{
		player[totalplayer]=newplayer;
		player[totalplayer]->id=totalplayer;
		name[totalplayer]=player[totalplayer]->Identifier;
		return true;
	}
}

void env::welcomeprint()
{
    char nousech[100];
    printf("欢迎来到这个神奇的鱼缸世界！！！");
    gets(nousech);
    printf("为什么我要说神奇呢？");
    gets(nousech);
    printf("竟然这里的鱼有血量，有攻击，有速度，还有护甲！！");
    gets(nousech);
    printf("竟然这里的水草能刷新！！");
    gets(nousech);
    printf("竟然这里的鱼还能互相残杀！！");
    gets(nousech);
    printf("我们不禁提出了一个深刻的哲学问题。");
    gets(nousech);
    printf("这些鱼互相攻击的动机是什么呢？");
    gets(nousech);
    printf("好吧。。。你慢慢想。。。他们已经开始了。。。。");
    gets(nousech);
    printf("1-->极简模式\n");
    printf("2-->单人监控模式\n");
    printf("3-->掌控全局模式\n");
    printf("4-->回顾历史\n");
    cin>>modelkind;
}

void env::readrecord(int& x,int& y)
{
    printf("读档位置：\n");
    char ftref[100];
    cin>>ftref;
    strcat(ftref,".ftr");
    ifstream ftf(ftref);
    printf("等待中。。。\n");
    ftf>>x>>y;
    for (int i=1;i<=y;++i)
        ftf>>name2[i];
    int z;
    for (int i=1;i<=x;++i)
        for (int j=1;j<=y;++j)
        {
            for (int k=1;k<=13;++k)
                ftf>>ftre[i][j][k];
            ftf>>z;
            ftresta[i][j]=z;
        }
    ftf.close();
}

void env::printround(int y,int z)
{
    printf("Round %d\n",z);
    cout<<setw(2)<<"ID"<<setw(10)<<"Author"<<setw(2+7)<<"Score"<<setw(8)<<"Status"<<setw(9)<<"Pos"<<setw(4)<<"Lv"<<setw(5)<<"Exp"<<setw(5)<<"HP"<<setw(6)<<"MaxHP"<<setw(4)<<"Sp"<<setw(4)<<"Att"<<setw(4)<<"Ar"<<setw(5)<<"Kill"<<setw(4)<<"Die"<<endl;
	for (int i=1;i<=y;++i)
		cout<<setw(2)<<ftre[z][i][1]<<setw(12)<<name2[ftre[z][i][1]]<<setw(7)<<ftre[z][i][2]<<setw(8)<<((ftresta[z][i])?"ALIVE":"DEAD")<<setw(3)<<'('<<setw(2)<<ftre[z][i][3]<<','<<setw(2)<<ftre[z][i][4]<<')'<<setw(4)<<ftre[z][i][5]<<setw(5)<<ftre[z][i][6]<<setw(5)<<ftre[z][i][7]<<setw(6)<<ftre[z][i][8]<<setw(4)<<ftre[z][i][9]<<setw(4)<<ftre[z][i][10]<<setw(4)<<ftre[z][i][11]<<setw(5)<<ftre[z][i][12]<<setw(4)<<ftre[z][i][13]<<endl;
}

void env::play()
{
	srand(time(NULL));
	welcomeprint();
	if (modelkind==4)
    {
        int roundsum,playersum;
        readrecord(roundsum,playersum);
        printf("又回到了辉煌的过去，那群鱼争霸的时代。。。\n");
        char nousech[100];
        gets(nousech);
        printf("大师要看那个回合呢？(1-%d)\n",roundsum);
        int roundnow;
        cin>>roundnow;
        printround(playersum,roundnow);
        printf("大师还要看吗？(1-%d/0表示退出)\n",roundsum);
        cin>>roundnow;
        while (roundnow!=0)
        {
            printround(playersum,roundnow);
            printf("大师还要看吗？(1-%d/0表示退出)\n",roundsum);
            cin>>roundnow;
        }
        return ;
    }
    if (modelkind==2)
    {
        printf("大师你要监控谁呢？(1-%d)\n",totalplayer);
        cin>>checkplayer;
    }
    printf("actions!!\n");
	for (int i=1;i<=totalplayer;++i)
		arrangePosition(i);
    int roundnum,roundsum=0;
    printf("大师要战多少回合呢？(1-500)\n");
    cin>>roundnum;
    roundsum=roundnum;
	for (int i=1;i<=totalplayer;++i)
		player[i]->init();
	createFood();
	for (int i=1;i<=roundnum;++i)
		round(i);
	printResult();
	printf("大师还要再战吗？(1-500/0表示结束)\n");
	cin>>roundnum;
	roundsum+=roundnum;
	while (roundnum!=0)
    {
        for (int i=roundsum-roundnum+1;i<=roundsum;++i)
            round(i);
        printResult();
        printf("大师还要再战吗？(1-500/0表示结束)\n");
        cin>>roundnum;
        roundsum+=roundnum;
    }
    printf("要保存自己光辉的历史吗？(y/n)\n");
    char c;
    cin>>c;
    if (c=='y')
        ftrecorder(roundsum);
}

void env::ftrecorder(int x)
{
    printf("存档位置？\n");
    char ftref[100];
    cin>>ftref;
    strcat(ftref,".ftr");
    ofstream ftf(ftref);
    printf("等待中。。。\n");
    ftf<<x<<' '<<totalplayer<<endl;
    for (int i=1;i<=totalplayer;++i)
        ftf<<name[i]<<endl;
    for (int i=1;i<=x;++i)
        for (int j=1;j<=totalplayer;++j)
        {
            for (int k=1;k<=13;++k)
                ftf<<ftre[i][j][k]<<' ';
            ftf<<((ftresta[i][j])?1:0)<<endl;
        }
    ftf.close();
    printf("光辉的历史已经写下，勇敢的鱼儿会去开辟新的篇章！！\n");
}

void env::arrangePosition(int newplayer)
{
	int ax=rand()%N+1,ay=rand()%M+1;
	while (tankmap[ax][ay]!=EMPTY)
	{
		ax=rand()%N+1;
		ay=rand()%M+1;
	}
	tankmap[ax][ay]=newplayer;
	player[newplayer]->x=ax;
	player[newplayer]->y=ay;
}

void env::createFood()
{
	for (int i=1;i<=N;++i)
		for (int j=1;j<=M;++j)
			if (tankmap[i][j]==FOOD)
				tankmap[i][j]=EMPTY;
	for (int i=1;i<=MAX_FOOD;++i)
	{
		int ax=rand()%N+1,ay=rand()%M+1;
		while (tankmap[ax][ay]!=EMPTY)
		{
			ax=rand()%N+1;
			ay=rand()%M+1;
		}
		tankmap[ax][ay]=FOOD;
	}
}

void env::round(int x)
{
	printf("Round %d\n",x);
	if (x%FOOD_ROUND==0) createFood();
	for (int i=1;i<=totalplayer;++i)
		if (player[i]->survive)
		{
			player[i]->exp++;
			upgrade(i);
		}
	actionSort();
	for (int i=1;i<=totalplayer;++i)
		if (player[sequence[i]]->survive)
            {
                if ((modelkind==3)||(modelkind==2 && sequence[i]==checkplayer)) printf("fish %d(%s) is now in action.\n",sequence[i],player[sequence[i]]->Identifier);
                player[sequence[i]]->play();
                if ((modelkind==3)||(modelkind==2 && sequence[i]==checkplayer)) {printf("Action finished.\n");Sleep(1000);}
            }
			else
			{
				if (player[sequence[i]]->cd>0)
					player[sequence[i]]->cd--;
					else
					{
						player[sequence[i]]->survive=true;
						player[sequence[i]]->hp=max(2,player[sequence[i]]->maxhp/4);
						int rx=0,ry=0;
						player[sequence[i]]->revive(rx,ry);
						if ((rx<1)||(ry<1)||(rx>N)||(ry>M))
						{
							rx=rx%N+1;
							ry=ry%M+1;
						}
						while (tankmap[rx][ry]!=EMPTY)
						{
							rx=rand()%N+1;
							ry=rand()%M+1;
						}
						tankmap[rx][ry]=sequence[i];
						player[sequence[i]]->x=rx;
						player[sequence[i]]->y=ry;
						if ((modelkind==3)||(modelkind==2 && sequence[i]==checkplayer)) printf("fish %d(%s) revive.\n",sequence[i],player[sequence[i]]->Identifier);
						if ((modelkind==3)||(modelkind==2 && sequence[i]==checkplayer)) printf("fish %d(%s) is now in action.\n",sequence[i],player[sequence[i]]->Identifier);
                        player[sequence[i]]->play();
                        if ((modelkind==3)||(modelkind==2 && sequence[i]==checkplayer)) {printf("Action finished.\n");Sleep(1000);}
					}
			}
    scoreSort();
    for (int i=1;i<=totalplayer;++i)
    {
        ftre[x][i][1]=sequence[i];
        ftre[x][i][2]=getscore(sequence[i]);
        ftresta[x][i]=player[sequence[i]]->survive;
        ftre[x][i][3]=player[sequence[i]]->x;
        ftre[x][i][4]=player[sequence[i]]->y;
        ftre[x][i][5]=player[sequence[i]]->level;
        ftre[x][i][6]=player[sequence[i]]->exp;
        ftre[x][i][7]=player[sequence[i]]->hp;
        ftre[x][i][8]=player[sequence[i]]->maxhp;
        ftre[x][i][9]=player[sequence[i]]->sp;
        ftre[x][i][10]=player[sequence[i]]->att;
        ftre[x][i][11]=player[sequence[i]]->ar;
        ftre[x][i][12]=player[sequence[i]]->kill;
        ftre[x][i][13]=player[sequence[i]]->killed;
    }
}

void env::actionSort()
{
	for (int i=1;i<=totalplayer;++i)
		t[i]=true;
	for (int i=1;i<=totalplayer;++i)
	{
		int fastPlayer=0;
		for (int j=1;j<=totalplayer;++j)
			if ((t[j])&&((fastPlayer==0)||(bigthan(j,fastPlayer))))
				fastPlayer=j;
		sequence[i]=fastPlayer;
		t[fastPlayer]=false;
	}
}

bool env::bigthan(int aplayer,int bplayer)
{
	if ((player[aplayer]->sp>player[bplayer]->sp)||((player[aplayer]->sp==player[bplayer]->sp)&&(player[aplayer]->hp<player[bplayer]->hp))
	||((player[aplayer]->sp==player[bplayer]->sp)&&(player[aplayer]->hp==player[bplayer]->hp)&&(player[aplayer]->level<player[bplayer]->level))
	||((player[aplayer]->sp==player[bplayer]->sp)&&(player[aplayer]->hp==player[bplayer]->hp)&&(player[aplayer]->level==player[bplayer]->level)&&(getscore(aplayer)<getscore(bplayer))))
		return true;
		else return false;
}

int env::getscore(int aplayer)
{
	return player[aplayer]->level*(player[aplayer]->level+1)/2+1+player[aplayer]->exp+player[aplayer]->kill*5-player[aplayer]->killed*player[aplayer]->killed/5;
}

bool env::upgrade(int aplayer)
{
	if (player[aplayer]->exp>player[aplayer]->level)
	{
		player[aplayer]->level++;
		player[aplayer]->exp-=player[aplayer]->level;
		player[aplayer]->point+=3;
		return true;
	}
	else return false;
}

int env::getTotalPlayer()
{
	return totalplayer;
}

int env::getMap(int mx,int my)
{
	return tankmap[mx][my];
}

int env::getHP(int aplayer)
{
	return player[aplayer]->hp;
}

bool env::move(int aplayer,int mx,int my)
{
	if (mx<1 || mx>N || my<1 || my>M) return false;
	if ((tankmap[mx][my]!=EMPTY)||(abs(player[aplayer]->x-mx)+abs(player[aplayer]->y-my)>player[aplayer]->sp))
		return false;
		else
		{
			tankmap[player[aplayer]->x][player[aplayer]->y]=EMPTY;
			if ((modelkind==3)||(modelkind==2 && aplayer==checkplayer)) printf("fish %d move from (%d,%d) to (%d,%d).\n",aplayer,player[aplayer]->x,player[aplayer]->y,mx,my);
			player[aplayer]->x=mx;
			player[aplayer]->y=my;
			tankmap[mx][my]=aplayer;
			return true;
		}
}

bool env::attack(int aplayer,int ax,int ay)
{
	if (ax<1 || ax>N || ay<1 || ay>M) return false;
	if ((tankmap[ax][ay]==EMPTY)||(abs(player[aplayer]->x-ax)+abs(player[aplayer]->y-ay)>1))
		return false;
		else
		{
			if (tankmap[ax][ay]==FOOD)
			{
				if (player[aplayer]->att>0)
				{
					player[aplayer]->exp++;
					tankmap[ax][ay]=EMPTY;
					upgrade(aplayer);
					if ((modelkind==3)||(modelkind==2 && aplayer==checkplayer)) printf("fish %d attack FOOD at (%d,%d).\n",aplayer,ax,ay);
					player[aplayer]->hp+=min(max(2,player[aplayer]->maxhp/4),player[aplayer]->maxhp-player[aplayer]->hp);
				}
			}
			else
			{
				int bplayer=tankmap[ax][ay];
				if ((modelkind==3)||(modelkind==2 && aplayer==checkplayer)) printf("fish %d attack fish %d at (%d,%d).\n",aplayer,bplayer,ax,ay);
				double armor=player[bplayer]->ar;
				int bleed=max(1,(int)(player[aplayer]->att*(1-armor/(10+armor))));
				player[bplayer]->hp-=min(bleed,player[bplayer]->hp);
				if (player[bplayer]->hp==0)
				{
					player[bplayer]->survive=false;
					if ((modelkind==3)||(modelkind==2 && aplayer==checkplayer)) printf("fish %d is killed.\n",bplayer);
					tankmap[player[bplayer]->x][player[bplayer]->y]=EMPTY;
					player[bplayer]->x=0;
					player[bplayer]->y=0;
					player[bplayer]->cd=2;
					player[bplayer]->killed++;
					player[aplayer]->kill++;
					player[aplayer]->exp+=max(1,player[bplayer]->level/2);
					if (player[aplayer]->level<player[bplayer]->level) player[aplayer]->exp+=3*(player[bplayer]->level-player[aplayer]->level);
					bool tt=upgrade(aplayer);
					while (tt) tt=upgrade(aplayer);
				}
			}
            return true;
		}
}

void env::printResult()
{
	scoreSort();
	cout<<setw(2)<<"ID"<<setw(10)<<"Author"<<setw(2+7)<<"Score"<<setw(8)<<"Status"<<setw(9)<<"Pos"<<setw(4)<<"Lv"<<setw(5)<<"Exp"<<setw(5)<<"HP"<<setw(6)<<"MaxHP"<<setw(4)<<"Sp"<<setw(4)<<"Att"<<setw(4)<<"Ar"<<setw(5)<<"Kill"<<setw(4)<<"Die"<<endl;
	for (int i=1;i<=totalplayer;++i)
		cout<<setw(2)<<sequence[i]<<setw(12)<<player[sequence[i]]->Identifier<<setw(7)<<getscore(sequence[i])<<setw(8)<<((player[sequence[i]]->survive)?"ALIVE":"DEAD")<<setw(3)<<'('<<setw(2)<<player[sequence[i]]->x<<','<<setw(2)<<player[sequence[i]]->y<<')'<<setw(4)<<player[sequence[i]]->level<<setw(5)<<player[sequence[i]]->exp<<setw(5)<<player[sequence[i]]->hp<<setw(6)<<player[sequence[i]]->maxhp<<setw(4)<<player[sequence[i]]->sp<<setw(4)<<player[sequence[i]]->att<<setw(4)<<player[sequence[i]]->ar<<setw(5)<<player[sequence[i]]->kill<<setw(4)<<player[sequence[i]]->killed<<endl;
}

void env::scoreSort()
{
	for (int i=1;i<=totalplayer;++i)
		t[i]=true;
	for (int i=1;i<=totalplayer;++i)
	{
		int dickPlayer=0;
		for (int j=1;j<=totalplayer;++j)
			if ((t[j])&&((dickPlayer==0)||(getscore(j)>getscore(dickPlayer))))
				dickPlayer=j;
		sequence[i]=dickPlayer;
		t[dickPlayer]=false;
	}
}
