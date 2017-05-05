#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.c"
#include "stages.c"
#include "map.c"
int main(int argc, char *argv[])
{
    int stage=1;
    map1();
    //stage=menu();
    if (stage==1)
    {
    	stage=stage1();
    }
    if (stage==2)
    {
        stage2();
    }
    return 0;
}


