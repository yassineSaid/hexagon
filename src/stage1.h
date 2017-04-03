#ifndef stage1_H_
#define stage1_H_
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
	SDL_Surface *back,*back_col;
}background;
typedef struct
{
	SDL_Rect position,position_affichage;
	SDL_Surface *render,*still,*walk_left[49],*walk_right[49],*jump[5],*jump_left[7],*jump_right[7],*sliding[7],*duck[3];
	int state,state0,anim,tentatives,inventory,height,width,speed;
	char name[6],images[50];
}perso;
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
typedef struct 
{
	int left,right,up,down;
}inpu;
void stage1();
void input (int *continuer,int *f,int *s,inpu *in);
int Deplacement_Perso (perso *per,int f,int *s,SDL_Rect *camera,background level);
void scrolling (perso *per, SDL_Rect *camera);
void init (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level);
int collision_back(perso *dante,background a);
SDL_Color GetPixel (SDL_Surface* pSurface,int x,int y);
void animation(perso *per);
int detec_sol (int x,background a);
#endif
