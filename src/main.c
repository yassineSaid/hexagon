#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "stage1.h"
int main(int argc, char *argv[])
{
    int stage;
    stage=menu();
    if (stage==1)
    {
    	stage1();
    }
    return 0;
}


