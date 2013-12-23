#ifndef env_h
#define env_h

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <windows.h>
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
        void welcomeprint();
        void ftrecorder(int);
		void arrangePosition(int);
		void createFood();
		void actionSort();
		void readrecord(int&,int&);
		void printround(int,int);
		bool bigthan(int,int);
		int getscore(int);
		bool upgrade(int);
		void scoreSort();
		void round(int);
		void printResult();
		int totalplayer;
		int modelkind;
		int checkplayer;
		int tankmap[N+1][M+1];
		const char* name[MAX_PLAYER+1];
		char name2[MAX_PLAYER+1][100];
		int ftre[MAX_ROUND+1][MAX_PLAYER+1][14];
		bool ftresta[MAX_ROUND+1][MAX_PLAYER+1];
		fish* player[MAX_PLAYER+1];
		int sequence[MAX_PLAYER+1];
		bool t[MAX_PLAYER+1];
};

#endif
