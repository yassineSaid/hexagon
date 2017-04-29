#include "stage1.h"
#include "stage.h"
#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>
void stage1()
{
    int continuer=1,f=0,s=0,cpt=0,t=0,cnt2=0,cnt3=0,action=0;
    SDL_Surface *ecran = NULL;
    SDL_Rect positionFond,camera;
    background level;
    perso per;
    inpu in;
    button butn;
    tableau tab;
    pause ps;
    const int FPS=60;
    Uint32 start;
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    init (&per,&camera,&positionFond,&in,ecran,&level,&butn,&tab,&ps);
    while (continuer!=0)
    {
        start=SDL_GetTicks();
        input(&continuer,&f,&s,&in,butn,&tab,&ps);
        Deplacement_Perso(&per,&f,&s,&camera,level,&butn);
        scrolling(&per,&camera);
        animation(&per);
        cpt++;
        if (cpt==5)
        {
            cpt=0;
            level.anim++;
            if (level.anim>5)
                level.anim=0;
        }
        SDL_BlitSurface(level.back[level.anim],&camera,ecran,&positionFond);
        SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
        if (butn.show==1)
        {
            SDL_BlitSurface(butn.button,NULL,ecran,&butn.position);
        }
        animation_tableau(&tab,&butn,ecran);
        pause_menu(&ps,ecran,&continuer,&cnt3,level,positionFond,camera);
        SDL_Flip(ecran);
        if (1000/FPS>SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    SDL_FreeSurface(ecran);
    SDL_Quit();

}

void init (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level,button *butn,tableau *tab,pause *ps)
{
    int i;
    char im[50];
    (*per).position.x=6000;
    //(*per).position_affichage.x=10;
    (*per).height=144;
    (*per).width=26;
    (*per).state=0;
    (*per).state0=1;
    (*per).jm=0;
    (*per).col_jm=0;
    (*per).tomb=0;
    (*per).anim=0;
    (*per).inventory=0;
    (*per).speed=5;
    strcpy((*per).name,"Dante");
    strcpy((*per).images,"pablo_testing_imin/pablo_");
    sprintf(im,"%sstill.png",(*per).images);
    (*per).render=IMG_Load("pablo_testing_imin/pablo_00000.png");
    (*level).back_col=IMG_Load("stage1_col.jpg");
    (*level).anim=0;
    (*per).position.y=(detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),*level)-147);
    (*camera).x=6000;
    (*camera).y=0;
    (*camera).h=600;
    (*camera).w=1366;
    (*positionFond).x=0;
    (*positionFond).y=0;
    (*in).up=0;
    (*in).down=0;
    (*in).left=0;
    (*in).right=0;
    butn->n_tab=0;
    butn->position.x=1000;
    butn->position.y=500;
    butn->button=IMG_Load("buttons/button.png");
    tab->affichage_tab=0;
    tab->cnt2=0;
    ps->pause=0;
    ps->resume=0;
    for(i=0; i<=83; i++)
    {
        sprintf(im,"images/kteb/kteb_%05d.png",i);
        ps->kteb[i]=IMG_Load(im);
    }
    for(i=0; i<6; i++)
    {
        sprintf(im,"images/background/stage1 edit_%05d.jpg",i);
        level->back[i]=IMG_Load(im);
    }
    for(i=0; i<49; i++)
    {
        sprintf(im,"%s%05d.png",(*per).images,i);
        (*per).walk_right[i]=IMG_Load(im);
    }
    strcpy((*per).images,"pablo_testing_isar/pablo_");
    for(i=0; i<49; i++)
    {
        sprintf(im,"%s%05d.png",(*per).images,i);
        (*per).walk_left[i]=IMG_Load(im);
    }
    /*for(i=0;i<7;i++)
    {
    	sprintf(im,"%sjump%d.png",(*per).images,i+1);
    	jump[i]=IMG_Load(im);
    }
    for(i=0;i<5;i++)
    {
    	sprintf(im,"%swalk_left%d.png",(*per).images,i+1) ;
    	walk_left[i]=IMG_Load(im);
    }
    for(i=0;i<7;i++)
    {
    	sprintf(im,"%sjump_left%d.png",(*per).images,i+1);
    	jump_left[i]=IMG_Load(im);
    }
    for(i=0;i<7;i++)
    {
    	sprintf(im,"%sjump_right%d.png",(*per).images,i+1);
    	jump_right[i]=IMG_Load(im);
    }
    for(i=0;i<7;i++)
    {
    	sprintf(im,"%ssliding%d.png",(*per).images,i+1);
    	sliding[i]=IMG_Load(im);
    }
    for(i=0;i<3;i++)
    {
    	sprintf(im,"%sduck%d.png",(*per).images,i+1);
    	duck[i]=IMG_Load(im);
    }*/
}

void black (SDL_Surface *ecran, int trans,int *t)
{
    SDL_Rect positionCarre;
    SDL_Surface *carre=NULL;
    positionCarre.x=0;
    positionCarre.y=0;
    carre = SDL_CreateRGBSurface(SDL_SWSURFACE, 1400, 600, 32, 0, 0, 0, 0);
    SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    if ((*t)<trans)
    {
        (*t)+=1;
        SDL_SetAlpha(carre, SDL_SRCALPHA, trans);
        SDL_BlitSurface(carre, NULL, ecran, &positionCarre);
    }
}
void animation_tableau(tableau *tab,button *butn,SDL_Surface *ecran)
{
    char im[50];
    if (tab->affichage_tab==1)
    {
        if (butn->n_tab==1)
        {
            sprintf(im,"images/animation tableau/tableau_%05d.jpg",tab->cnt2);
            tab->tableau[tab->cnt2]=IMG_Load(im);
            SDL_BlitSurface(tab->tableau[tab->cnt2],NULL,ecran,NULL);
            SDL_FreeSurface(tab->tableau[tab->cnt2]);
            tab->cnt2++;
        }
        else if (butn->n_tab==2)
        {
            sprintf(im,"images/animation tableau1/tableau_%05d.jpg",tab->cnt2);
            tab->tableau[tab->cnt2]=IMG_Load(im);
            SDL_BlitSurface(tab->tableau[tab->cnt2],NULL,ecran,NULL);
            SDL_FreeSurface(tab->tableau[tab->cnt2]);
            tab->cnt2++;
        }
    }
    if ((tab->cnt2)==200)
    {
        tab->affichage_tab=0;
        tab->cnt2=0;
        butn->n_tab=0;
    }
}


