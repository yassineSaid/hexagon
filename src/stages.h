#ifndef stages_H_
#define stages_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


#define level_width 10000
//#define level_height 1200
#define screen_width 1366
#define screen_height 600
typedef struct
{
	SDL_Surface *back[25],*back_col,*back1;
	int anim,cpt;
}background;
typedef struct
{
	SDL_Rect position,position_affichage,position_jump,position_pre_jump;
	SDL_Surface *still[3],*render,*walk_left[8],*walk_right[8],*jump_left[8],*jump_right[8],*sliding[7],*duck[3];
	int state,state0,anim,tentatives,inventory,height,width,speed,interacted,jumping,jm,col_jm,tomb,col;
	char name[6],images[50];
	SDL_Color couleur[8];
}perso;
typedef struct
{
	SDL_Surface *cerebus_imin[7],*cerebus_isar[7];
	SDL_Rect position,position_affichage;
	int compteur_enemie,cnt_blit,etat;
}enemie;
typedef struct
{
    SDL_Surface *image_inventaire,*image_object[5];
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
    int taken[3],npaper,pickedonce[3];
}indices;
typedef struct
{
    SDL_Surface *door_A[4][5];
	SDL_Rect position[3],position_affichage[3];
	int state[3],ndoor,code,cnt[3],cnt_delay,burning_cnt;
}doors;
typedef struct
{
	SDL_Surface *button[2];
	SDL_Rect position,position_affichage;
	int show,n_tab,cnt_blit;
}button;
typedef struct
{
	SDL_Surface *mir, *soc,*rotated;
	SDL_Rect position[2],position_affichage[2];
	int reflection,det,ok;
	double angle;
}mirror;
typedef struct
{
	SDL_Rect position,position_affichage;
	int state;
}socrates;
typedef struct
{
    SDL_Surface *buck;
	SDL_Rect position,position_affichage;
	int n_bucket,picked,full;
}bucket;
typedef struct
{
    SDL_Surface *key;
	SDL_Rect position,position_affichage;
	int n_key,picked,used;
}keys;
typedef struct
{
    SDL_Surface *plant[94];
	SDL_Rect position,position_affichage;
	int state,cnt,n_plant,water_fall;
}plant;
typedef struct
{
	SDL_Surface *light,*rotated;
	SDL_Rect position,position_affichage;
	double reflection;
	int ok;
}lumiere;
typedef struct
{
	int left,right,up,down,escape;
}inpu;
typedef struct
{
	SDL_Surface *l[3],*button[10][2];
	SDL_Rect position,position_button[10],position_mouse[10][2];
	int state,interacted,n_lock;
}locks;
void stage2();
void init_stage2(perso *per,SDL_Rect *camera,inpu *in,SDL_Surface *ecran,background *level,button *butn,pause *ps,button *butn1,enemie *mob,enemie *mob2);
void init_background2(background *level);
void mob_yitharek(enemie *mob,SDL_Rect *camera,SDL_Surface *ecran);
void initialitation_mob(enemie *mob);
/////////////////////////////////////////////
int stage1();
void input(int *continuer, int *f,int *s,inpu *in,int *manette,char d[3]);
void Deplacement_Perso (perso *per,int *l,int *s,SDL_Rect *camera,background level,int *level_height);
void scrolling (perso *per, SDL_Rect *camera,int *level_height);
void init_stage1(perso *per,SDL_Rect *camera,inpu *in,SDL_Surface *ecran,background *level,button *butn,tableau *tab,pause *ps,indices *ind,doors *door,mirror *mirro,bucket *buck,keys *key,plant *pl,lumiere *lum,button *butn1,locks *lo);
void collision_back(perso *dante,background a);
SDL_Color GetPixel (SDL_Surface* pSurface,int x,int y);
void animation(perso *per,int *cpt_perso);
int detec_sol (int x,background a,int *level_height);
void black (SDL_Surface *ecran, int trans,int *t);
void animation_tableau(perso *per,tableau *tab,button *butn,SDL_Surface *ecran);
void pause_menu(pause *ps,SDL_Surface *ecran,int *continuer,int *compteur,background level,SDL_Rect camera,int *manette);
void Affichage_objet(indices *ind,SDL_Rect *camera,SDL_Surface *ecran,perso *per,doors *door,pause *ps,mirror *mirro,bucket *buck,plant *pl,keys *key,lumiere *lum,locks *lo);
void check_changement(int *f,perso *dante,button *butn,pause *ps,indices *ind,doors *door,bucket *buck,plant *pl,keys *key,mirror *mirro,locks *lo);
void blit_button(button *butn,SDL_Surface *ecran);
void affichage_background(background *level,SDL_Surface *ecran,SDL_Rect camera);
void collision_doors(perso *dante,doors *door);
void watering_plant(pause *ps,bucket *buck,plant *pl);
void fill_bucket(pause *ps,bucket *buck,plant *pl);
void open_door_with_key(pause *ps,doors *door,keys *key);
void read_paper(pause *ps,perso *per,SDL_Surface *ecran);
void blit_door_in_both_states(doors *door,perso *per,SDL_Rect *camera,SDL_Surface *ecran,locks *lo);
void blit_paper(indices *ind,pause *ps,SDL_Surface *ecran,SDL_Rect *camera,perso *per);
void blit_bucket(bucket *buck,pause *ps,SDL_Surface *ecran,SDL_Rect *camera,perso *per);
void blit_plant(plant *pl,SDL_Rect *camera,SDL_Surface *ecran);
void blit_key(keys *key,SDL_Rect *camera,plant *pl,perso *per,pause *ps,SDL_Surface *ecran);
void blit_mirroir(mirror *mirro,SDL_Rect *camera,SDL_Surface *ecran,perso *per,lumiere *lum);
void rotation_mirroir(mirror *mirr,button *butn1,background *level,SDL_Surface *ecran,SDL_Rect *camera,perso *per,lumiere *lum,doors *door);
void bruler_porte(lumiere *lum,doors *door,SDL_Surface *ecran);
int lock (perso *per,SDL_Surface *ecran,background level,SDL_Rect camera,locks *lo);
void init_perso(perso *per);
void init_portes(doors *door,locks *lo);
void init_mirroire(mirror *mirro,lumiere *lum);
void init_buttons(button *butn,button *butn1);
void init_pause_menu(pause *ps);
void init_bucket(bucket *buck);
void init_key(keys *key);
void init_plant(plant *pl);
void init_indices(indices *ind);
void init_background1(background *level);
void init_input(inpu *in);
int arduinoReadData(int *x,char s[3]);
int arduinoWriteData(int x);
#endif
