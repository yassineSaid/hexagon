#ifndef map_H_
#define map_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "stages.h"


#define map_width 2500
#define map_height 2500
void map1();
void input1 (int *continuer,int *f,int *s,inpu *in);
int Deplacement_Perso1 (persomap *per,int *l,int *s,SDL_Rect *camera,background level);
void scrolling1 (persomap *per, SDL_Rect *camera);
void init1 (persomap *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level);
int collision_back1(persomap *dante,background a);
void animation1(persomap *per);
#endif