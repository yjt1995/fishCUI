#ifndef env_h
#define env_h

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include "constants.h"

class fish;

class env
{
	public:
		env();
		~env();
		bool addAI(fish*);
		void play();
		void round(int);
		void printResult();
		int getTotalPlayer();
		int getMap(int,int);
		int getHP(int);
		bool move(int,int,int);
		bool attack(int,int,int); 
	private:
		int totalplayer;
		int tankmap[N+1][M+1];
		fish* player[MAX_PLAYER+1];
		int sequence[MAX_PLAYER+1];	
		bool t[MAX_PLAYER+1];
}

#endif
