#include "env.h"

env()
{
	totalPlayer=0;
	for (int i=0;i<=N;++i)
		for (int j=0;j<=M;++j)
			tankmap[i][j]=EMPTY;
	for (int i=0;i<=MAX_PLAYER;i++)
		sequence[i]=0;
}

~env()
{
	for (int i=1;i<=totalPlayer;++i)
		delete player[i];
}

bool env::addAI(fish* newplayer)
{
	totalPlayer++;
	if (totalPlayer>MAX_PLAYER)
	{
		totalPlayer--;
		return false;
	}
	else
	{
		player[totalPlayer]=newplayer;
		return true;
	}
	player[totalPlayer]->id=totalPlayer;
}

void env::play()
{
	srand(time(NULL));
	for (int i=1;i<=totalPlayer;++i)
		arrangePosition(i);
	for (int i=1;i<=totalPlayer;++i)
		player[i]->init();
	createFood();
	for (int i=1;i<=MAX_ROUND;++i)
		round(i);
	printResult();
}

void env::arangePosition(int newplayer)
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

void env::round(int x);
{
	if (x%FOOD_ROUND==0) createFood();
	for (int i=1;i<=totalPlayer;++i)
		if (player[i]->survive)
		{
			player[i]->exp++;
			upgrade(i);
		}
	actionSort();
	for (int i=1;i<=totalPlayer;++i)
		if (player[sequence[i]]->survive)
			player[sequence[i]]->play();
			else
			{
				if (player[sequence[i]]->cd>0)
					player[sequence[i]]->cd--;
					else
					{
						player[sequence[i]]->survive=true;
						player[sequence[i]]->hp=max(2,player[sequence[i]]->maxhp/4);
						int rx=0,ry=0;
						revive(rx,ry);
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
						tankmap[rx][ry]=newplayer;
						player[newplayer]->x=rx;
						player[newplayer]->y=ry;
						player[sequence[i]]->play();
					}
			}
	cout<<"round "<<x<<endl; 
}

void env::actionSort();
{
	for (int i=1;i<=totalPlayer;++i)
		t[i]=true;
	for (int i=1;i<=totalPlayer;++i)
	{
		int fastPlayer=0;
		for (int j=1;j<=totalPlayer;++j)
			if ((t[j])&&((fastPlayer==0)||(bigthan(j,fastPlayer))))
				fastPlayer=j;
		sequence[i]=j;
		t[j]=false;
	}
}

void env::bigthan(int aplayer,int bplayer)
{
	if ((player[aplayer]->sp>player[bplayer]->sp)||((player[aplayer]->sp==player[bplayer]->sp)&&(player[aplayer]->hp<player[bplayer]->hp))
	||((player[aplayer]->sp==player[bplayer]->sp)&&(player[aplayer]->hp==player[bplayer]->hp)&&(player[aplayer]->level<player[bplayer]->level))
	||((player[aplayer]->sp==player[bplayer]->sp)&&(player[aplayer]->hp==player[bplayer]->hp)&&(player[aplayer]->level==player[bplayer]->level)&&(getscore(aplayer)<getscore(bplayer))))
		return true;
		else return false;
}

void env::getscore(int aplayer)
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
	return totalPlayer;
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
	if ((tankmap[mx][my]!=EMPTY)||(abs(player[aplayer]->x-mx)+abs(player[aplayer]->y-my)>player[aplayer]->sp))
		return false;
		else
		{
			tankmap[player[aplayer]->x][player[aplayer]->y]=EMPTY;
			player[aplayer]->x=mx;
			player[aplayer]->y=my;
			tankmap[mx][my]=aplayer;
			return true;
		}
}

bool env::attack(int aplayer,int ax,int ay)
{
	if ((tankmap[mx][my]==EMPTY)||(abs(player[aplayer]->x-mx)+abs(player[aplayer]->y-my)>1))
		return false;
		else
		{
			if (tankmap[mx][my]==FOOD)
			{
				if (player[aplayer]->att>0)
				{
					player[aplayer]->exp++;
					upgrade(aplayer);
					player[aplayer]->hp+=min(max(2,player[aplayer]->maxhp/4),maxhp-hp);
				}
			}
			else
			{
				int bplayer=tankmap[mx][my];
				double armor=player[bplayer]->ar;
				int bleed=max(1,(int)(player[aplayer]->att*(1-armor/(10+armor))));
				player[bplayer]->hp-=min(bleed,player[bplayer]->hp);
				if (player[bplayer]->hp==0)
				{
					player[bplayer]->survive=false;
					tankmap[player[bplayer]->x][player[bplayer]->y]=EMPTY;
					player[bplayer]->x=0;
					player[bplayer]->y=0;
					player[bplayer]->cd=2;
					player[bplayer]->killed++;
					player[aplayer]->kill++;
					player[aplayer]->exp+=max(1,player[bplayer]->level/2);
					if (player[aplayer]->level<player[bplayer]->level) player[aplayer]->exp+=3*(player[bplayer]->level-player[aplayer]->level);
					bool tt=upgrade(aplayer);
					while (tt) upgrade(aplayer);
				}
			}
			return true;
		}
}

void env::printResult()
{
	scoreSort();
	cout<<setw(6)<<"ID"<<setw(4+7)<<"Score"<<stew(4)<<"Lv"<<stew(5)<<"HP"<<setw(6)<<"MaxHP"<<setw(4)<<"Sp"<<setw(4)<<"Att"<<setw(4)<<"Ar"<<setw(5)<<"Kill"<<setw(4)<<"Die";
	for (int i=1;i<=totalplayer;++i)
		cout<<setw(10)<<player[sequence(i)]->Identifier<<setw(7)<<getscore(sequence[i])<<stew(4)<<player[sequence(i)]->level<<stew(5)<<player[sequence(i)]->hp<<setw(6)<<player[sequence(i)]->maxhp<<setw(4)<<player[sequence(i)]->sp<<setw(4)<<player[sequence(i)]->att<<setw(4)<<player[sequence(i)]->ar<<setw(5)<<player[sequence(i)]->kill<<setw(4)<<player[sequence(i)]->killed;
}

void env::scoreSort()
{
	for (int i=1;i<=totalPlayer;++i)
		t[i]=true;
	for (int i=1;i<=totalPlayer;++i)
	{
		int dickPlayer=0;
		for (int j=1;j<=totalPlayer;++j)
			if ((t[j])&&((dickPlayer==0)||(getscore(j)>getscore(dickPlayer))))
				dickPlayer=j;
		sequence[i]=j;
		t[j]=false;
	}
}
