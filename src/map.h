#ifndef map_H_
#define map_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "stages.h"


#define map_width 1500	
#define map_height 1500
int map1(int *levels);
void input1 (int *continuer,int *f,int *s,inpu *in);
int Deplacement_Perso1 (perso *per,int *l,int *s,SDL_Rect *camera,background level,button *butn);
void scrolling1 (perso *per, SDL_Rect *camera);
void init1 (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level,button *butn,int levels);
int collision_back1(perso *dante,background a,button *butn);
void animation1(perso *per);
void init_button(button *butn);
#endif
