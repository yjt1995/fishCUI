#include "env.h"
#include "fish.h"

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
		{std::cout<<"1"<<std::endl;delete player[i];std::cout<<"2"<<std::endl;}
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
		return true;
	}
}

void env::play()
{
	srand(time(NULL));
	for (int i=1;i<=totalplayer;++i)
		arrangePosition(i);
	for (int i=1;i<=totalplayer;++i)
		player[i]->init();
	createFood();
	for (int i=1;i<=MAX_ROUND;++i)
		round(i);
	printResult();
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
			{std::cout<<i<<"play"<<std::endl;player[sequence[i]]->play();std::cout<<i<<"playend"<<std::endl;}
			else
			{
				if (player[sequence[i]]->cd>0)
					player[sequence[i]]->cd--;
					else
					{//std::cout<<"d1"<<std::endl;
						player[sequence[i]]->survive=true;
						player[sequence[i]]->hp=std::max(2,player[sequence[i]]->maxhp/4);
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
						//std::cout<<"d1"<<std::endl;
						player[sequence[i]]->play();
					}
			}
	std::cout<<"round "<<x<<std::endl;
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
{std::cout<<"m"<<aplayer<<std::endl;
	if (mx<1 || mx>N || my<1 || my>M) {std::cout<<"mend"<<aplayer<<std::endl;return false;}
	if ((tankmap[mx][my]!=EMPTY)||(abs(player[aplayer]->x-mx)+abs(player[aplayer]->y-my)>player[aplayer]->sp))
		{std::cout<<"mend"<<aplayer<<std::endl;return false;}
		else
		{
			tankmap[player[aplayer]->x][player[aplayer]->y]=EMPTY;
			player[aplayer]->x=mx;
			player[aplayer]->y=my;
			tankmap[mx][my]=aplayer;
			std::cout<<"mend"<<aplayer<<std::endl;
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
					player[aplayer]->hp+=std::min(std::max(2,player[aplayer]->maxhp/4),player[aplayer]->maxhp-player[aplayer]->hp);
				}
			}
			else
			{std::cout<<aplayer<<"a"<<std::endl;
				int bplayer=tankmap[ax][ay];
				tankmap[ax][ay]=EMPTY;
				double armor=player[bplayer]->ar;
				int bleed=std::max(1,(int)(player[aplayer]->att*(1-armor/(10+armor))));
				player[bplayer]->hp-=std::min(bleed,player[bplayer]->hp);
				if (player[bplayer]->hp==0)
				{
					player[bplayer]->survive=false;
					tankmap[player[bplayer]->x][player[bplayer]->y]=EMPTY;
					player[bplayer]->x=0;
					player[bplayer]->y=0;
					player[bplayer]->cd=2;
					player[bplayer]->killed++;
					player[aplayer]->kill++;
					player[aplayer]->exp+=std::max(1,player[bplayer]->level/2);
					if (player[aplayer]->level<player[bplayer]->level) player[aplayer]->exp+=3*(player[bplayer]->level-player[aplayer]->level);
					bool tt=upgrade(aplayer);
					while (tt) tt=upgrade(aplayer);
				}std::cout<<aplayer<<"a"<<bplayer<<std::endl;
			}
            return true;
		}
}

void env::printResult()
{
	scoreSort();
	std::cout<<std::setw(6)<<"ID"<<std::setw(4+7)<<"Score"<<std::setw(4)<<"Lv"<<std::setw(5)<<"HP"<<std::setw(6)<<"MaxHP"<<std::setw(4)<<"Sp"<<std::setw(4)<<"Att"<<std::setw(4)<<"Ar"<<std::setw(5)<<"Kill"<<std::setw(4)<<"Die"<<std::endl;
	for (int i=1;i<=totalplayer;++i)
		std::cout<<std::setw(10)<<player[sequence[i]]->Identifier<<std::setw(7)<<getscore(sequence[i])<<std::setw(4)<<player[sequence[i]]->level<<std::setw(5)<<player[sequence[i]]->hp<<std::setw(6)<<player[sequence[i]]->maxhp<<std::setw(4)<<player[sequence[i]]->sp<<std::setw(4)<<player[sequence[i]]->att<<std::setw(4)<<player[sequence[i]]->ar<<std::setw(5)<<player[sequence[i]]->kill<<std::setw(4)<<player[sequence[i]]->killed<<std::endl;
	//std::cout<<"done"<<std::endl;
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
