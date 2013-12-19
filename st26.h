#ifndef st26_h
#define st26_h

#include "fish.h"
#include "cstdlib"

class st26:public fish{
	private:
		int a[41][41];
		int gameRound;
		void increase();
		void check();
		bool kexing(int,int);
		void beginAttack(int,int);
		void eatAndAttack();
	public:
		void init();
		void play();
		void revive(int&,int&);
		st26();
		~st26();
}; 
#endif
