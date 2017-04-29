#ifndef stage1_H_
#define stage1_H_
#include "menu.h"
#include "stage.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


#define level_width 10000
#define level_height 600
#define screen_width 1366
#define screen_height 600
typedef struct
{
    SDL_Surface *tableau[201];
    int affichage_tab,cnt2;
}tableau;
typedef struct
{
	SDL_Rect position,position_affichage;
	int angle,reflection;
}mirror;
typedef struct
{
	SDL_Rect position,position_affichage;
	int state;
}socrates;
typedef struct
{
	SDL_Rect position,position_affichage;
	int state;
}bucket;
typedef struct
{
	SDL_Rect position,position_affichage;
	int state;
}plant;
typedef struct
{
	SDL_Rect position,position_affichage;
	int state;
}door1;
typedef struct
{
	SDL_Rect position,position_affichage;
	int state;
}door2;
typedef struct
{
	SDL_Rect position,position_affichage;
	int state,code;
}door3;
void stage1();
void init (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level,button *butn,tableau *tab,pause *ps);
void animation_tableau(tableau *tab,button *butn,SDL_Surface *ecran);
#endif
