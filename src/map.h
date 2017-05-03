#ifndef map_H_
#define map_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "stages.h"


#define map_width 6000
#define map_height 6000
void map();
void input1 (int *continuer,int *f,int *s,inpu *in);
int Deplacement_Perso1 (perso *per,int *l,int *s,SDL_Rect *camera,background level);
void scrolling1 (perso *per, SDL_Rect *camera);
void init1 (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level);
int collision_back1(perso *dante,background a);
void animation1(perso *per);
#endif
