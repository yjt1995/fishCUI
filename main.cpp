#include "env.h"
#include "fish.h"
#include "TAAI.h"
#include "TAAI_HARD.h"
#include "TAAI_LUNATIC.h"
#include "TAAI_CRAZY.h"
#include "st26.h"
#include "st24.h"
#include "st04.h"
#include "st18.h"
env syst;
env& fish::host=syst;

int main()
{
    for (int i=0;i<=20;i++) syst.addAI(new TAAI());
    syst.addAI(new TAAI());
    syst.addAI(new TAAI());
    syst.addAI(new TAAI());
    syst.addAI(new TAAI());
    //syst.addAI(new st26());
    //system.addAI(new TAAI_HARD());
    //system.addAI(new TAAI_HARD());
    //system.addAI(new TAAI_HARD());
    //system.addAI(new TAAI_HARD());
    syst.addAI(new st26());
    syst.addAI(new st04());
   // syst.addAI(new st18());
    syst.addAI(new st24());
    syst.play();
}

