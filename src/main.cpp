#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.c"
#include "stages.c"
#include "map.h"
int main(int argc, char *argv[])
{
    int stage=1;
    //map();
    //stage=menu();
    if (stage==1)
    {
    	stage1();
    }
    else if (stage==2)
    {
        stage2();
    }
    return 0;
}


