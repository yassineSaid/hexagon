#include "stages.h"
#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_rotozoom.h>
void stage2()
{
    int continuer=1,f=0,s=0,cpt_perso=0,cnt3=0;
    SDL_Surface *ecran = NULL;
    SDL_Rect camera;
    background level;
    perso per;
    inpu in;
    button butn,butn1;
    pause ps;
    const int FPS=60;
    Uint32 start;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    init_stage2(&per,&camera,&in,ecran,&level,&butn,&ps,&butn1);
    while (continuer!=0)
    {
        start=SDL_GetTicks();
        input(&continuer,&f,&s,&in);
        Deplacement_Perso(&per,&f,&s,&camera,level);
        scrolling(&per,&camera);
        animation(&per,&cpt_perso);
        affichage_background(&level,ecran,camera);
        SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
        if (f==11)
        {
        ps.pause=1;

        }
        pause_menu(&ps,ecran,&continuer,&cnt3,level,camera);
        SDL_Flip(ecran);
        if (1000/FPS>SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    SDL_FreeSurface(ecran);
    SDL_Quit();

}
void init_background2(background *level)
{
    int i=0;
    char im[50];
    for(i=0; i<25; i++)
    {
        sprintf(im,"images/stage2/stage55_%05d.jpg",i);
        level->back[i]=IMG_Load(im);
    }
    (*level).back_col=IMG_Load("stage_collision2.jpg");
    (*level).anim=0;
    level->cpt=0;

}
void init_stage2(perso *per,SDL_Rect *camera,inpu *in,SDL_Surface *ecran,background *level,button *butn,pause *ps,button *butn1)
{
    int i,j;
    char im[50];
    init_background2(level);
    init_input(in);
    init_perso(per);
    init_buttons(butn,butn1);
    init_pause_menu(ps);
    (*camera).x=4000;
    (*camera).y=0;
    (*camera).h=600;
    (*camera).w=1366;
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/////////////////////////////////////////////////
void stage1()
{
    int continuer=1,f=0,s=0,cpt_perso=0,cnt3=0;
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
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    init_stage1(&per,&camera,&in,ecran,&level,&butn,&tab,&ps,&ind,&door,&mirro,&buck,&key,&pl,&lum,&butn1,&lo);
    while (continuer!=0)
    {
        start=SDL_GetTicks();
        input(&continuer,&f,&s,&in);
        collision_doors(&per,&door);
        Deplacement_Perso(&per,&f,&s,&camera,level);
        scrolling(&per,&camera);
        animation(&per,&cpt_perso);
        check_changement(&f,&per,&butn,&ps,&ind,&door,&buck,&pl,&key,&mirro,&lo);
        affichage_background(&level,ecran,camera);
        Affichage_objet(&ind,&camera,ecran,&per,&door,&ps,&mirro,&buck,&pl,&key,&lum,&lo);
        blit_button(&butn,ecran);
        animation_tableau(&per,&tab,&butn,ecran);
        pause_menu(&ps,ecran,&continuer,&cnt3,level,camera);
        rotation_mirroir(&mirro,&butn1,&level,ecran,&camera,&per,&lum,&door);
        bruler_porte(&lum,&door,ecran);
        lock(&per,ecran,level,camera,&lo);
        door.state[2]=lo.state;
        SDL_Flip(ecran);
        if (1000/FPS>SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    SDL_FreeSurface(ecran);
    SDL_Quit();

}
void init_stage1(perso *per,SDL_Rect *camera,inpu *in,SDL_Surface *ecran,background *level,button *butn,tableau *tab,pause *ps,indices *ind,doors *door,mirror *mirro,bucket *buck,keys *key,plant *pl,lumiere *lum,button *butn1,locks *lo)
{
    int i,j;
    char im[50];
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
    (*camera).x=4000;
    (*camera).y=0;
    (*camera).h=600;
    (*camera).w=1366;
    tab->cnt2=0; //compteur tableau animé
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
    door->position[2].x=9800;
    door->position[2].y=300;
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
    for(i=0; i<=3; i++)
        {
            sprintf(im,"components/beb_nar_%d.png",i+1);
            door->door_A[2][i]=IMG_Load(im);
        }
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
void input (int *continuer, int *f,int *s,inpu *in)
{
    int space=0,enter=0,escape=0;
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
            case SDLK_RETURN:
            {
                enter=1;
            }
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
    else if (enter)
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
     fprintf(stderr,"%d\n",door->state[2]);
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
void Deplacement_Perso (perso *per,int *l,int *s,SDL_Rect *camera,background level)
{
    //printf("x=%d\ny=%d\n",per->position.x,per->position.y);1500 480
    int col,f;
    perso per_0;
    per_0=(*per);
    (*per).state=0;
    f=(*l);
    if ((*s)!=0)
        (*per).speed=5;
    else
        (*per).speed=6;
    /*if ((*s)<=-1)
    {
        if ((*s)<=-3)
        {
            (*per).position.y+=(*s);
            (*s)+=1;
            if (collision_back(per,level)==4)
                (*s)=1;
        }
        else
            (*s)=1;
    }
    if ((*s)>=1)
    {
        if ((*per).position.y<detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),level)-(per->render->h-((per->render->h-per->height)/2)))
        {
            (*per).position.y+=(*s);
            (*s)++;
            if ((*per).position.y>detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),level)-(per->render->h-((per->render->h-per->height)/2)))
            {
                (*per).position.y=detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),level)-(per->render->h-((per->render->h-per->height)/2));
            }
        }
        else
        {
            (*s)=0;
            (*per).position.y=detec_sol(per->position.x + per->render->w-20,level);
        }
    }*/
    //fprintf(stderr,"%d\n",f);
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
        if (per->position.y>detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),level)-(per->render->h-((per->render->h-per->height)/2)))
        {
            (*s)=0;
            per->jm=0;
            per->position.y=detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),level)-(per->render->h-((per->render->h-per->height)/2));
            per->col_jm=0;
            per->tomb=0;
        }
        else if (per->tomb==1)
        {
            per->position_jump.x+=per->speed;
            (*per).position_jump.y=(-0.023*(per->position_jump.x*per->position_jump.x));
            per->position.y=per->position_pre_jump.y-per->position_jump.y;
        }
        else if ((per->col==4)&&(per->col_jm==0))
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
        //printf("%d     %d\n",(*per).position_jump.x,(*per).position_jump.y);
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
        /*if ((*per).position.y>0)
        {
            (*per).position.y-=(*per).speed;
        }*/
        per->state=5;
    }/*
    else if (f==4)
    {
        if ((*per).position.y<260)
        {
            (*per).position.y+=(*per).speed;
        }
    }*/
    else if (f==5)
    {
        /*if ((*per).position.x<(level_width-per->render->w-50))
        {
            (*per).position.x+=(*per).speed;
        }
        if ((*per).position.y>0)
        {
            (*per).position.y-=(*per).speed;
        }*/
        (*per).state=3;
    }
    else if (f==6)
    {
        /*if ((*per).position.x>(per->render->w/2)+(per->width/2)+2)
        {
            (*per).position.x-=(*per).speed;
        }
        if ((*per).position.y>0)
        {
            (*per).position.y-=(*per).speed;
        }*/
        (*per).state=4;
    }
    /*else if (f==7)
    {
        if ((*per).position.x<(level_width-per->render->w))
        {
            (*per).position.x+=(*per).speed;
        }
        if ((*per).position.y<260)
        {
            (*per).position.y+=(*per).speed;
        }
    }
    else if (f==8)
    {
        if ((*per).position.x>(per->render->w/2)+(per->width/2)+2)
        {
            (*per).position.x-=(*per).speed;
        }
        if ((*per).position.y<260)
        {
            (*per).position.y+=(*per).speed;
        }
    }*/
    else
    {
        (*per).state=0;
    }
    collision_back(per,level);
    if (per->col==1)
    {
        (*per)=per_0;
        (*per).state=0;
        (*s)=0;
    }
    else if (per->col==5)
    {
        if ((*l)==1)
            (*per).position.x-=(*per).speed;
        if ((*l)==2)
            (*per).position.x+=(*per).speed;
        (*per).state=0;
        //per->jumping=0;
    }
    else if ((*s)==0)
        if ((detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),level)-(per->render->h-((per->render->h-per->height)/2)))-(*per).position.y<20)
            (*per).position.y=(detec_sol(((per->position.x) + (per->render->w/2) + (per->width/2)),level)-(per->render->h-((per->render->h-per->height)/2)));
        else if (per->tomb==0)
        {
            per->jm=0;
            per->col_jm=0;
            per->tomb=1;
            (*s)=1;
        }
    per->col=0;
}
void scrolling (perso *per, SDL_Rect *camera)
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
    if( camera->y > level_height - camera->h )
    {
        camera->y = level_height - camera->h;
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
    int i=0;

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

    if ((dante->couleur[2].r==255 && dante->couleur[2].g==255 && dante->couleur[2].b==255)||(dante->couleur[6].r==255 && dante->couleur[6].g==255 && dante->couleur[6].b==255)||(dante->couleur[7].r==255 && dante->couleur[7].g==255 && dante->couleur[7].b==255))
        dante->col= 3;
    else if (dante->couleur[3].r==255 && dante->couleur[3].g==255 && dante->couleur[3].b==255)
        dante->col= 4;
    else if ((dante->couleur[4].r==255 && dante->couleur[4].g==255 && dante->couleur[4].b==255)||(dante->couleur[6].r==255 && dante->couleur[6].g==255 && dante->couleur[6].b==255))
        dante->col= 5;
    /*if ((couleur[6].r==255 && couleur[6].g==255 && couleur[6].b==255)||(couleur[4].r==255 && couleur[4].g==255 && couleur[4].b==255))
    return 5;*/
    else if (dante->couleur[5].r==255 && dante->couleur[5].g==255 && dante->couleur[5].b==255)
        dante->col= 2;
    else if ((dante->couleur[0].r==255 && dante->couleur[0].g==255 && dante->couleur[0].b==255)&&(dante->couleur[5].r==255 && dante->couleur[5].g==255 && dante->couleur[5].b==255))
        dante->col= 5;
    else if ((dante->couleur[0].r==255 && dante->couleur[0].g==255 && dante->couleur[0].b==255)&&(dante->couleur[4].r==255 && dante->couleur[4].g==255 && dante->couleur[4].b==255)&&(dante->couleur[5].r==255 && dante->couleur[5].g==255 && dante->couleur[5].b==255))
        dante->col= 1;
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
int detec_sol (int x,background a)
{
    int i,y;
    SDL_Color couleur;
    i=level_height-10;
    y=0;
    while ((i>0)&&(y==0))
    {
        couleur=GetPixel (a.back_col, x, i);
        if (couleur.r!=255 || couleur.g!=255 || couleur.b!=255)
        {
            y=i;
        }
        i--;
    }
    if (y==0)
        y=400;
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
void pause_menu(pause *ps,SDL_Surface *ecran,int *continuer,int *compteur,background level,SDL_Rect camera)
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
                    case SDLK_RETURN:
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
                    case SDLK_RETURN:
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
    for (i=0; i<3; i++)
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

        if (key->picked==0)
            {SDL_BlitSurface(key->key,NULL,ecran,&key->position_affichage);
             fprintf(stderr,"%d\n",pl->state);}
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
    int a=1,i;
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
    int i,curseur=0,enter=0,code[2]={5,8},code1[2]={11,11},cpt=0,b=0,f=0;
    char im[50];
    SDL_Event event;
    SDL_Color couleur={0, 0, 0};
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
    for (i=0;i<3;i++)
    {
        sprintf(im,"components/kouba_%d.png",i);
        lo->l[i]=IMG_Load(im);
    }
    for (i=0;i<10;i++)
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
    for (i=1;i<5;i++)
    {
        lo->position_button[i].x=lo->position_button[i-1].x+80;
        lo->position_button[i].y=400;
        lo->position_mouse[i][0].x=lo->position_button[i].x;
        lo->position_mouse[i][1].x=lo->position_button[i].x+80;
        lo->position_mouse[i][0].y=lo->position_button[i].y;
        lo->position_mouse[i][1].y=lo->position_button[i].y+80;
    }
    for (i=5;i<10;i++)
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
            for (i=0;i<10;i++)
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
            }
        }
        if ((enter==1)&&(code1[0]==11))
        {
            for (i=0;i<10;i++)
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
            for (i=0;i<10;i++)
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
    fprintf(stderr,"%d\n",lo->state);
    return lo->state;

    }
}
