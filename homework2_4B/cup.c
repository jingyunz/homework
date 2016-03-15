#include <stdio.h>
#include <stdlib.h>
#include "cup.h"

extern int times;

void cmove(cup *cup1,cup *cup2)
{
    int move;
    if((*cup1).now<(*cup2).full-(*cup2).now)
     move=(*cup1).now;
    else
     move=(*cup2).full-(*cup2).now;

    (*cup1).now-=move;
    (*cup2).now=(*cup2).now+move;

    times++;

}
