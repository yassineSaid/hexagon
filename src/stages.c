#include "stages.h"
#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_rotozoom.h>
int stage3()
{
    int continuer=1,f=0,s=0,cpt_perso=0,cnt3=0,manette=0;
    int level_height=1200;
    char d[3];
    SDL_Surface *ecran = NULL;
    SDL_Rect camera;
    background level;
    perso per;
    inpu in;
    button butn,butn1;
    pause ps;
    enemie mob,mob2,mob3;
    health hl;
    hache ha;
    scie sc;
    const int FPS=60;
    Uint32 start;
    Mix_Music *musique;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    init_stage3(&per,&camera,&in,ecran,&level,&butn,&ps,&butn1,&mob,&mob2,&mob3,&hl,&ha);
    init_scie(&sc);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    musique = Mix_LoadMUS("stage3.mp3");
    Mix_PlayMusic(musique, -1);
    while (continuer!=0)
    {
        start=SDL_GetTicks();
        input(&continuer,&f,&s,&in,&manette,d);
        if (per.detectable)
        Deplacement_Perso(&per,&f,&s,&camera,level,&level_height);
        scrolling(&per,&camera,&level_height);
        animation(&per,&cpt_perso);
        check_changement_stage3(&f,&per,&butn,&ps);
        affichage_background(&level,ecran,camera);
        blit_button(&butn,ecran);
        col_hache(&ha,&per,ecran,camera,&hl);
        col_scie(&sc,&per,ecran,camera,&hl);
        health_bar(&hl,ecran,&per,&camera);
        mob_yitharek(&mob,&camera,ecran,2000,1650,&per,5,&hl,1);
        mob_yitharek(&mob2,&camera,ecran,1250,1070,&per,5,&hl,1);
        mob_yitharek(&mob3,&camera,ecran,9000,7300,&per,2,&hl,3);
        if (per.detectable)
        SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
        if (f==11)
        {
            ps.pause=1;

        }
        pause_menu(&ps,ecran,&continuer,&cnt3,level,camera,&manette);
        if (per.position.x>9800)
        {
            return 4;
            continuer=0;
        }
        //fprintf(stderr,"%d\n",per.position.y);
        SDL_Flip(ecran);
        if (1000/FPS>SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    Mix_FreeMusic(musique);
    SDL_FreeSurface(ecran);
    SDL_Quit();

}
int IA(perso *dante , enemie *mob)
{
	int a=0;
	if(((mob->position.x-dante->position.x)<200)&&((mob->position.x-dante->position.x)>(-200)))
	{

		a=1;
	}
	return a;
}
void initialitation_mob(enemie *mob,int positionx,int positiony)
{
    char path[40];
    int i=0;
    mob->position.x=positionx;
    mob->position.y=positiony;
    mob->cnt_blit=0;
    mob->compteur_enemie=0;
    mob->etat=1;
    mob->hitonce=0;
    mob->time=0;
    for (i=0; i<6; i++)
    {
        sprintf(path,"images/cerebus_imin/cerebus%d.png",i);
        mob->cerebus_imin[i]=IMG_Load(path);
    }
    for (i=0; i<6; i++)
    {
        sprintf(path,"images/cerebus_isar/cerebus%d.png",i);
        mob->cerebus_isar[i]=IMG_Load(path);
    }
}
void initialitation_mob_kbir(enemie *mob,int positionx,int positiony)
{
    char path[40];
    int i=0;
    mob->position.x=positionx;
    mob->position.y=positiony;
    mob->cnt_blit=0;
    mob->compteur_enemie=0;
    mob->etat=1;
    mob->hitonce=0;
    mob->time=0;
    for (i=0; i<3; i++)
    {
        sprintf(path,"images/monster/right/%d.png",i+1);  //change here
        mob->cerebus_imin[i]=IMG_Load(path);
    }
    for (i=0; i<3; i++)
    {
        sprintf(path,"images/monster/left/%d.png",i+1); //change here
        mob->cerebus_isar[i]=IMG_Load(path);
    }
}
void init_scie(scie *sc)
{
    int i;
    char im[50];
    sc->cnt=0;
    sc->m=1;
    sc->anim=0;
    sc->hitonce=0;
    sc->time=0;
    sc->position.x=0;
    sc->position.y=0;
    for (i=0;i<14;i++)
    {
        sprintf(im,"images/scie/normal/%d.png",i+1);
        sc->s[i]=IMG_Load(im);
        sprintf(im,"images/scie/col/%d_col.png",i+1);
        sc->s_col[i]=IMG_Load(im);
    }
}
int col_scie (scie *sc,perso *dante,SDL_Surface *ecran,SDL_Rect camera,health *hp)
{
    SDL_Rect point[8];
    SDL_Color couleur[8];
    int i,col=0;

    point[4].x=dante->position.x + dante->render->w/2 + dante->width/2; //HAUT DROIT
    point[4].y=dante->position.y + dante->render->h/4;

    point[0].x=dante->position.x + dante->render->w/2 + dante->width/2; //CENTRE DROIT
    point[0].y=dante->position.y + dante->render->h/2;

    point[5].x=dante->position.x + dante->render->w/2 + dante->width/2; //BAS DROIT
    point[5].y=dante->position.y + (dante->render->h*3)/4;

    point[1].x=dante->position.x + dante->render->w/2; //CENTRE BAS
    point[1].y=dante->position.y + dante->render->h;

    point[3].x=dante->position.x + dante->render->w/2; //CENTRE HAUT
    point[3].y=dante->position.y;

    point[6].x=dante->position.x + dante->render->w/2 - dante->width/2; //HAUT GAUCHE
    point[6].y=dante->position.y + dante->render->h/4;

    point[2].x=dante->position.x + dante->render->w/2 - dante->width/2; //CENTRE GAUCHE
    point[2].y=dante->position.y + dante->render->h/2;

    point[7].x=dante->position.x + dante->render->w/2 - dante->width/2; //BAS GAUCHE
    point[7].y=dante->position.y + (dante->render->h*3)/4;


    couleur[0]=GetPixel (sc->s_col[sc->anim], point[0].x, point[0].y);
    couleur[1]=GetPixel (sc->s_col[sc->anim], point[1].x, point[1].y);
    couleur[2]=GetPixel (sc->s_col[sc->anim], point[2].x, point[2].y);
    couleur[3]=GetPixel (sc->s_col[sc->anim], point[3].x, point[3].y);
    couleur[4]=GetPixel (sc->s_col[sc->anim], point[4].x, point[4].y);
    couleur[5]=GetPixel (sc->s_col[sc->anim], point[5].x, point[5].y);
    couleur[6]=GetPixel (sc->s_col[sc->anim], point[6].x, point[6].y);
    couleur[7]=GetPixel (sc->s_col[sc->anim], point[7].x, point[7].y);

    for (i=0;i<8;i++)
    {
        if (couleur[i].r>=250 && couleur[i].g==0 && couleur[7].b==0)
            col=1;
    }
    sc->cnt++;
    if ((sc->cnt%3)==1)
    {
        sc->anim+=sc->m;
        if (sc->anim>13)
        {
            sc->anim=13;
            sc->m=-1;
        }
        if (sc->anim==0)
        {
            sc->anim=0;
            sc->m=1;
        }

    }
    SDL_BlitSurface(sc->s[sc->anim],&camera,ecran,NULL);
    if (dante->detectable==1)
    {
    if (sc->hitonce==0)
    {
        if (col==1)
        {
        hp->vie--;
        sc->hitonce=1;
        }
    }
    if (sc->hitonce==1)
    {
        sc->time=SDL_GetTicks();
    }
    if ((sc->time%2000)==0)
    {
        sc->hitonce=0;
        sc->time=0;
    }
    }
    //printf("hitonce=%d\n",sc->hitonce);
    //printf("time=%d\n",sc->time);
    return col;
}
void init_hache(hache *ha)
{
    int i;
    char im[50];
    ha->m=2;
    ha->p=0;
    ha->cnt=0;
    ha->anim=0;
    ha->hitonce=0;
    ha->position.x=0;
    ha->position.y=0;
    ha->time=0;
    for (i=0;i<13;i++)
    {
        sprintf(im,"images/hache/normal/%d.png",i+1);
        ha->h[i]=IMG_Load(im);
        sprintf(im,"images/hache/col/%d_col.png",i+1);
        ha->h_col[i]=IMG_Load(im);
    }
}
int col_hache (hache *ha,perso *dante,SDL_Surface *ecran,SDL_Rect camera,health *hp)
{
    SDL_Rect point[8];
    SDL_Color couleur[8];
    int i,col=0;

    point[4].x=dante->position.x + dante->render->w/2 + dante->width/2; //HAUT DROIT
    point[4].y=dante->position.y + dante->render->h/4;

    point[0].x=dante->position.x + dante->render->w/2 + dante->width/2; //CENTRE DROIT
    point[0].y=dante->position.y + dante->render->h/2;

    point[5].x=dante->position.x + dante->render->w/2 + dante->width/2; //BAS DROIT
    point[5].y=dante->position.y + (dante->render->h*3)/4;

    point[1].x=dante->position.x + dante->render->w/2; //CENTRE BAS
    point[1].y=dante->position.y + dante->render->h;

    point[3].x=dante->position.x + dante->render->w/2; //CENTRE HAUT
    point[3].y=dante->position.y;

    point[6].x=dante->position.x + dante->render->w/2 - dante->width/2; //HAUT GAUCHE
    point[6].y=dante->position.y + dante->render->h/4;

    point[2].x=dante->position.x + dante->render->w/2 - dante->width/2; //CENTRE GAUCHE
    point[2].y=dante->position.y + dante->render->h/2;

    point[7].x=dante->position.x + dante->render->w/2 - dante->width/2; //BAS GAUCHE
    point[7].y=dante->position.y + (dante->render->h*3)/4;


    couleur[0]=GetPixel (ha->h_col[ha->anim], point[0].x, point[0].y);
    couleur[1]=GetPixel (ha->h_col[ha->anim], point[1].x, point[1].y);
    couleur[2]=GetPixel (ha->h_col[ha->anim], point[2].x, point[2].y);
    couleur[3]=GetPixel (ha->h_col[ha->anim], point[3].x, point[3].y);
    couleur[4]=GetPixel (ha->h_col[ha->anim], point[4].x, point[4].y);
    couleur[5]=GetPixel (ha->h_col[ha->anim], point[5].x, point[5].y);
    couleur[6]=GetPixel (ha->h_col[ha->anim], point[6].x, point[6].y);
    couleur[7]=GetPixel (ha->h_col[ha->anim], point[7].x, point[7].y);

    for (i=0;i<8;i++)
    {
        if (couleur[i].r>=250 && couleur[i].g==0 && couleur[7].b==0)
            col=1;
    }
    ha->cnt++;
    if (ha->cnt%2)
    {
        if (ha->p==0)
        {
            if (ha->m==-1)
                ha->anim+=ha->m;
            else if (ha->m==2)
                ha->anim+=ha->m;
        }
        if (ha->anim>12)
        {
            ha->anim=12;
            ha->m=-1;
        }
        if (ha->anim==0)
        {
            ha->anim=0;
            ha->p++;
        }
        if (ha->p>30)
        {
            ha->p=0;
            ha->m=2;
        }

    }
    SDL_BlitSurface(ha->h[ha->anim],&camera,ecran,NULL);
    if (dante->detectable==1)
    {
    if (ha->hitonce==0)
    {
        if (col==1)
        {
        hp->vie--;
        ha->hitonce=1;
        }
    }
    if (ha->hitonce==1)
    {
        ha->time=SDL_GetTicks();
    }
    if ((ha->time%2000)==0)
    {
        ha->hitonce=0;
        ha->time=0;
    }
    }
    return col;
}
void mob_yitharek(enemie *mob,SDL_Rect *camera,SDL_Surface *ecran,int max_position_right,int max_position_left,perso *dante,int nmbrofsprites,health *hl,int speed)
{
    int d=0;
    mob->position_affichage.x=(mob->position.x)-(*camera).x;
    mob->position_affichage.y=(mob->position.y)-(*camera).y;
    //fprintf(stderr,"detectable=%d\n",dante->detectable);
        if (mob->cnt_blit==5)
        mob->compteur_enemie++;
    if (mob->cnt_blit>5)
    {
        mob->cnt_blit=0;
    }
    if (mob->compteur_enemie>nmbrofsprites)
    {
        mob->compteur_enemie=0;
    }
    if(IA(dante,mob))
    {
        if (dante->detectable==1)
    {

        if(dante->position.x<mob->position.x)
    	{
    		mob->etat=2;
    	}
    	else if(dante->position.x>mob->position.x)
    	{
    		mob->etat=1;
    	}
    }
    else if (dante->detectable==0)
    {
        if (mob->position.x>max_position_right)
    	{
        	mob->etat=2;
    	}
    	else if (mob->position.x<max_position_left)
    	{
        	mob->etat=1;
    	}
    }
    }
    else
    {
    	if (mob->position.x>max_position_right)
    	{
        	mob->etat=2;
    	}
    	else if (mob->position.x<max_position_left)
    	{
        	mob->etat=1;
    	}
    }
    if(IA(dante,mob))
    {
        if (dante->detectable==1)
    {
    	d=mob->position.x-dante->position.x;
    	if(dante->position.x<mob->position.x)
    	{
            if (mob->position.x<max_position_left)
            {
                mob->position.x+=0;
            }
            else
    		mob->position.x=dante->position.x+d-speed;
    	}
    	else
    	{
           if (mob->position.x>max_position_right)
            {
                mob->position.x+=0;
            }
            else
    		mob->position.x=dante->position.x+d+speed;
    	}
    }
        else if (dante->detectable==0)
        {

        if (mob->etat==1)
        {
        (mob->position.x)+=speed;
        }
        else if (mob->etat==2)
        {
        (mob->position.x)-=speed;
        }
        }
    }
    else
    {
    if (mob->etat==1)
    {
        (mob->position.x)+=speed;
    }
    else if (mob->etat==2)
    {
        (mob->position.x)-=speed;
    }
    }
    if (mob->etat==1)
    {
    SDL_BlitSurface(mob->cerebus_imin[mob->compteur_enemie],NULL,ecran,&mob->position_affichage);
    }
    else if (mob->etat==2)
    {
    SDL_BlitSurface(mob->cerebus_isar[mob->compteur_enemie],NULL,ecran,&mob->position_affichage);

    }
    if (dante->detectable==1)
    {
    if (mob->hitonce==0)
    {
    if (((dante->position.x+(dante->render->w/2))<((mob->position.x+mob->cerebus_imin[0]->w)-20))&&((dante->position.x+(dante->render->w/2))>mob->position.x))
    {
        if (((dante->position.y+5)>mob->position.y)&&((dante->position.y+5)<mob->position.y+mob->cerebus_imin[0]->h))
        {hl->vie--;
        mob->hitonce=1;
        }
    }
    }
    }
    if (mob->hitonce==1)
    {
        mob->time=SDL_GetTicks();
    }
    if ((mob->time%2000)==0)
    {
        mob->hitonce=0;
        mob->time=0;
    }
    //fprintf(stderr,"lives=%d\n",dante->tentatives);
     //fprintf(stderr,"hitonce=%d\n",mob->hitonce);
    mob->cnt_blit++;
}
void check_changement_stage3(int *f,perso *dante,button *butn,pause *ps)
{
    butn->show=0;
    if ((dante->couleur[0].b==255&&dante->couleur[0].g==0&&dante->couleur[0].r==12)||(dante->couleur[2].b==255&&dante->couleur[2].g==0&&dante->couleur[2].r==12))
    {
        butn->show=1;
        butn->cacher=1;
    }
    if ((*f==10)&&(butn->show==1)&&(dante->detectable==1))
        dante->detectable=0;
    else if ((*f==10)&&(butn->show==1)&&(dante->detectable==0))
        dante->detectable=1;
}
void init_background3(background *level)
{
    int i=0;
    char im[50];
    for(i=0; i<25; i++)
    {
        sprintf(im,"images/stage3/stage3.jpg");
        level->back[i]=IMG_Load(im);
    }
    (*level).back_col=IMG_Load("images/stage3/stage3_col.jpg");
    (*level).anim=0;
    level->cpt=0;

}
void init_stage3(perso *per,SDL_Rect *camera,inpu *in,SDL_Surface *ecran,background *level,button *butn,pause *ps,button *butn1,enemie *mob,enemie *mob2,enemie *mob3,health *hl,hache *ha)
{
    init_background3(level);
    init_input(in);
    init_perso(per);
    init_health_bar(hl);
    init_hache(ha);
    initialitation_mob(mob,1800,1050);
    initialitation_mob(mob2,1100,1050);
    initialitation_mob_kbir(mob3,8750,995);
    init_buttons(butn,butn1);
    init_pause_menu(ps);
    per->position.y=600;        //y=215
    per->position.x=300;
    per->detectable=1;
    (*camera).x=4000;
    (*camera).y=0;
    (*camera).h=600;
    (*camera).w=1366;
}
///////////////////////////////////////////////
///////////////////////////////////////////////
int stage2()
{
    int continuer=1,f=0,s=0,cpt_perso=0,cnt3=0,manette=0,chrono=0;
    int level_height=1200;
    char d[3];
    SDL_Surface *ecran = NULL;
    SDL_Rect camera;
    background level;
    perso per;
    inpu in;
    time t;
    button butn,butn1;
    pause ps;
    coins coin;
    Texte texte;
    const int FPS=60;
    Uint32 start;
    Mix_Music *musique;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    init_stage2(&per,&camera,&in,ecran,&level,&butn,&ps,&butn1,&coin,&texte,&t);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    musique = Mix_LoadMUS("stage2.mp3");
    Mix_PlayMusic(musique, -1);
    while (continuer!=0)
    {
        start=SDL_GetTicks();
        input(&continuer,&f,&s,&in,&manette,d);
        Deplacement_Perso(&per,&f,&s,&camera,level,&level_height);
        scrolling(&per,&camera,&level_height);
        animation(&per,&cpt_perso);
        affichage_background(&level,ecran,camera);
        afficher_collected_coins(&texte,&coin,ecran);
        SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
        blit_coins(&coin,&camera,ecran);
        collect_coins(&coin,&per);
        check_win(&t,&coin,&continuer,&per);
        check_changement_stage2(&per,&t,&coin);
        if (f==11)
        {
        ps.pause=1;

        }
        pause_menu(&ps,ecran,&continuer,&cnt3,level,camera,&manette);
        if (f!=0 || chrono==1)
        {
            timer(&t,ecran,chrono);
            chrono=1;
        }
        SDL_Flip(ecran);
        fprintf(stderr,"%d\n",per.position.x);
        if ((per.position.x>9900)&&(coin.collected==18))
        {
            return 3;
            continuer=0;
        }
        if (1000/FPS>SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));

    }
    Mix_FreeMusic(musique);
    SDL_FreeSurface(ecran);
    SDL_Quit();

}
void check_changement_stage2(perso *dante,time *t,coins *cn)
{
    //printf("r=%d\ng=%d\nb=%d\n",dante->couleur[0].r,dante->couleur[0].g,dante->couleur[0].b);
    if ((dante->couleur[0].b==1&&dante->couleur[0].g==240&&dante->couleur[0].r==255)||(dante->couleur[2].b==0&&dante->couleur[2].g==240&&dante->couleur[2].r==255))
    {
         dante->position.x=500;
            dante->position.y=1000;
            t->temps=120000;
            init_coins(cn);
    }
}
void init_background2(background *level)
{
    int i=0;
    char im[50];
    level->back_col=NULL;
    for(i=0; i<25; i++)
    {
        sprintf(im,"images/stage2/stage55_00000.jpg");
        level->back[i]=IMG_Load(im);

    }
    level->back_col=IMG_Load("images/stage2/stage55_00000_col.jpg");
    (*level).anim=0;
    level->cpt=0;

}
void init_coins(coins *coin)
{
    int i;
    coin->nbr_coin=18;
    for(i=0;i< coin->nbr_coin;i++)
     coin->coin[i]=IMG_Load("Gold.png");
    coin->collected=0;
    coin->position[0].x=2571;
    coin->position[0].y=940;
    coin->position[1].x=4149;
    coin->position[1].y=940;
    coin->position[2].x=5379;
    coin->position[2].y=940;
    coin->position[3].x=1330;
    coin->position[3].y=940;

    coin->position[4].x=6441;
    coin->position[4].y=40;
    coin->position[5].x=6632;
    coin->position[5].y=234;
    coin->position[6].x=5417;
    coin->position[6].y=321;
    coin->position[7].x=4595;
    coin->position[7].y=321;
    coin->position[8].x=3708;
    coin->position[8].y=444;
    coin->position[9].x=2926;
    coin->position[9].y=288;
    coin->position[10].x=2631;
    coin->position[10].y=288;
    coin->position[11].x=2330;
    coin->position[11].y=288;
    coin->position[12].x=2147;
    coin->position[12].y=288;
    coin->position[13].x=1814;
    coin->position[13].y=288;
    coin->position[14].x=6420;
    coin->position[14].y=782;
    coin->position[15].x=6822;
    coin->position[15].y=1011;
    coin->position[16].x=7497;
    coin->position[16].y=716;
    coin->position[17].x=7992;
    coin->position[17].y=713;
}
void blit_coins(coins *coin,SDL_Rect *camera,SDL_Surface *ecran)
{
    int i;
    for(i=0;i<coin->nbr_coin;i++)
    {
        coin->position_affichage[i].x=(coin->position[i].x) - (camera->x);
        coin->position_affichage[i].y=(coin->position[i].y) - (camera->y);
        SDL_BlitSurface(coin->coin[i],NULL,ecran,&coin->position_affichage[i]);
    }
    SDL_Flip(ecran);
}
void collect_coins(coins *coin,perso *per)
{
    int i,j;
    for(i=0;i<coin->nbr_coin;i++)
    {
        if((per->position.x>=(coin->position[i].x)-10) && ((per->position.x)<=coin->position[i].x+coin->coin[i]->w) && (per->position.y +per->render->h >=coin->position[i].y ) && (per->position.y<=coin->position[i].y + coin->coin[i]->h))
        {
            coin->nbr_coin--;
            coin->collected++;
            for(j=i;j<coin->nbr_coin;j++)
            {
                coin->coin[j]=coin->coin[j+1];
                coin->position[j]=coin->position[j+1];
            }
        }
    }
            //fprintf(stderr,"%d\n",coin->collected);

}
void init_texte(Texte *texte)
{
    (texte->couleur).r=255;
    (texte->couleur).g=0;
    (texte->couleur).b=0;;//noir

    TTF_Init();
    texte->police = TTF_OpenFont("polices/Cardinal.ttf",40);      /* Chargement de la police*/
    (texte->position_txt).x=90;
    (texte->position_txt).y=30;
    (texte->position_icon).x=40;
    (texte->position_icon).y=30;
    texte->icon=IMG_Load("Gold.png");

}
void afficher_collected_coins(Texte *texte,coins *coin,SDL_Surface *ecran)
{
 sprintf((texte->text_a_afficher),"%d/18",(coin->collected));
 (texte->text_surface) = TTF_RenderText_Blended((texte->police), (texte->text_a_afficher) , (texte->couleur));
 SDL_BlitSurface( (texte->text_surface), NULL, ecran, &(texte->position_txt) );
 SDL_BlitSurface(texte->icon, NULL, ecran, &(texte->position_icon));
}
void init_timer(time *t)
{
    t->temps=120000;
    t->temps_actuel=SDL_GetTicks();
    t->temps_precedent=SDL_GetTicks();
    t->couleur.r=255;
    t->couleur.g=0;
    t->couleur.b=0;
    t->angle=0;
    t->pos_time.x=1150;
    t->pos_time.y=30;
    strcpy(t->policeH,"polices/Cardinal.ttf");
    t->police=TTF_OpenFont(t->policeH, 40);
    t->icon=IMG_Load("time.png");
    t->pos_icon.x=1100;
    t->pos_icon.y=30;
}
void timer (time *t,SDL_Surface *ecran,int chrono)
{
    char time[8];
    t->temps_actuel = SDL_GetTicks();
    if (chrono==0)
        t->temps_precedent=SDL_GetTicks();
    t->dt=((t->temps_actuel)-(t->temps_precedent));
    t->temps-=t->dt;
    //printf("%d\n",t->dt);
    //printf("%d\n",t->temps);
    t->temps_precedent=t->temps_actuel;
    if (t->temps<0)
        t->temps=0;
    t->min=t->temps/60000;
    t->sec=(t->temps%60000)/1000;
    if (t->sec<10)
        sprintf(time,"%d:0%d",t->min,t->sec);
    else
        sprintf(time,"%d:%d",t->min,t->sec);
    t->aff_time = TTF_RenderText_Blended(t->police,time,t->couleur);
    //t->aff_time = rotozoomSurface(t->aff_time,t->angle,1,0);
    //t->angle+=1;
    SDL_BlitSurface(t->aff_time,NULL,ecran,&t->pos_time);
    SDL_BlitSurface(t->icon,NULL,ecran,&t->pos_icon);
}
void check_win(time *t,coins *coin,int *continuer,perso *per)
{
    if  ((t->temps==0) && (coin->collected<9))
        {
            per->position.x=500;
            per->position.y=1000;
            t->temps=120000;
            init_coins(coin);
        }
}
void init_stage2(perso *per,SDL_Rect *camera,inpu *in,SDL_Surface *ecran,background *level,button *butn,pause *ps,button *butn1,coins *coin,Texte *texte,time *t)
{
    int i,j;
    char im[50];
    init_background2(level);
    init_input(in);
    init_perso(per);
    init_buttons(butn,butn1);
    init_pause_menu(ps);
    init_coins(coin);
    init_texte(texte);
    init_timer(t);
    per->position.x=500;
    per->position.y=1050;
    (*camera).x=4000;
    (*camera).y=0;
    (*camera).h=600;
    (*camera).w=1366;
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/////////////////////////////////////////////////
int stage1()
{
    int a,continuer=1,f=0,s=0,cpt_perso=0,cnt3=0,manette=0;
    int level_height=600;
    char d[3];
    SDL_Surface *ecran = NULL;
    SDL_Rect camera;
    background level;
    perso per;
    inpu in;
    button butn,butn1;
    tableau tab;
    pause ps;
    indices ind;
    doors door;
    mirror mirro;
    bucket buck;
    keys key;
    plant pl;
    lumiere lum;
    locks lo;
    const int FPS=60;
    Uint32 start;
    Mix_Music *musique;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    init_stage1(&per,&camera,&in,ecran,&level,&butn,&tab,&ps,&ind,&door,&mirro,&buck,&key,&pl,&lum,&butn1,&lo);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    musique = Mix_LoadMUS("stage1.mp3");
    Mix_PlayMusic(musique, -1);
    while (continuer!=0)
    {
        start=SDL_GetTicks();
        input(&continuer,&f,&s,&in,&manette,d);
        a=arduinoWriteData(per.tentatives);
        collision_doors(&per,&door);
        Deplacement_Perso(&per,&f,&s,&camera,level,&level_height);
        scrolling(&per,&camera,&level_height);
        animation(&per,&cpt_perso);
        check_changement(&f,&per,&butn,&ps,&ind,&door,&buck,&pl,&key,&mirro,&lo);
        affichage_background(&level,ecran,camera);
        Affichage_objet(&ind,&camera,ecran,&per,&door,&ps,&mirro,&buck,&pl,&key,&lum,&lo);
        blit_button(&butn,ecran);
        animation_tableau(&per,&tab,&butn,ecran);
        pause_menu(&ps,ecran,&continuer,&cnt3,level,camera,&manette);
        rotation_mirroir(&mirro,&butn1,&level,ecran,&camera,&per,&lum,&door);
        bruler_porte(&lum,&door,ecran);
        lock(&per,ecran,level,camera,&lo);
        door.state[2]=lo.state;
        if (per.position.x>9900)
        {
            return 2;
            continuer=0;
        }
        SDL_Flip(ecran);
        if (1000/FPS>SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    SDL_FreeSurface(ecran);
    Mix_FreeMusic(musique);
    SDL_Quit();

}
void init_stage1(perso *per,SDL_Rect *camera,inpu *in,SDL_Surface *ecran,background *level,button *butn,tableau *tab,pause *ps,indices *ind,doors *door,mirror *mirro,bucket *buck,keys *key,plant *pl,lumiere *lum,button *butn1,locks *lo)
{
    init_background1(level);
    init_input(in);
    init_perso(per);
    init_portes(door,lo);
    init_mirroire(mirro,lum);
    init_buttons(butn,butn1);
    init_pause_menu(ps);
    init_bucket(buck);
    init_key(key);
    init_plant(pl);
    init_indices(ind);
    //per->position.x=500;
    //per->position.y=600;
    (*camera).x=4000;
    (*camera).y=0;
    (*camera).h=600;
    (*camera).w=1366;
    tab->cnt2=0; //compteur tableau animé
}
void init_input(inpu *in)
{
    (*in).up=0;
    (*in).down=0;
    (*in).left=0;
    (*in).right=0;
}
void init_background1(background *level)
{
    int i=0;
    char im[50];
    for(i=0; i<6; i++)
    {
        sprintf(im,"images/background/stage1 edit_%05d.jpg",i);
        level->back[i]=IMG_Load(im);
    }
    (*level).back_col=IMG_Load("stage1_col.jpg");
    (*level).anim=0;
    level->cpt=0;

}
void init_indices(indices *ind)
{
    int i=0;
    ind->taken[0]=0;
    ind->taken[1]=0;
    ind->taken[2]=0;
    ind->npaper=0;
    ind->papier=IMG_Load("components/war9a msakra.png");
    ind->positionindices[0].x=1920;
    ind->positionindices[0].y=520;
    ind->positionindices[1].x=8380;
    ind->positionindices[1].y=520;
    for (i=0; i<3; i++)
    {
        ind->pickedonce[i]=0;
    }
}
void init_plant(plant *pl)
{
    int i=0;
    char im[50];
    pl->state=0;
    pl->cnt=0;
    pl->n_plant=0;
    pl->water_fall=0;
    pl->position.x=1450;
    pl->position.y=400;
    for(i=0; i<=64; i++)
    {
        sprintf(im,"images/plant/plant_%05d.png",i);
        pl->plant[i]=IMG_Load(im);
    }
}
void init_key(keys *key)
{
    key->used=0;
    key->picked=0;
    key->key=IMG_Load("components/key.png");
    key->position.x=1550;
    key->position.y=450;
}
void init_bucket(bucket *buck)
{
    buck->buck=IMG_Load("components/stall.png");
    buck->n_bucket=0;
    buck->full=0;
    buck->position.x=1250;
    buck->position.y=500;
    buck->picked=0;
}
void init_pause_menu(pause *ps)
{
    int i=0;
    char im[50];
    ps->pause=0;
    ps->resume=0;
    ps->inv.image_inventaire=IMG_Load("components/inventory.png");
    ps->inv.image_object[0]=IMG_Load("components/war9a msakra.png");
    ps->inv.image_object[1]=IMG_Load("components/stall_inv.png");
    ps->inv.image_object[2]=IMG_Load("components/war9a ma7loula.png");
    ps->inv.image_object[3]=IMG_Load("components/war9a ma7loula2.png");
    ps->inv.image_object[4]=IMG_Load("components/key_inv.png");
    ps->inv.pickedobject=0;
    ps->inv.filledonce=0;
    ps->inv.position.x=650;
    ps->inv.position.y=100;
    ps->inv.position_objects[0].x=675;
    ps->inv.position_objects[0].y=210;
    ps->inv.position_objects[1].x=710;
    ps->inv.position_objects[1].y=210;
    ps->inv.position_objects[2].x=745;
    ps->inv.position_objects[2].y=210;
    ps->inv.position_objects[3].x=675;
    ps->inv.position_objects[3].y=250;
    ps->inv.selected=-1;
    ps->inv.use=0;
    for(i=0; i<=83; i++)
    {
        sprintf(im,"images/kteb/kteb_%05d.png",i);
        ps->kteb[i]=IMG_Load(im);
    }
    for (i=0; i<6; i++)
    {
        ps->inv.filled[i]=0;
    }
}
void init_buttons(button *butn,button *butn1)
{
    butn->cnt_blit=0;
    butn->n_tab=0;
    butn->position.x=1200;
    butn->position.y=500;
    butn->button[0]=IMG_Load("buttons/button.png");
    butn->button[1]=IMG_Load("buttons/buttonp.png");
    butn1->button[0]=IMG_Load("buttons/upb.png");
    butn1->button[1]=IMG_Load("buttons/downw.png");
    butn1->position.x=1200;
    butn1->position.y=500;
    butn1->cnt_blit=0;
}
void init_mirroire(mirror *mirro,lumiere *lum)
{
    lum->light=IMG_Load("images/dhaw.png");
    lum->position.x=5500;
    lum->position.y=-25;
    lum->ok=0;
    lum->reflection=0;
    mirro->rotated=NULL;
    mirro->det=0;
    mirro->ok=0;
    mirro->mir=IMG_Load("components/mirror.png");
    mirro->soc=IMG_Load("components/support.png");
    mirro->angle=1;
    mirro->position[0].x=5700;
    mirro->position[1].x=5700;
    mirro->position[0].y=400;
    mirro->position[1].y=345;
}
void init_portes(doors *door,locks *lo)
{
    int i=0;
    char im[50];
    lo->interacted=0;
    lo->state=0;
    door->position[0].x=3660;
    door->position[0].y=285;
    door->position[1].x=6356;
    door->position[1].y=200;
    door->position[2].x=9850;
    door->position[2].y=280;
    door->ndoor=0;
    door->burning_cnt=0;
    for (i=0; i<3; i++)
    {
        door->cnt[i]=0;
    }
    door->cnt_delay=0;
    for (i=0; i<3; i++)
    {
        door->state[i]=0;
    }
    for(i=0; i<=3; i++)
    {
        sprintf(im,"components/beb_%d.png",i+1);
        door->door_A[0][i]=IMG_Load(im);
    }
    for(i=0; i<=3; i++)
    {
        sprintf(im,"components/beb_nar_%d.png",i+1);
        door->door_A[1][i]=IMG_Load(im);
    }
    for(i=0; i<=1; i++)
    {
        sprintf(im,"components/final_door%d.png",i+1);
        door->door_A[2][i]=IMG_Load(im);
    }
}
void health_bar(health *hl,SDL_Surface *ecran,perso *per,SDL_Rect *camera)
{   int i=0;

    hl->position.y=per->position_affichage.y-30;
    hl->position.x=per->position_affichage.x-23;
    for (i=0;i<5;i++)
    {
    if (hl->vie==i)
    SDL_BlitSurface(hl->heal[i],NULL,ecran,&hl->position);
    }
    if(camera->x==0)
        hl->position.x=per->position_affichage.x-23;

       else if( camera->x == level_width - camera->w )
    {
        hl->position.x=per->position_affichage.x;
    }
    if (hl->vie<1)
    {
    per->position.x=300;
    per->position.y=600;
    hl->vie=4;
    }
}
void init_health_bar(health *hl)
{
    hl->vie=4;
    hl->heal[4]=IMG_Load("images/health0.png");
    hl->heal[3]=IMG_Load("images/health1.png");
    hl->heal[2]=IMG_Load("images/health2.png");
    hl->heal[1]=IMG_Load("images/health3.png");
    hl->heal[0]=IMG_Load("images/health4.png");

}
void init_perso(perso *per)
{
    int i=0;
    char im[50];
    (*per).position.x=500;
    //(*per).position_affichage.x=10;
    (*per).height=90;
    (*per).width=40;
    (*per).state=0;
    (*per).state0=1;
    (*per).anim=0;
    (*per).inventory=0;
    (*per).speed=5;
    per->interacted=0;
    (*per).position.y=500;
    (*per).render=IMG_Load("images/personage_idl_imin/1.png");
    strcpy((*per).name,"Dante");
    per->tentatives=3;
    for(i=0; i<6; i++)
    {
        sprintf(im,"images/perso_yimchi_imin/%d.png",i+1);
        (*per).walk_right[i]=IMG_Load(im);
    }

    for(i=0; i<6; i++)
    {
        sprintf(im,"images/perso_yimchi_isar/%d.png",i+1);
        (*per).walk_left[i]=IMG_Load(im);
    }
    for(i=0; i<6; i++)
    {
        sprintf(im,"images/personage_ynagiz_imin/%d.png",i+1);
        (*per).jump_right[i]=IMG_Load(im);
    }
    for(i=0; i<6; i++)
    {
        sprintf(im,"images/personage_ynagiz_isar/%d.png",i+1);
        (*per).jump_left[i]=IMG_Load(im);
    }
    for(i=0; i<3; i++)
    {
        sprintf(im,"images/personage_idl/%d.png",i+1);
        (*per).still[i]=IMG_Load(im);
    }
}
void input (int *continuer, int *f,int *s,inpu *in,int *manette,char d[3])
{
    int space=0,escape=0;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            (*continuer) = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                escape=1;
                break;
            case SDLK_RIGHT:
                (*in).right=1;
                break;
            case SDLK_LEFT:
                (*in).left=1;
                break;
            case SDLK_UP:
            {
                in->up=1;
            }
            break;
            /*case SDLK_DOWN:
            	(*in).down=1;
            break;*/
            case SDLK_SPACE:
                space=1;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                (*in).right=0;
                break;
            case SDLK_LEFT:
                (*in).left=0;
                break;
            case SDLK_UP:
                (*in).up=0;
                break;
            case SDLK_DOWN:
                (*in).down=0;
                break;
            default:
                break;
            }
            break;

        }
    }
    /*k=arduinoReadData(manette,d);
    fprintf(stderr,"%d\n",*manette);
    switch((*manette))
            {
            case 0:
                {
                in->right=0;
                in->left=0;
                in->up=0;
                //escape=0;
                enter=0;
                }
                break;
            case 1:
                in->right=1;
                break;
            case 2:
                in->left=1;
                break;
            case 3:
                in->up=1;
                break;
             case 5:
                in->up=1;
                in->right=1;
                break;
            case 6:
                in->up=1;
                in->left=1;
                break;
            case 9:
                //escape=1;
                break;
            case 8:
                enter=1;
                break;
            }
            */
    if ((*in).right)
    {
        if (((*in).up)&&((*s)==0))
        {
            (*s)=1;
            (*f)=5;
        }
        else if ((*in).down)
            (*f)=7;
        else
            (*f)=1;
    }
    else if ((*in).left)
    {
        if (((*in).up)&&((*s)==0))
        {
            (*s)=1;
            (*f)=6;
        }
        else if ((*in).down)
            (*f)=8;
        else
            (*f)=2;
    }
    else if (space)
        *f=10;
    else if (escape)
    {
        *f=11;
    }
    else if (((*in).up)&&((*s)==0))
    {
        (*f)=3;
        (*s)=1;
    }
    /*
    else if ((*in).down)
    {
    	if ((*in).left)
    		(*f)=8;
    	else if ((*in).right)
    		(*f)=7;
    	else
    		(*f)=4;
    }*/
    else
    {
        (*f)=0;
    }
    /*if (manette==1)
    {
        (*f)=1;
    }*/
    /*if ((space)&&((*s)==0))
    {
        (*s)=-16;
    }*/
    //fprintf(stderr,"f=%d\n",*f);

}
void affichage_background(background *level,SDL_Surface *ecran,SDL_Rect camera)
{
    level->cpt++;
    if (level->cpt==5)
    {
        level->cpt=0;
        level->anim++;
        if (level->anim>5)
            level->anim=0;
    }
    SDL_BlitSurface(level->back[level->anim],&camera,ecran,NULL);
}
void blit_button(button *butn,SDL_Surface *ecran)
{
    if (butn->show==1)
    {
        if (butn->cnt_blit<20)
            SDL_BlitSurface(butn->button[0],NULL,ecran,&butn->position);
        else
        {
            SDL_BlitSurface(butn->button[1],NULL,ecran,&butn->position);
        }
        butn->cnt_blit++;
        if (butn->cnt_blit==40)
            butn->cnt_blit=0;
    }
}
void check_changement(int *f,perso *dante,button *butn,pause *ps,indices *ind,doors *door,bucket *buck,plant *pl,keys *key,mirror *mirro,locks *lo)
{
    butn->show=0;
    if ((dante->couleur[0].b==0&&dante->couleur[0].g==210&&dante->couleur[0].r==0)||(dante->couleur[2].b==0&&dante->couleur[2].g==210&&dante->couleur[2].r==0))
    {
        butn->show=1;
        butn->n_tab=1;
    }
    else if ((dante->couleur[0].b==0&&dante->couleur[0].g==0&&dante->couleur[0].r==254)||(dante->couleur[2].b==0&&dante->couleur[2].g==0&&dante->couleur[2].r==254))
    {
        butn->show=1;
        butn->n_tab=2;
    }
    else butn->n_tab=0;
    if ((dante->couleur[0].b==130&&dante->couleur[0].g==0&&dante->couleur[0].r==0)||(dante->couleur[2].b==130&&dante->couleur[2].g==0&&dante->couleur[2].r==0))
    {
        if (ind->pickedonce[0]==0)
        {
            butn->show=1;
            ind->npaper=1;
        }
    }
    else if ((dante->couleur[0].b==0&&dante->couleur[0].g==129&&dante->couleur[0].r==0)||(dante->couleur[2].b==0&&dante->couleur[2].g==129&&dante->couleur[2].r==0))
    {
        if (ind->pickedonce[1]==0)
        {
            butn->show=1;
            ind->npaper=2;
        }
    }
    else ind->npaper=0;
    if ((dante->couleur[0].b==90&&dante->couleur[0].g==0&&dante->couleur[0].r==0)||(dante->couleur[2].b==90&&dante->couleur[2].g==0&&dante->couleur[2].r==0))
    {
        butn->show=1;
        door->ndoor=1;
    }
    else if ((dante->couleur[0].b==1&&dante->couleur[0].g==170&&dante->couleur[0].r==0)||(dante->couleur[2].b==1&&dante->couleur[2].g==170&&dante->couleur[2].r==0))
    {
        butn->show=1;
        door->ndoor=2;
    }
    else if ((dante->couleur[0].b==0&&dante->couleur[0].g==90&&dante->couleur[0].r==0)||(dante->couleur[2].b==0&&dante->couleur[2].g==90&&dante->couleur[2].r==0))
    {
        butn->show=1;
        door->ndoor=3;

    }
    else door->ndoor=0;
    //fprintf(stderr,"%d\n",door->state[2]);
    if ((dante->couleur[0].b==210&&dante->couleur[0].g==0&&dante->couleur[0].r==0)||(dante->couleur[2].b==210&&dante->couleur[2].g==0&&dante->couleur[2].r==0))
    {
        if (buck->picked==0)
        {
            butn->show=1;
            buck->n_bucket=1;
        }
    }
    else buck->n_bucket=0;
    if ((dante->couleur[0].b==170&&dante->couleur[0].g==0&&dante->couleur[0].r==0)||(dante->couleur[2].b==170&&dante->couleur[2].g==0&&dante->couleur[2].r==0))
    {
        butn->show=1;
        pl->n_plant=1;
    }
    else pl->n_plant=0;
    if ((dante->couleur[0].b==254&&dante->couleur[0].g==0&&dante->couleur[0].r==0)||(dante->couleur[2].b==254&&dante->couleur[2].g==0&&dante->couleur[2].r==0))
    {
        butn->show=1;
        pl->water_fall=1;
    }
    else pl->water_fall=0;
    if ((dante->couleur[0].b==170&&dante->couleur[0].g==0&&dante->couleur[0].r==0)||(dante->couleur[2].b==170&&dante->couleur[2].g==0&&dante->couleur[2].r==0))
    {
        // butn->show=1;
        if (pl->state==1)
        {
            //fprintf(stderr,"%d\n",key->n_key);
            if (key->picked==0)
            {
                key->n_key=1;
            }
        }
    }
    else key->n_key=0;
    if ((dante->couleur[0].b==1&&dante->couleur[0].g==255&&dante->couleur[0].r==0)||(dante->couleur[2].b==1&&dante->couleur[2].g==255&&dante->couleur[2].r==0))
    {
        butn->show=1;
        mirro->det=1;

    }
    else mirro->det=0;
    //fprintf(stderr,"blue=%d\n green=%d\n red=%d\n show=%d\n",dante->couleur[0].b,dante->couleur[0].g,dante->couleur[0].r,butn->show);

    if ((*f==10)&&(butn->show==1))
        dante->interacted=1;
    else dante->interacted=0;
    if ((*f)==10)
    {
        if (ps->inv.selected!=-1)
        {
            if (butn->show==0)
            {
                if (ps->inv.use==0)
                    ps->inv.use=1;
                else if (ps->inv.use==1)
                    ps->inv.use=0;
            }
            else if (butn->show==1)
            {
                if (pl->n_plant==1)
                {
                    if (ps->inv.use==0)
                        ps->inv.use=1;
                    else if (ps->inv.use==1)
                        ps->inv.use=0;
                }
                if (pl->water_fall==1)
                {
                    if (ps->inv.use==0)
                        ps->inv.use=1;
                    else if (ps->inv.use==1)
                        ps->inv.use=0;
                }
                if (door->ndoor==1)
                {
                    if (ps->inv.use==0)
                        ps->inv.use=1;
                    else if (ps->inv.use==1)
                        ps->inv.use=0;
                }
                if (key->n_key==1)
                {
                    if (ps->inv.use==0)
                        ps->inv.use=1;
                    else if (ps->inv.use==1)
                        ps->inv.use=0;
                }
            }
        }
    }
    if ((*f)==11)
    {
        ps->pause=1;

    }
}
void Deplacement_Perso (perso *per,int *l,int *s,SDL_Rect *camera,background level,int *level_height)
{
    //printf("x=%d\ny=%d\n",per->position.x,per->position.y);1500 480
    int f,a=0;
    perso per_0;
    per_0=(*per);
    (*per).state=0;
    f=(*l);
    if ((*s)!=0)
        (*per).speed=5;
    else
        (*per).speed=6;
    collision_back(per,level);
    if ((*s)==1)
    {
        if (per->jm!=1)
        {
            per->position_pre_jump.x=per->position.x;
            per->position_pre_jump.y=per->position.y;
            per->position_jump.x=-80;
            if (per->tomb==1)
                per->position_jump.x=0;
            per->position_jump.y=0;
            per->jm=1;
        }
        if ((per->position.y)>(detec_sol(((per->position.x) + (per->render->w/2)),level,level_height,per)-per->render->h))
        {
            (*s)=0;
            per->jm=0;
            per->position.y=detec_sol(((per->position.x) + (per->render->w/2)),level,level_height,per)-per->render->h;
            per->col_jm=0;
            per->tomb=0;
        }
        else if (per->tomb==1)
        {
            per->position_jump.x+=per->speed;
            (*per).position_jump.y=(-0.023*(per->position_jump.x*per->position_jump.x));
            per->position.y=per->position_pre_jump.y-per->position_jump.y;
        }
        else if ((per->c.droite_haut || per->c.gauche_haut)&&(per->col_jm==0))
        {
            per->position_jump.x=-per->position_jump.x;
            (*per).position_jump.y=(-0.023*(per->position_jump.x*per->position_jump.x))+150;
            per->position.y=per->position_pre_jump.y-per->position_jump.y;
            per->col_jm=1;
            per->position_jump.x+=per->speed;
        }
        else
        {
            per->position_jump.x+=per->speed;
            (*per).position_jump.y=(-0.023*(per->position_jump.x*per->position_jump.x))+150;
            per->position.y=per->position_pre_jump.y-per->position_jump.y;
        }
    }
    if (f==1)
    {
        if ((*per).position.x<(level_width-per->render->w))
        {
            (*per).position.x+=(*per).speed;
            (*per).state=1;
        }
    }
    else if (f==2)
    {
        if ((*per).position.x>-(per->render->w/2)+(per->width/2)+2)
        {
            (*per).position.x-=(*per).speed;
            (*per).state=2;
        }
    }
    else if (f==3)
    {
        per->state=5;
    }
    else if (f==5)
    {
        (*per).state=3;
    }
    else if (f==6)
    {
        (*per).state=4;
    }
    else
    {
        (*per).state=0;
    }
    if (per->c.gauche_haut && per->c.gauche_centre)
    {
        (*per).position.x=per_0.position.x;
        //(*per).position.x+=(*per).speed;
        (*per).state=0;
        if (f==1)
            (*per).position.x+=(*per).speed;
        //(*s)=0;
        //per->jumping=0;
    }
    else if (per->c.droite_haut && per->c.droite_centre)
    {
        (*per).position.x=per_0.position.x;
        //(*per).position.x-=(*per).speed;
        (*per).state=0;
        if (f==2)
            (*per).position.x-=(*per).speed;
        //(*s)=0;
        //per->jumping=0;
    }
    else if ((*s)==0)
    {
        if (((detec_sol(((per->position.x) + (per->render->w/2)),level,level_height,per))-per->render->h-(*per).position.y<20)&&(!per->c.droite_haut)&&(!per->c.gauche_haut))
        {
            (*per).position.y=detec_sol(((per->position.x) + (per->render->w/2)),level,level_height,per)-per->render->h;
        }
        else if (per->tomb==0)
        {
            per->jm=0;
            per->col_jm=0;
            per->tomb=1;
            (*s)=1;
        }
    }
    //printf("%d\n",(*s));

    if (per->col==5)
    {
        if ((*l)==1)
            (*per).position.x-=(*per).speed;
        (*per).state=0;
        //(*s)=0;
    }
    per->col=0;
}
void scrolling (perso *per, SDL_Rect *camera,int *level_height)
{
    camera->x=(per->position.x+(per->width/2))-(screen_width/2);
    camera->y=(per->position.y+(per->height/2))-(screen_height/2);
    if( camera->x < 0 )
    {
        camera->x = 0;
    }
    if( camera->y < 0 )
    {
        camera->y = 0;
    }
    if( camera->x > level_width - camera->w )
    {
        camera->x = level_width - camera->w;
    }
    if( camera->y > (*level_height) - camera->h )
    {
        camera->y = (*level_height) - camera->h;
    }
    per->position_affichage.x=per->position.x-camera->x;
    per->position_affichage.y=per->position.y-camera->y;
}
SDL_Color GetPixel (SDL_Surface* pSurface,int x,int y)
{
    SDL_Color color;
    Uint32 col= 0;
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy (&col,pPosition,pSurface->format->BytesPerPixel);
    SDL_GetRGB (col,pSurface->format,&color.r,&color.g,&color.b);
    return (color);
}
void collision_back(perso *dante,background a)
{

    SDL_Rect point[8];


    point[4].x=dante->position.x + dante->render->w/2 + dante->width/2; //HAUT DROIT
    point[4].y=dante->position.y + dante->render->h/4;

    point[0].x=dante->position.x + dante->render->w/2 + dante->width/2; //CENTRE DROIT
    point[0].y=dante->position.y + dante->render->h/2;

    point[5].x=dante->position.x + dante->render->w/2 + dante->width/2; //BAS DROIT
    point[5].y=dante->position.y + (dante->render->h*3)/4;

    point[1].x=dante->position.x + dante->render->w/2; //CENTRE BAS
    point[1].y=dante->position.y + dante->render->h;

    point[3].x=dante->position.x + dante->render->w/2; //CENTRE HAUT
    point[3].y=dante->position.y;

    point[6].x=dante->position.x + dante->render->w/2 - dante->width/2; //HAUT GAUCHE
    point[6].y=dante->position.y + dante->render->h/4;

    point[2].x=dante->position.x + dante->render->w/2 - dante->width/2; //CENTRE GAUCHE
    point[2].y=dante->position.y + dante->render->h/2;

    point[7].x=dante->position.x + dante->render->w/2 - dante->width/2; //BAS GAUCHE
    point[7].y=dante->position.y + (dante->render->h*3)/4;


    dante->couleur[0]=GetPixel (a.back_col, point[0].x, point[0].y);
    dante->couleur[1]=GetPixel (a.back_col, point[1].x, point[1].y);
    dante->couleur[2]=GetPixel (a.back_col, point[2].x, point[2].y);
    dante->couleur[3]=GetPixel (a.back_col, point[3].x, point[3].y);
    dante->couleur[4]=GetPixel (a.back_col, point[4].x, point[4].y);
    dante->couleur[5]=GetPixel (a.back_col, point[5].x, point[5].y);
    dante->couleur[6]=GetPixel (a.back_col, point[6].x, point[6].y);
    dante->couleur[7]=GetPixel (a.back_col, point[7].x, point[7].y);


    /*if (couleur[0].r!=255 || couleur[0].g!=255 || couleur[0].b!=255)
    return 10;

    else if (couleur[1].r==255 && couleur[1].g==255 && couleur[1].b==255)
    return 3;*/

    /*if ((dante->couleur[2].r==255 && dante->couleur[2].g==255 && dante->couleur[2].b==255)||(dante->couleur[6].r==255 && dante->couleur[6].g==255 && dante->couleur[6].b==255)||(dante->couleur[7].r==255 && dante->couleur[7].g==255 && dante->couleur[7].b==255))
        dante->col= 3;
    else if (dante->couleur[3].r==255 && dante->couleur[3].g==255 && dante->couleur[3].b==255)
        dante->col= 4;
    else if ((dante->couleur[4].r==255 && dante->couleur[4].g==255 && dante->couleur[4].b==255)||(dante->couleur[6].r==255 && dante->couleur[6].g==255 && dante->couleur[6].b==255))
        dante->col= 5;
    /*if ((couleur[6].r==255 && couleur[6].g==255 && couleur[6].b==255)||(couleur[4].r==255 && couleur[4].g==255 && couleur[4].b==255))
    return 5;
    else if ((dante->couleur[5].r==255 && dante->couleur[5].g==255 && dante->couleur[5].b==255)||(dante->couleur[7].r==255 && dante->couleur[7].g==255 && dante->couleur[7].b==255))
        dante->col= 2;
    else if ((dante->couleur[0].r==255 && dante->couleur[0].g==255 && dante->couleur[0].b==255)&&(dante->couleur[5].r==255 && dante->couleur[5].g==255 && dante->couleur[5].b==255))
        dante->col= 5;
    else if ((dante->couleur[0].r==255 && dante->couleur[0].g==255 && dante->couleur[0].b==255)&&(dante->couleur[4].r==255 && dante->couleur[4].g==255 && dante->couleur[4].b==255)&&(dante->couleur[5].r==255 && dante->couleur[5].g==255 && dante->couleur[5].b==255))
        dante->col= 1;*/
    //fprintf(stderr,"blue=%d\n green=%d\n red=%d\n",dante->couleur[5].b,dante->couleur[5].g,dante->couleur[5].r);
    if (dante->couleur[0].r==255 && dante->couleur[0].g==255 && dante->couleur[0].b==255)
        dante->c.droite_centre=1;
    else
        dante->c.droite_centre=0;
    if (dante->couleur[1].r==255 && dante->couleur[1].g==255 && dante->couleur[1].b==255)
        dante->c.bas=1;
    else
        dante->c.bas=0;
    if (dante->couleur[2].r==255 && dante->couleur[2].g==255 && dante->couleur[2].b==255)
        dante->c.gauche_centre=1;
    else
        dante->c.gauche_centre=0;
    if (dante->couleur[3].r==255 && dante->couleur[3].g==255 && dante->couleur[3].b==255)
        dante->c.haut=1;
    else
        dante->c.haut=0;
    if (dante->couleur[4].r==255 && dante->couleur[4].g==255 && dante->couleur[4].b==255)
        dante->c.droite_haut=1;
    else
        dante->c.droite_haut=0;
    if (dante->couleur[5].r==255 && dante->couleur[5].g==255 && dante->couleur[5].b==255)
        dante->c.droite_bas=1;
    else
        dante->c.droite_bas=0;
    if (dante->couleur[6].r==255 && dante->couleur[6].g==255 && dante->couleur[6].b==255)
        dante->c.gauche_haut=1;
    else
        dante->c.gauche_haut=0;
    if (dante->couleur[7].r==255 && dante->couleur[7].g==255 && dante->couleur[7].b==255)
        dante->c.gauche_bas=1;
    else
        dante->c.gauche_bas=0;

}
void collision_doors(perso *dante,doors *door)
{
    if ((dante->couleur[0].b==90&&dante->couleur[0].g==0&&dante->couleur[0].r==0)||(dante->couleur[2].b==90&&dante->couleur[2].g==0&&dante->couleur[2].r==0))
    {
        if (door->state[0]==0)
        {
            dante->col=5;
        }
    }
    else if ((dante->couleur[0].b==1&&dante->couleur[0].g==170&&dante->couleur[0].r==0)||(dante->couleur[2].b==1&&dante->couleur[2].g==170&&dante->couleur[2].r==0))
    {
        if (door->state[1]==0)
            dante->col=5;
    }
    else if ((dante->couleur[0].b==0&&dante->couleur[0].g==90&&dante->couleur[0].r==0)||(dante->couleur[2].b==0&&dante->couleur[2].g==90&&dante->couleur[2].r==0))
    {
        if (door->state[2]==0)
            dante->col=5;
    }
}
void animation(perso *per,int *cpt_perso)
{
    //fprintf(stderr,"%d",per->anim);
    (*cpt_perso)++;
    if ((*per).state!=(*per).state0)
    {
        (*per).anim=0;
    }
    if ((*per).state==1)
    {
        (*per).state0=(*per).state;
        (*per).render=(*per).walk_right[(*per).anim];
        if (*cpt_perso>5)
        {
            *cpt_perso=0;
            (*per).anim++;
        }
    }
    else if ((*per).state==2)
    {
        (*per).state0=(*per).state;
        (*per).render=(*per).walk_left[(*per).anim];
        if (*cpt_perso>5)
        {
            *cpt_perso=0;
            (*per).anim++;
        }
    }
    if (per->state==3)
    {
        per->jumping=1;
    }
    if (per->state==4)
    {
        per->jumping=2;
    }
    if (per->state==5)
    {
        per->jumping=3;
    }
    if ((*per).jumping==2)
    {
        (*per).state0=(*per).state;
        (*per).render=(*per).jump_left[(*per).anim];
        if (*cpt_perso>5)
        {
            *cpt_perso=0;
            (*per).anim++;
        }
        if ((*per).anim==5)
        {
            per->state0=2;
            per->jumping=0;
        }
    }
    else if ((*per).jumping==1)
    {
        (*per).state0=(*per).state;
        (*per).render=(*per).jump_right[(*per).anim];
        if (*cpt_perso>4)
        {
            *cpt_perso=0;
            (*per).anim++;
        }
        if ((*per).anim==5)
        {
            per->state0=1;
            per->jumping=0;
        }
    }
    else if (((*per).jumping==3)||(per->jumping==4))
    {
        if (per->state0==1)
        {
            (*per).render=(*per).jump_right[(*per).anim];
            per->jumping=3;
        }
        if (per->state0==2)
        {
            (*per).render=(*per).jump_left[(*per).anim];
            per->jumping=4;
        }
        (*per).state0=(*per).state;
        if (*cpt_perso>4)
        {
            *cpt_perso=0;
            (*per).anim++;
        }
        if ((*per).anim==5)
        {
            if (per->jumping==3)
                per->state0=1;
            if (per->jumping==4)
                per->state0=2;
            per->jumping=0;
        }
    }
    else if ((*per).state==0)
    {
        (*per).anim=0;
        if ((*per).state0==1)
            (*per).render=IMG_Load("images/personage_idl_imin/1.png");
        if ((*per).state0==2)
            (*per).render=IMG_Load("images/personage_idl_isar/1.png");
    }
    if ((*per).anim==5)
    {
        (*per).anim=0;
    }
}
int detec_sol (int x,background a,int *level_height,perso *per)
{
    int i,y;
    SDL_Color couleur;
    i=per->position.y+per->render->h-5; //(*level_height)-10 //per->position.y+100
    y=0;
    while ((i<(*level_height))&&(y==0))
    {
        couleur=GetPixel (a.back_col, x, i);
    //fprintf(stderr,"couleur.r=%d\ncouleur.b=%d\ncouleur.g=%d\n",couleur.r,couleur.b,couleur.g);
        if (couleur.r>=252 && couleur.g>=252 && couleur.b>=252)
        {
            y=i;
        }
        i++;
    }
    if (y==0)
        y=400;
        //fprintf(stderr,"i=%d\n",i);
    return y;
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
void animation_tableau(perso *per,tableau *tab,button *butn,SDL_Surface *ecran)
{
    char im[50];
    if ((per->interacted==1)&&(butn->n_tab==1))
        tab->play=1;
    if ((per->interacted==1)&&(butn->n_tab==2))
        tab->play=2;
    if (tab->play==1)
    {
        sprintf(im,"images/animation tableau/tableau_%05d.jpg",tab->cnt2);
        tab->tableau[tab->cnt2]=IMG_Load(im);
        SDL_BlitSurface(tab->tableau[tab->cnt2],NULL,ecran,NULL);
        SDL_FreeSurface(tab->tableau[tab->cnt2]);
        tab->cnt2++;
    }
    else if (tab->play==2)
    {
        sprintf(im,"images/animation tableau1/tableau_%05d.jpg",tab->cnt2);
        tab->tableau[tab->cnt2]=IMG_Load(im);
        SDL_BlitSurface(tab->tableau[tab->cnt2],NULL,ecran,NULL);
        SDL_FreeSurface(tab->tableau[tab->cnt2]);
        tab->cnt2++;
    }

    if ((tab->cnt2)==200)
    {
        per->interacted=0;
        tab->cnt2=0;
        butn->n_tab=0;
        tab->play=0;
    }
}
void pause_menu(pause *ps,SDL_Surface *ecran,int *continuer,int *compteur,background level,SDL_Rect camera,int *manette)
{
    if (ps->pause==1)
    {
        SDL_Rect positionCarre;
        SDL_Surface *carre=NULL;
        positionCarre.x=800;
        positionCarre.y=500;
        SDL_Event event;
        Uint32 start;
        const int FPS=30;
        int curseur=1;
        int ok=0,i=0,mouse_x=0,mouse_y=0,mouse=1,selec;
        SDL_Color couleurMenu = {0, 0, 0},couleurMenu_selected = {255, 0, 0};
        TTF_Font *police;
        SDL_Surface *texte[5],*texte_selected[5];
        char policeH[]="polices/Cardinal.ttf";
        int tailleHelp=50;
        SDL_Rect positionMenu[5];
        positionMenu[0].x=320;
        positionMenu[0].y=150;
        police = TTF_OpenFont(policeH, tailleHelp);
        texte[0] = TTF_RenderText_Blended(police, "New game ", couleurMenu);
        texte[1] = TTF_RenderText_Blended(police, "Load game ", couleurMenu);
        texte[2] = TTF_RenderText_Blended(police, "Settings ", couleurMenu);
        texte[3] = TTF_RenderText_Blended(police, "Exit ", couleurMenu);
        texte_selected[0] = TTF_RenderText_Blended(police, "New game ", couleurMenu_selected);
        texte_selected[1] = TTF_RenderText_Blended(police, "Load game ", couleurMenu_selected);
        texte_selected[2] = TTF_RenderText_Blended(police, "Settings ", couleurMenu_selected);
        texte_selected[3] = TTF_RenderText_Blended(police, "Exit ", couleurMenu_selected);
        carre = SDL_CreateRGBSurface(SDL_SWSURFACE, 30, 35, 32, 0, 0, 0, 0);
        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        for (i=1; i<4; i++)
        {
            positionMenu[i].x=320;
            positionMenu[i].y=positionMenu[i-1].y+70;
        }
        while ((ps->pause==1)&&(*continuer==1))
        {
            if (curseur>4)
                curseur=1;
            if (curseur<1)
                curseur=4;
            //fprintf(stderr,"ok=%d\n curseur%d\n",ok,curseur);
            start=SDL_GetTicks();
            SDL_BlitSurface(level.back[level.anim],&camera,ecran,NULL);
            SDL_BlitSurface(ps->kteb[*compteur],NULL,ecran,NULL);
            if (*compteur>=81)
            {
                for (i=0; i<4; i++)
                {
                    if (curseur==(i+1))
                    {
                        SDL_BlitSurface(texte_selected[i], NULL, ecran, &positionMenu[i]);
                    }
                    else
                    {
                        SDL_BlitSurface(texte[i], NULL, ecran, &positionMenu[i]);
                    }
                }
                SDL_BlitSurface(ps->inv.image_inventaire, NULL, ecran, &ps->inv.position);
                for (i=0; i<6; i++)
                {
                    if(ps->inv.filled[i]==1)
                    {
                        if ((ps->inv.objects_type[i]==1)||(ps->inv.objects_type[i]==2))
                        {
                            if (ps->inv.selected==i)
                            {
                                positionCarre.x=ps->inv.position_objects[i].x+33;
                                positionCarre.y=ps->inv.position_objects[i].y+35;
                                SDL_BlitSurface(carre,NULL,ecran,&positionCarre);
                            }
                            SDL_BlitSurface(ps->inv.image_object[0],NULL,ecran,&ps->inv.position_objects[i]);
                        }
                        else if (ps->inv.objects_type[i]==3)
                        {
                            if (ps->inv.selected==i)
                            {
                                positionCarre.x=ps->inv.position_objects[i].x+33;
                                positionCarre.y=ps->inv.position_objects[i].y+35;
                                SDL_BlitSurface(carre,NULL,ecran,&positionCarre);
                            }
                            SDL_BlitSurface(ps->inv.image_object[1],NULL,ecran,&ps->inv.position_objects[i]);
                        }
                        else if (ps->inv.objects_type[i]==4)
                        {
                            if (ps->inv.selected==i)
                            {
                                positionCarre.x=ps->inv.position_objects[i].x+33;
                                positionCarre.y=ps->inv.position_objects[i].y+35;
                                SDL_BlitSurface(carre,NULL,ecran,&positionCarre);
                            }
                            SDL_BlitSurface(ps->inv.image_object[4],NULL,ecran,&ps->inv.position_objects[i]);
                        }
                    }
                }
            }
            SDL_Flip(ecran);
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_QUIT:
                    (*continuer) = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        ps->resume=1;
                        break;
                    case SDLK_UP:
                        curseur--;
                        break;
                    case SDLK_DOWN:
                        curseur++;
                        break;
                    case SDLK_SPACE:
                        ok=1;
                        break;
                        break;
                    default:
                        break;
                    }
                case SDL_MOUSEMOTION:
                    mouse=1;
                    mouse_x=event.motion.x;
                    mouse_y=event.motion.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        selec=1;
                    }
                    break;
                }
            }
            if (mouse==1)
            {
                if (selec==1)
                {
                    if ((mouse_x>705)&&(mouse_x<735)&&(mouse_y>245)&&(mouse_y<280))
                    {
                        if (ps->inv.filled[0]==1)
                            ps->inv.selected=0;
                    }
                    else if ((mouse_x>740)&&(mouse_x<770)&&(mouse_y>245)&&(mouse_y<280))
                    {
                        if (ps->inv.filled[1]==1)
                            ps->inv.selected=1;
                    }

                    else if ((mouse_x>775)&&(mouse_x<805)&&(mouse_y>245)&&(mouse_y<280))
                    {
                        if (ps->inv.filled[2]==1)
                            ps->inv.selected=2;
                    }
                    else if ((mouse_x>705)&&(mouse_x<735)&&(mouse_y>282)&&(mouse_y<315))
                    {
                        if (ps->inv.filled[3]==1)
                            ps->inv.selected=3;
                    }
                    else if ((mouse_x>740)&&(mouse_x<770)&&(mouse_y>282)&&(mouse_y<315))
                    {
                        if (ps->inv.filled[4]==1)
                            ps->inv.selected=4;
                    }
                    else if ((mouse_x>775)&&(mouse_x<805)&&(mouse_y>282)&&(mouse_y<315))
                    {
                        if (ps->inv.filled[5]==1)
                            ps->inv.selected=5;
                    }
                    else
                    {
                        //curseur=0;
                    }
                    mouse=0;
                    selec=0;
                }
            }
            //fprintf(stderr,"%d\n",ps->inv.selected);
            if ((curseur==4)&&(ok==1))
                *continuer=0;
            if ((ps->resume)==0)
            {
                (*compteur)++;
                if ((*compteur)>=83)
                {
                    (*compteur)=83;
                }
            }
            else if ((ps->resume)==1)
            {
                (*compteur)--;
                if ((*compteur)<=0)
                {
                    ps->pause=0;
                    ps->resume=0;
                }
            }
            ok=0;
            if (1000/FPS>SDL_GetTicks()-start)
                SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
        *compteur=0;
        (*manette)=0;
    }
}
void Affichage_objet(indices *ind,SDL_Rect *camera,SDL_Surface *ecran,perso *per,doors *door,pause *ps,mirror *mirro,bucket *buck,plant *pl,keys *key,lumiere *lum,locks *lo)
{
    int i=0;
    blit_door_in_both_states(door,per,camera,ecran,lo);
    blit_paper(ind,ps,ecran,camera,per);
    blit_bucket(buck,ps,ecran,camera,per);
    blit_plant(pl,camera,ecran);
    blit_key(key,camera,pl,per,ps,ecran);
    blit_mirroir(mirro,camera,ecran,per,lum);

    ////////////// 5abbi fil inventaire
    if (ps->inv.pickedobject!=0)
    {
        for(i=0; i<6; i++)
        {

            if (ps->inv.filledonce==0)
            {
                if (ps->inv.filled[i]==0)
                {
                    ps->inv.filled[i]=1;
                    ps->inv.filledonce=1;
                    ps->inv.objects_type[i]=ps->inv.pickedobject;
                    ps->inv.pickedobject=0;
                }
                //fprintf(stderr,"ps->inv.objects_type[%d]=%d\n",i,ps->inv.objects_type[i]);
            }
        }
    }
    /////////////////////////
    ps->inv.filledonce=0;
    //fprintf(stderr,"%d\n",ps->inv.selected);
    /*    UTILISATION DES OBJETS */
    if (ps->inv.selected!=-1)
    {
        watering_plant(ps,buck,pl);
        fill_bucket(ps,buck,pl);
        open_door_with_key(ps,door,key);            //using inventory items on objects
        read_paper(ps,per,ecran);

        /***************************************/
        //per->interacted=0;
    }
    SDL_BlitSurface(per->render,NULL,ecran,&per->position_affichage);
}
void watering_plant(pause *ps,bucket *buck,plant *pl)
{
    if (pl->state==0)
    {
        if (ps->inv.objects_type[(ps->inv.selected)]==3)
        {
            if (buck->full==1)
            {
                if (ps->inv.use==1)
                {
                    //fprintf(stderr,"%d\n",ps->inv.use);                   //yis9i nabta
                    if (pl->n_plant==1)
                    {
                        pl->state=1;
                        buck->full=0;
                    }
                }
            }
        }
    }
}
void fill_bucket(pause *ps,bucket *buck,plant *pl)
{
    if (pl->state==0)
    {
        if (ps->inv.objects_type[(ps->inv.selected)]==3)
        {
            if (buck->full==0)
            {
                if (ps->inv.use==1)
                {
                    if (pl->water_fall==1)   //replace here
                    {
                        //fprintf(stderr,"you have filled the bucket with water\n");  //FILL BUCKET
                        buck->full=1;
                    }
                }
            }
        }
    }
}
void open_door_with_key(pause *ps,doors *door,keys *key)
{
    if (door->state[0]==0)
    {
        if (ps->inv.objects_type[(ps->inv.selected)]==4)
        {
            if (key->used==0)
            {
                if (ps->inv.use==1)
                {
                    if (door->ndoor==1)   //opened door with key
                    {
                        //fprintf(stderr,"mouniiiiiir\n");
                        door->state[0]=1;
                        key->used=1;
                    }
                }
            }
        }
    }
}
void read_paper(pause *ps,perso *per,SDL_Surface *ecran)
{
    SDL_Rect position_papier_open;
    position_papier_open.x=400;
    position_papier_open.y=100;
    SDL_Event event;
    if ((ps->inv.objects_type[(ps->inv.selected)]==1)||(ps->inv.objects_type[(ps->inv.selected)]==2))
    {
        while (ps->inv.use==1)
        {
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                /*case SDL_QUIT:
                    (*continuer) = 0;
                    break;*/
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        ps->inv.use=0;
                        break;
                    default:
                        break;
                    }
                }
            }
            SDL_BlitSurface(per->render,NULL,ecran,&per->position_affichage);
            if (ps->inv.objects_type[(ps->inv.selected)]==1)
            {
                SDL_BlitSurface(ps->inv.image_object[2],NULL,ecran,&position_papier_open);
            }
            else if (ps->inv.objects_type[(ps->inv.selected)]==2)
            {
                SDL_BlitSurface(ps->inv.image_object[3],NULL,ecran,&position_papier_open);
            }
            SDL_Flip(ecran);
        }
    }
    else ps->inv.use=0;
}
void blit_door_in_both_states(doors *door,perso *per,SDL_Rect *camera,SDL_Surface *ecran,locks *lo)
{
    int i=0;
    for (i=0; i<3; i++)
    {
        door->position_affichage[i].x=(door->position[i].x)-(*camera).x;
        door->position_affichage[i].y=(door->position[i].y)-(*camera).y;
    }
    if (per->interacted==1)
    {
        if (door->ndoor==3)
        {
            lo->interacted=1;
        }
    }
    for (i=0; i<2; i++)
    {
        if (door->state[i]==0)
            SDL_BlitSurface(door->door_A[i][0],NULL,ecran,&door->position_affichage[i]);
        else if ((door->cnt[i]==3)&&(door->state[i]==1))
            SDL_BlitSurface(door->door_A[i][3],NULL,ecran,&door->position_affichage[i]);
        else if ((door->cnt[i]<3)&&(door->state[i]==1))
        {
            if (door->cnt[i]>3)
                door->cnt[i]=3;
            if (door->cnt_delay>10)
                door->cnt[i]++;
            if (door->cnt_delay==11)
                door->cnt_delay=0;
            SDL_BlitSurface(door->door_A[i][door->cnt[i]],NULL,ecran,&door->position_affichage[i]);
            door->cnt_delay++;
        }
    }
    if (door->state[2]==0)
        SDL_BlitSurface(door->door_A[2][0],NULL,ecran,&door->position_affichage[i]);
    else if (door->state[2]==1)
        SDL_BlitSurface(door->door_A[2][1],NULL,ecran,&door->position_affichage[i]);
}
void blit_paper(indices *ind,pause *ps,SDL_Surface *ecran,SDL_Rect *camera,perso *per)
{
    int i=0;
    for (i=0; i<2; i++)
    {
        ind->positiononscreen[i].x=(ind->positionindices[i].x)-(*camera).x;
        ind->positiononscreen[i].y=(ind->positionindices[i].y)-(*camera).y;
    }
    if (per->interacted==1)
    {
        if (ind->npaper==1)
        {
            ind->taken[0]=1;
            ps->inv.pickedobject=1;
            ind->pickedonce[0]=1;
        }
        else if (ind->npaper==2)
        {
            ind->taken[1]=1;
            ps->inv.pickedobject=2;
            ind->pickedonce[1]=1;
        }
        else ps->inv.pickedobject=0;
    }
    if (ind->taken[0]==0)
        SDL_BlitSurface(ind->papier,NULL,ecran,&ind->positiononscreen[0]);
    if (ind->taken[1]==0)
        SDL_BlitSurface(ind->papier,NULL,ecran,&ind->positiononscreen[1]);
    if ((ind->taken[0]==1)||(ind->taken[1]==1))
    {
        if ((ps->inv.objects_type[(ps->inv.selected)]==1)||(ps->inv.objects_type[(ps->inv.selected)]==2))
        {
            ind->positiononscreen[0].x=1200;
            ind->positiononscreen[0].y=30;
            SDL_BlitSurface(ind->papier,NULL,ecran,&ind->positiononscreen[0]);
        }
    }
}
void blit_bucket(bucket *buck,pause *ps,SDL_Surface *ecran,SDL_Rect *camera,perso *per)
{
    buck->position_affichage.x=(buck->position.x)-(*camera).x;
    buck->position_affichage.y=(buck->position.y)-(*camera).y;
    if (per->interacted==1)
    {
        if (buck->n_bucket==1)
        {
            ps->inv.pickedobject=3;
            buck->picked=1;
        }
    }
    else ps->inv.pickedobject=0;
    if (buck->picked==0)
        SDL_BlitSurface(buck->buck,NULL,ecran,&buck->position_affichage);
    if (buck->picked==1)
    {
        if (ps->inv.objects_type[(ps->inv.selected)]==3)
        {
            buck->position_affichage.x=1200;
            buck->position_affichage.y=30;
            SDL_BlitSurface(buck->buck,NULL,ecran,&buck->position_affichage);
        }
    }
}
void blit_plant(plant *pl,SDL_Rect *camera,SDL_Surface *ecran)
{
    pl->position_affichage.x=(pl->position.x)-(*camera).x;
    pl->position_affichage.y=(pl->position.y)-(*camera).y;
    if (pl->state==1)
    {
        if (pl->cnt>63)
            pl->cnt=63;
        pl->cnt++;
        SDL_BlitSurface(pl->plant[pl->cnt],NULL,ecran,&pl->position_affichage);
        //fprintf(stderr,"%d\n",per->position.x);
    }
}
void blit_key(keys *key,SDL_Rect *camera,plant *pl,perso *per,pause *ps,SDL_Surface *ecran)
{
    key->position_affichage.x=(key->position.x)-(*camera).x;
    key->position_affichage.y=(key->position.y)-(*camera).y;
    if (per->interacted==1)
    {
        if (key->n_key==1)
        {
            ps->inv.pickedobject=4;
            key->picked=1;
        }
    }
    else ps->inv.pickedobject=0;
    if (pl->state==1)
    {
        if (pl->cnt==64)
        {
            if (key->picked==0)
            {
                SDL_BlitSurface(key->key,NULL,ecran,&key->position_affichage);
            }
        }
    }
    if (key->picked==1)
    {
        if (ps->inv.objects_type[(ps->inv.selected)]==4)
        {
            key->position_affichage.x=1200;
            key->position_affichage.y=30;
            SDL_BlitSurface(key->key,NULL,ecran,&key->position_affichage);
        }
    }
}
void blit_mirroir(mirror *mirro,SDL_Rect *camera,SDL_Surface *ecran,perso *per,lumiere *lum)
{
    int i=0;
    if(per->interacted==1)
    {

        if(mirro->det==1)
        {
            mirro->ok=1;
        }
        else
        {
            mirro->ok=0;
        }

    }
    for (i=0; i<2; i++)
    {
        mirro->position_affichage[i].x=(mirro->position[i].x)-(*camera).x;
        mirro->position_affichage[i].y=(mirro->position[i].y)-(*camera).y;
    }
    if(mirro->ok==2)
    {
        mirro->position_affichage[1].x=(mirro->position[1].x)-(*camera).x -mirro->rotated->w/2 +100;
        mirro->position_affichage[1].y=(mirro->position[1].y)-(*camera).y -mirro->rotated->h/2 +60;
        SDL_BlitSurface(mirro->soc,NULL,ecran,&mirro->position_affichage[0]);
        SDL_BlitSurface(mirro->rotated,NULL,ecran,&mirro->position_affichage[1]);
    }
    else if(mirro->ok==1)
    {
        SDL_BlitSurface(mirro->soc,NULL,ecran,&mirro->position_affichage[0]);
        SDL_BlitSurface(mirro->mir,NULL,ecran,&mirro->position_affichage[1]);
    }
    else if(mirro->ok==0)
    {
        SDL_BlitSurface(mirro->soc,NULL,ecran,&mirro->position_affichage[0]);
        SDL_BlitSurface(mirro->mir,NULL,ecran,&mirro->position_affichage[1]);
    }
    lum->position_affichage.x=(lum->position.x)-(*camera).x;
    lum->position_affichage.y=(lum->position.y)-(*camera).y;
    if(lum->ok==0)
    {
        SDL_BlitSurface(lum->light,NULL,ecran,&lum->position_affichage);
    }
    else if(lum->ok==1)
    {
        SDL_BlitSurface(lum->rotated,NULL,ecran,&lum->position_affichage);
    }

}
void rotation_mirroir(mirror *mirr,button *butn1,background *level,SDL_Surface *ecran,SDL_Rect *camera,perso *per,lumiere *lum,doors *door)
{
    int a=1;
    SDL_Event event;
    if(mirr->ok==1)
    {

        while(a)
        {

            SDL_PollEvent(&event);
            {
                switch(event.type)
                {
                case SDL_QUIT:
                    a=0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        mirr->angle+=0.5;
                        lum->reflection+=0.1;
                        break;
                    case SDLK_DOWN:
                        mirr->angle-=0.5;
                        lum->reflection-=0.1;
                        break;
                    case SDLK_ESCAPE:
                        a=0;
                        mirr->ok=2;
                        lum->ok=1;
                        break;
                    default: break;
                    }
                }
            }
            printf("reflection %.2f\n",lum->reflection);
            mirr->rotated=rotozoomSurface(mirr->mir, mirr->angle, 1, 2);
            lum->rotated=rotozoomSurface(lum->light,lum->reflection,1,2);
            mirr->position_affichage[1].x=(mirr->position[1].x)-(*camera).x -mirr->rotated->w/2 +100;
            mirr->position_affichage[1].y=(mirr->position[1].y)-(*camera).y -mirr->rotated->h/2 +60;
            lum->position_affichage.x=(lum->position.x)-(*camera).x ;
            lum->position_affichage.y=(lum->position.y)-(*camera).y ;
            affichage_background(level,ecran,*camera);
            SDL_BlitSurface(mirr->soc,NULL,ecran,&mirr->position_affichage[0]);
            SDL_BlitSurface(mirr->rotated,NULL,ecran,&mirr->position_affichage[1]);
            SDL_BlitSurface(lum->rotated,NULL,ecran,&lum->position_affichage);
            SDL_BlitSurface(per->render,NULL,ecran,&per->position_affichage);
            SDL_BlitSurface(door->door_A[1][0],NULL,ecran,&door->position_affichage[1]);
            if (butn1->cnt_blit<10)
            {
                SDL_BlitSurface(butn1->button[0],NULL,ecran,&butn1->position);
            }
            else
            {
                SDL_BlitSurface(butn1->button[1],NULL,ecran,&butn1->position);
            }
            butn1->cnt_blit++;
            if (butn1->cnt_blit==40)
                butn1->cnt_blit=0;
            SDL_Flip(ecran);
            SDL_FreeSurface(ecran);
        }



    }
}
void bruler_porte(lumiere *lum,doors *door,SDL_Surface *ecran)
{

    if((lum->reflection<(-2.20))&&(lum->reflection>-3))
    {
        door->state[1]=1;
    }

}
int lock (perso *per,SDL_Surface *ecran,background level,SDL_Rect camera,locks *lo)
{

    if (lo->interacted==1)
    {
        int i,curseur=0,enter=0,code[2]= {5,8},code1[2]= {11,11},cpt=0,b=0,f=0,a;
        char im[50];
        SDL_Event event;
        SDL_Color couleur= {0, 0, 0};
        lo->state=0;
        SDL_Rect pos_c[2];
        TTF_Font *police;
        SDL_Surface *c[10];
        char policeH[]="polices/Cardinal.ttf";
        const int FPS=60;
        Uint32 start;
        police = TTF_OpenFont(policeH, 30);
        c[0] = TTF_RenderText_Blended(police, "0", couleur);
        c[1] = TTF_RenderText_Blended(police, "1", couleur);
        c[2] = TTF_RenderText_Blended(police, "2", couleur);
        c[3] = TTF_RenderText_Blended(police, "3", couleur);
        c[4] = TTF_RenderText_Blended(police, "4", couleur);
        c[5] = TTF_RenderText_Blended(police, "5", couleur);
        c[6] = TTF_RenderText_Blended(police, "6", couleur);
        c[7] = TTF_RenderText_Blended(police, "7", couleur);
        c[8] = TTF_RenderText_Blended(police, "8", couleur);
        c[9] = TTF_RenderText_Blended(police, "9", couleur);
        pos_c[0].x=595;
        pos_c[0].y=235+30;
        pos_c[1].x=735;
        pos_c[1].y=235+30;
        for (i=0; i<3; i++)
        {
            sprintf(im,"components/kouba_%d.png",i);
            lo->l[i]=IMG_Load(im);
        }
        for (i=0; i<10; i++)
        {
            sprintf(im,"components/Keyboard_White_%d.png",i);
            lo->button[i][0]=IMG_Load(im);
            sprintf(im,"components/Keyboard_Black_%d.png",i);
            lo->button[i][1]=IMG_Load(im);
        }
        lo->position.x=480;
        lo->position.y=30;
        lo->position_button[0].x=480;
        lo->position_button[0].y=400;
        lo->position_mouse[0][0].x=lo->position_button[0].x;
        lo->position_mouse[0][1].x=lo->position_button[0].x+80;
        lo->position_mouse[0][0].y=lo->position_button[0].y;
        lo->position_mouse[0][1].y=lo->position_button[0].y+80;
        for (i=1; i<5; i++)
        {
            lo->position_button[i].x=lo->position_button[i-1].x+80;
            lo->position_button[i].y=400;
            lo->position_mouse[i][0].x=lo->position_button[i].x;
            lo->position_mouse[i][1].x=lo->position_button[i].x+80;
            lo->position_mouse[i][0].y=lo->position_button[i].y;
            lo->position_mouse[i][1].y=lo->position_button[i].y+80;
        }
        for (i=5; i<10; i++)
        {
            lo->position_button[i].x=lo->position_button[i-5].x;
            lo->position_button[i].y=480;
            lo->position_mouse[i][0].x=lo->position_button[i].x;
            lo->position_mouse[i][1].x=lo->position_button[i].x+80;
            lo->position_mouse[i][0].y=lo->position_button[i].y;
            lo->position_mouse[i][1].y=lo->position_button[i].y+80;
        }
        /*for (i=0;i<10;i++)
        {
            SDL_BlitSurface(lo.button[i][0],NULL,ecran,&lo.position_button[i]);
        }*/
        while ((lo->interacted==1)&&(per->tentatives>0))
        {
            //fprintf(stderr,"%d\n",lo->interacted);
            a=arduinoWriteData(per->tentatives);
            SDL_BlitSurface(level.back[level.anim],&camera,ecran,NULL);
            SDL_BlitSurface(per->render,NULL,ecran,&per->position_affichage);
            SDL_BlitSurface(lo->l[b],NULL,ecran,&lo->position);
            if (code1[0]!=11)
                SDL_BlitSurface(c[code1[0]],NULL,ecran,&pos_c[0]);
            if (code1[1]!=11)
                SDL_BlitSurface(c[code1[1]],NULL,ecran,&pos_c[1]);

            if (f!=0)
            {
                f++;
                if (f<20)
                {
                    if (f%2==1)
                    {
                        pos_c[0].x=593;
                        pos_c[1].x=733;
                        lo->position.x=478;
                    }
                    else
                    {
                        pos_c[0].x=597;
                        pos_c[1].x=737;
                        lo->position.x=482;
                    }
                    a=arduinoWriteData(per->tentatives+5);

                }
                else
                {
                    f=0;
                    code1[0]=11;
                    code1[1]=11;
                    per->tentatives--;
                    pos_c[0].x=595;
                    pos_c[1].x=735;
                    lo->position.x=480;
                    if (per->tentatives==0)
                    {
                        lo->interacted=0;
                    }
                }
            }
            else if (lo->state==0)
            {
                for (i=0; i<10; i++)
                {
                    if (curseur==i)
                        SDL_BlitSurface(lo->button[i][1],NULL,ecran,&lo->position_button[i]);
                    else
                        SDL_BlitSurface(lo->button[i][0],NULL,ecran,&lo->position_button[i]);
                }
            }
            else
            {
                cpt++;
                if (cpt==5)
                    b=1;
                if (cpt==10)
                    b=2;
                if (cpt==15)
                    lo->interacted=0;
            }
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        lo->interacted=0;
                        break;
                    default: break;
                    }
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if ((cpt==0)&&(f==0))
                            enter++;
                    }
                case SDL_MOUSEMOTION:
                    if ((event.motion.x>lo->position_mouse[0][0].x)&&(event.motion.x<lo->position_mouse[0][1].x)&&(event.motion.y>lo->position_mouse[0][0].y)&&(event.motion.y<lo->position_mouse[0][1].y))
                    {
                        curseur=0;
                    }
                    else if ((event.motion.x>lo->position_mouse[1][0].x)&&(event.motion.x<lo->position_mouse[1][1].x)&&(event.motion.y>lo->position_mouse[1][0].y)&&(event.motion.y<lo->position_mouse[1][1].y))
                    {
                        curseur=1;
                    }
                    else if ((event.motion.x>lo->position_mouse[2][0].x)&&(event.motion.x<lo->position_mouse[2][1].x)&&(event.motion.y>lo->position_mouse[2][0].y)&&(event.motion.y<lo->position_mouse[2][1].y))
                    {
                        curseur=2;
                    }
                    else if ((event.motion.x>lo->position_mouse[3][0].x)&&(event.motion.x<lo->position_mouse[3][1].x)&&(event.motion.y>lo->position_mouse[3][0].y)&&(event.motion.y<lo->position_mouse[3][1].y))
                    {
                        curseur=3;
                    }
                    else if ((event.motion.x>lo->position_mouse[4][0].x)&&(event.motion.x<lo->position_mouse[4][1].x)&&(event.motion.y>lo->position_mouse[4][0].y)&&(event.motion.y<lo->position_mouse[4][1].y))
                    {
                        curseur=4;
                    }
                    else if ((event.motion.x>lo->position_mouse[5][0].x)&&(event.motion.x<lo->position_mouse[5][1].x)&&(event.motion.y>lo->position_mouse[5][0].y)&&(event.motion.y<lo->position_mouse[5][1].y))
                    {
                        curseur=5;
                    }
                    else if ((event.motion.x>lo->position_mouse[6][0].x)&&(event.motion.x<lo->position_mouse[6][1].x)&&(event.motion.y>lo->position_mouse[6][0].y)&&(event.motion.y<lo->position_mouse[6][1].y))
                    {
                        curseur=6;
                    }
                    else if ((event.motion.x>lo->position_mouse[7][0].x)&&(event.motion.x<lo->position_mouse[7][1].x)&&(event.motion.y>lo->position_mouse[7][0].y)&&(event.motion.y<lo->position_mouse[7][1].y))
                    {
                        curseur=7;
                    }
                    else if ((event.motion.x>lo->position_mouse[8][0].x)&&(event.motion.x<lo->position_mouse[8][1].x)&&(event.motion.y>lo->position_mouse[8][0].y)&&(event.motion.y<lo->position_mouse[8][1].y))
                    {
                        curseur=8;
                    }
                    else if ((event.motion.x>lo->position_mouse[9][0].x)&&(event.motion.x<lo->position_mouse[9][1].x)&&(event.motion.y>lo->position_mouse[9][0].y)&&(event.motion.y<lo->position_mouse[9][1].y))
                    {
                        curseur=9;
                    }
                    else
                    {
                        curseur=-1;
                    }
                    break;
                    default: break;
                }
            }
            if ((enter==1)&&(code1[0]==11))
            {
                for (i=0; i<10; i++)
                {
                    if (curseur==i)
                    {
                        code1[0]=curseur;
                    }
                }
                if (code1[0]==11)
                    enter=0;
            }
            if ((enter==2)&&(code1[1]==11))
            {
                for (i=0; i<10; i++)
                {
                    if (curseur==i)
                    {
                        code1[1]=curseur;
                    }
                }
                if (code1[1]==11)
                {
                    enter=1;
                }
            }
            if ((code1[0]!=11)&&(code1[1]!=11))
            {
                if ((code1[0]==code[0])&&(code1[1]==code[1])&&(cpt==0))
                {
                    lo->state=1;
                    cpt=1;
                    /*for (i=0;i<20;i++)
                    {
                        SDL_BlitSurface(lo.l[i/5],NULL,ecran,&lo.position);
                    }*/
                }
                else if ((cpt==0)&&(f==0))
                {

                    f=1;
                    enter=0;
                }
            }
            //printf("%d%d\n%d",code1[0],code1[1],f);
            if (1000/FPS>SDL_GetTicks()-start)
                SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
            SDL_Flip(ecran);
        }
        //fprintf(stderr,"%d\n",lo->state);
        return lo->state;

    }
}
int arduinoReadData(int *x,char s[3])
{

    //system("stty -F /dev/ttyACM0 9600 -parenb cs8 -cstopb");
    char chemin[]="/dev/ttyACM0";
    FILE* f;
    f=fopen(chemin,"r");

    if(f == NULL)
        return(-1);

    fscanf(f,"%s",s);
    //printf("arduino_input=%d\n",*x);
    (*x)=atoi(s);
    //printf("arduino_input=%d\n",*x);

    fclose(f);

    return(0);
}
int arduinoWriteData(int x)
{

    //system("stty -F /dev/ttyACM0 9600 -parenb cs8 -cstopb");
    char chemin[]="/dev/ttyACM0";
    FILE* f;
    f=fopen(chemin,"w");

    if(f == NULL)
        return(-1);

    //fprintf(f,"%d",x);
    //printf("arduino_input=%d\n",*x);
    //printf("arduino_input=%d\n",*x);

    fclose(f);

    return(0);
}

