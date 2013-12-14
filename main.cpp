#include "TAAI_HARD.h"
#include "TAAI_LUNATIC.h"
#include "TAAI_CRAZY.h"
#include "st26.h"
#include "st24.h"
env system;
env& fish::host=system;

int main()
{
    for (int i=0;i<=9;i++) system.addAI(new TAAI());
    //system.addAI(new TAAI());
    //system.addAI(new TAAI_LUNATIC());
    //system.addAI(new TAAI_HARD());
    //system.addAI(new TAAI_HARD());
    //system.addAI(new TAAI_HARD());
    //system.addAI(new TAAI_HARD());
    system.addAI(new st26());
    system.addAI(new st24());
    system.play();
}
