#ifndef MENU_H_
#define MENU_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
typedef struct
{
	SDL_Rect positionButton[6], positionButtonu[6], positionMouse[6][2], positionHelp[9], positionVolumeM[20], positionVolumeB[20];
	SDL_Rect positionTexteSetting[4],positionFond,positionMouseSetting[4][2];
	SDL_Surface *Menu_anime[200][2],*button[6],*buttonu[6],*intro[450],*Cinematique[953];
	TTF_Font *police;
	int tailleHelp,tailleSetting,full,anim,resolution_courante,resolution_antecedante,loaded;
	char smenu[12],nom_fichier[20];
	FILE *f;
}position;
typedef struct 
{
	int volm,volb;
}affichage;
void initialiser_intro(position *a,int nombre_images,const char chemin_w[],const char chemin_f[], SDL_Surface *ecran);
int initialiser_cinematique(void *ptr);
void cinematique(position *a,SDL_Surface **intro,int nombre_de_images,const char *song_name, SDL_Surface *ecran);
int menu();
//void pause();
void fullscreen(position *pos);
void smallscreen(position *pos);
void help(int tailleHelp, SDL_Color couleurHelp, int *p, position *pos, SDL_Surface *ecran);
void setting (int *volm, int *volb, position *pos, SDL_Surface *ecran, Mix_Chunk *ding,int *p);
void TxtSetting (SDL_Surface *texteSetting[], SDL_Surface *texteSettingu[], position *pos);
void loading(position *pos);
void loading_c(position *pos);
int initialiser(void *ptr);
void read_file(position *a,int *volb,int *volm);
#endif
