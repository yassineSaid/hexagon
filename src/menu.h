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
	TTF_Font *police;
	int tailleHelp,tailleSetting,full,anim;
	char smenu[12];
}position;
int menu();
void pause();
void fullscreen(position *pos);
void smallscreen(position *pos);
void help(char policeHelp[],int tailleHelp, SDL_Color couleurHelp, int *p, position *pos, SDL_Surface *ecran);
void setting (int *volm, int *volb, position *pos, SDL_Surface *ecran, Mix_Chunk *ding,int *p);
void TxtSetting (SDL_Surface *texteSetting[], SDL_Surface *texteSettingu[], position *pos);
#endif