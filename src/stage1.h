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
	SDL_Surface *back[6],*back_col,*back1;
	int anim,cpt;
}background;
typedef struct
{
	SDL_Rect position,position_affichage,position_jump,position_pre_jump;
	SDL_Surface *still[3],*render,*walk_left[8],*walk_right[8],*jump_left[8],*jump_right[8],*sliding[7],*duck[3];
	int state,state0,anim,tentatives,inventory,height,width,speed,interacted,jumping,jm,col_jm,tomb;
	char name[6],images[50];
	SDL_Color couleur[8];
}perso;
typedef struct
{
    SDL_Surface *image_inventaire,*image_object[4];
    SDL_Rect position;
    SDL_Rect position_objects[6];
    int objects_type[6],filled[6];
    int pickedobject,filledonce,selected,use;

}inventaire;
typedef struct
{
	SDL_Surface *kteb[84];
	int pause,resume;
	inventaire inv;
}pause;
typedef struct
{
    SDL_Surface *tableau[201];
    int cnt2,play;
}tableau;
typedef struct
{
    SDL_Surface *papier;
    SDL_Rect positionindices[2],positiononscreen[2];
    int taken[2],npaper,pickedonce[2];
}indices;
typedef struct
{
    SDL_Surface *door_A[4][4];
	SDL_Rect position[3],position_affichage[3];
	int state[3],ndoor,code,cnt[3],cnt_delay;
}doors;
typedef struct
{
	SDL_Surface *mir, *soc;
	SDL_Surface *button[2];
	SDL_Rect position[2],position_affichage[2];
	int show,n_tab,cnt_blit;
}button;
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
	int left,right,up,down,escape;
}inpu;
void stage1();
void input (int *continuer, int *f,int *s,inpu *in);
void Deplacement_Perso (perso *per,int *l,int *s,SDL_Rect *camera,background level);
void scrolling (perso *per, SDL_Rect *camera);
void init (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level,button *butn,tableau *tab,pause *ps,indices *ind,doors *door,mirror *mirro);
int collision_back(perso *dante,background a);
SDL_Color GetPixel (SDL_Surface* pSurface,int x,int y);
void animation(perso *per,int *cpt_perso);
int detec_sol (int x,background a);
void black (SDL_Surface *ecran, int trans,int *t);
void animation_tableau(perso *per,tableau *tab,button *butn,SDL_Surface *ecran);
void pause_menu(pause *ps,SDL_Surface *ecran,int *continuer,int *compteur,background level,SDL_Rect positionFond,SDL_Rect camera);
void Affichage_objet(indices *ind,SDL_Rect *camera,SDL_Surface *ecran,perso *per,doors *door,pause *ps);
void check_changement(int *f,perso *dante,button *butn,pause *ps,indices *ind,doors *door);
void blit_button(button *butn,SDL_Surface *ecran);
void affichage_background(background *level,SDL_Surface *ecran,SDL_Rect camera);
#endif
