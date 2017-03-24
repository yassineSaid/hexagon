#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "stage1.h"
int main(int argc, char *argv[])
{
	int continuer=1,x=0,y=0,f=0,m=0,s=0;
	SDL_Surface *ecran = NULL,*fond = NULL,*bass = NULL;
	SDL_Rect positionFond,camera;
	SDL_Event event;
	perso per;
	inpu in;
	SDL_Init(SDL_INIT_VIDEO);
	in.up=0;
	in.down=0;
	in.left=0;
	in.right=0;
	positionFond.x=0;
	positionFond.y=0;
	camera.x=0;
	camera.y=0;
	camera.h=600;
	camera.w=1366;
	per.position.x=90;
	per.position.y=250;
	per.height=338;
	per.width=160;
	per.position_affichage.x=per.position.x;
	per.position_affichage.y=per.position.y;
	ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	fond=IMG_Load("stage1 edit.jpg");
	bass=IMG_Load("bassem.png");
	SDL_BlitSurface(fond,&camera,ecran,&positionFond);
	SDL_BlitSurface(bass,NULL,ecran,&per.position_affichage);
	SDL_Flip(ecran);
	while (continuer!=0)
    {
    	input(&continuer,&f,&s,&in);
		m=Deplacement_Perso(&per,f,&s,&camera);
	    scrolling(&per,&camera);
		SDL_BlitSurface(fond,&camera,ecran,&positionFond);
		SDL_BlitSurface(bass,NULL,ecran,&per.position_affichage);
		SDL_Flip(ecran);
		m=0;
    }
    SDL_FreeSurface(ecran);
    SDL_Quit();
 
    return EXIT_SUCCESS;
}
