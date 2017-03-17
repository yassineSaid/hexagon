#ifndef stage1_H_
#define stage1_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
typedef struct
{
	SDL_Rect position,position_affichage;
	int state,tentatives,inventory;
	char name[6];
}perso;
typedef struct 
{
	SDL_Rect position;
	int angle,reflection;
}mirror;
typedef struct 
{
	SDL_Rect position;
	int state;
}socrates;
typedef struct 
{
	SDL_Rect position;
	int state;
}bucket;
typedef struct 
{
	SDL_Rect position;
	int state;
}plant;
typedef struct 
{
	SDL_Rect position;
	int state;
}door1;
typedef struct 
{
	SDL_Rect position;
	int state;
}door2;
typedef struct 
{
	SDL_Rect position;
	int state,code;
}door3;
typedef struct 
{
	int left,right,up,down;
}inpu;
void input (int *continuer,int *f,int *s,inpu *in);
int Deplacement_Perso (perso *per,int f,int *s,SDL_Rect *camera);
#endif