#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "stages.h"
#include "map.h"
int main(int argc, char *argv[])
{
    int stage=0,levels=1;
    //stage=menu();
    if (stage==0)
    stage=map1(&levels);
    if (stage==1)
    {
    	levels=stage1();
    }
    if (stage==1)
    stage=map1(&levels);
    if (stage==2)
    {
        levels=stage2();
    }
    if (stage==2)
    stage=map1(&levels);
    if (stage==3)
    {
        stage3();
    }
    return 0;
}



