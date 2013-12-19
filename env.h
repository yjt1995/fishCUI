#ifndef env_h
#define env_h

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "constants.h"

class fish;

class env
{
	public:
		env();
		~env();
		bool addAI(fish*);
		void play();
		int getTotalPlayer();
		int getMap(int,int);
		int getHP(int);
		bool move(int,int,int);
		bool attack(int,int,int);
	private:
		void arrangePosition(int);
		void createFood();
		void actionSort();
		bool bigthan(int,int);
		int getscore(int);
		bool upgrade(int);
		void scoreSort();
		void round(int);
		void printResult();
		int totalplayer;
		int tankmap[N+1][M+1];
		fish* player[MAX_PLAYER+1];
		int sequence[MAX_PLAYER+1];
		bool t[MAX_PLAYER+1];
};

#endif
