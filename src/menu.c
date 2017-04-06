#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
void initialiser_intro(position *a,int nombre_images,const char chemin_w[],const char chemin_f[], SDL_Surface *ecran)
{
    int i;
    char Image_path[50];
    a->positionFond.x=0;
    a->positionFond.y=0;
    if (a->resolution_courante==1)
    {
        for (i=0; i<=nombre_images; i++)
        {
            sprintf(Image_path,"%s%05d.jpg",chemin_w,i);
            a->intro[i]=IMG_Load(Image_path);
        }
        ecran=SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    }
    else if (a->resolution_courante==2)
    {
        for (i=0; i<=nombre_images; i++)
        {
            sprintf(Image_path,"%s%05d.jpg",chemin_f,i);
            a->intro[i]=IMG_Load(Image_path);
        }
        ecran=SDL_SetVideoMode(1366,768,32,SDL_HWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
    }
}
void cinematique(position *a,int nombre_de_images,const char *song_name, SDL_Surface *ecran)
{
    const int FPS=28;
    Uint32 start;
    int i=0,fix=0,continuer=1;
    Mix_Music *musique;
    SDL_Event event;
    musique = Mix_LoadMUS(song_name);
    Mix_PlayMusic(musique, -1);
    while (continuer)
    {
        start=SDL_GetTicks();
        if (i==nombre_de_images)
        {
            continuer=0;
        }
        SDL_BlitSurface(a->intro[i],NULL,ecran,&a->positionFond);
        SDL_Flip(ecran);
        i++;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer=0;
                break;
            case SDL_KEYUP:
                fix=0;
                break;
            case SDL_KEYDOWN:
                if (!fix)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                    {
                        continuer=0;
                    }
                    break;
                    default:
                        break;
                    }
                }
                fix=1;
                break;
            }
        }
        if (1000/FPS>SDL_GetTicks()-start)
       SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    Mix_FreeMusic(musique);

    for (i=0; i<=nombre_de_images; i++)
    {
        SDL_FreeSurface(a->intro[i]);
    }
    SDL_FreeSurface(ecran);
}
int menu ()
{
	SDL_Surface *ecran = NULL;
    position pos;
    SDL_Event event,eventm;
    Mix_Music *musique;
    Mix_Chunk *ding;
    SDL_Color couleurHelp = {247, 199, 134};
    int curseur=1,continuer=1,m=0,i,fix=0,ac=1,j,cont=1,volm=0,volb=14,stage=0,enter=0,mouse=0,mouse_x,mouse_y;
    char policeHelp[]="polices/Cardinal.ttf",policeSetting[]="polices/TrueLies.ttf";
    char menu_a[40],butt[11];
    const int FPS=40;
	Uint32 start;
 	const SDL_VideoInfo* myPointer = SDL_GetVideoInfo();
 	if (pos.resolution_courante==1)
	    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	else
		ecran = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	sprintf(pos.nom_fichier,"config.txt");
	read_file(&pos);
	initialiser_intro(&pos,445,"images/intro/intro_","images/intro2/intro_",ecran);
    pos.resolution_antecedante=pos.resolution_courante;
    cinematique(&pos,445,"music/intt.mp3",ecran);
    initialiser_intro(&pos,445,"images/post_intro/p_intro","images/post_intro2/p_intro",ecran);
    cinematique(&pos,118,"music/intt.mp3",ecran);
	loading(&pos);
 	strcpy(pos.smenu,"images/menu2/menu_");
 
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    SDL_WM_SetCaption("Brave Wanderer", NULL);
    pos.police = TTF_OpenFont(policeHelp, pos.tailleHelp);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
    {
    	printf("%s", Mix_GetError());
    }
    if(TTF_Init() == -1)
	{
    	fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    	exit(EXIT_FAILURE);
	}
 	
    ding = Mix_LoadWAV("music/ding.wav");
    musique = Mix_LoadMUS("music/musique.mp3");
    Mix_PlayMusic(musique, 2);
    Mix_Volume(1,MIX_MAX_VOLUME-(volb*7));
    pos.positionFond.x=0;
    pos.positionFond.y=0;
    /*for (i=0; i<=108; i++)
    {
        sprintf(menu_a,"menu2/menu_%05d.jpg",i);
        Menu_anime[i]=IMG_Load(menu_a);
    }*/
    while (continuer!=0)
    {
    	start=SDL_GetTicks();
		if (curseur==0)
			{curseur=6;ac=6;}
		if (curseur>6)
			{curseur=1;ac=1;}
		if (i>152) i=0;
		if (pos.resolution_courante==1)
	    	{
	    		SDL_BlitSurface(pos.Menu_anime[i][0],NULL,ecran,&pos.positionFond);
	    	}
		else
			{
				SDL_BlitSurface(pos.Menu_anime[i][1],NULL,ecran,&pos.positionFond);
			}
	    i++;
	    pos.anim++;
    while (SDL_PollEvent(&event))
	{
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            /*case SDL_KEYUP:
                fix=0;*/
			break;
            case SDL_KEYDOWN:
				if(!fix)
				{
                	switch(event.key.keysym.sym)
                	{
                    case SDLK_UP: 
						curseur--;
                    break;
                    case SDLK_DOWN: 
						curseur++;
                    break;
		    		case SDLK_KP_ENTER:
						enter=1;
                    break;
		    		case SDLK_RETURN:
						enter=1;
                    break;
					//fix=1;
					}
                }
            break;
            case SDL_MOUSEMOTION:
            	mouse=1;
            	mouse_x=event.motion.x;
            	mouse_y=event.motion.y;
            break;
            case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					enter=1;
				}
            break;

        }
	}
	if (mouse==1)
	{
		if ((mouse_x>pos.positionMouse[0][0].x)&&(mouse_x<pos.positionMouse[0][1].x)&&(mouse_y>pos.positionMouse[0][0].y)&&(mouse_y<pos.positionMouse[0][1].y))
        {
    		curseur=1;
    	}
    	else if ((mouse_x>pos.positionMouse[1][0].x)&&(mouse_x<pos.positionMouse[1][1].x)&&(mouse_y>pos.positionMouse[1][0].y)&&(mouse_y<pos.positionMouse[1][1].y))
    	{
    		curseur=2;
    	}
    	else if ((mouse_x>pos.positionMouse[2][0].x)&&(mouse_x<pos.positionMouse[2][1].x)&&(mouse_y>pos.positionMouse[2][0].y)&&(mouse_y<pos.positionMouse[2][1].y))
    	{
    		curseur=3;
    	}
    	else if ((mouse_x>pos.positionMouse[3][0].x)&&(mouse_x<pos.positionMouse[3][1].x)&&(mouse_y>pos.positionMouse[3][0].y)&&(mouse_y<pos.positionMouse[3][1].y))
    	{
    		curseur=4;
    	}
        else if ((mouse_x>pos.positionMouse[4][0].x)&&(mouse_x<pos.positionMouse[4][1].x)&&(mouse_y>pos.positionMouse[4][0].y)&&(mouse_y<pos.positionMouse[4][1].y))
      	{
       		curseur=5;
    	}
    	else if ((mouse_x>pos.positionMouse[5][0].x)&&(mouse_x<pos.positionMouse[5][1].x)&&(mouse_y>pos.positionMouse[5][0].y)&&(mouse_y<pos.positionMouse[5][1].y))
    	{
    		curseur=6;
    	}
    	else
    	{
    		curseur=0;
    	}
    	mouse=0;
	}
	if (enter==1)
	{
		if (curseur==1)
		{
			stage=1;
			continuer=0;
		}
		if (curseur==4)
		{
			setting (&volm,&volb,&pos,ecran,ding,&i);
		}
		if (curseur==5)
		{
			Mix_PlayChannel(1, ding, 0);
			help(pos.tailleHelp,couleurHelp,&i,&pos,ecran);
			Mix_PlayChannel(1, ding, 0);
		}
		if (curseur==6)
		{
			Mix_PlayChannel(1, ding, 0);
			continuer = 0;
		}
		enter=0;
	}
	for (j=0;j<6;j++)
	{
		if ((j+1)==curseur)
		{
			SDL_BlitSurface(pos.buttonu[j], NULL, ecran, &pos.positionButtonu[j]);
		}
		else
		{
			SDL_BlitSurface(pos.button[j], NULL, ecran, &pos.positionButton[j]);
		}
	}
        SDL_Flip(ecran);
    if (ac!=curseur)
    {
    	Mix_PlayChannel(1, ding, 0);
    	ac = curseur;
    }
    if (1000/FPS>SDL_GetTicks()-start)
    	SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    pos.f=fopen("config.txt","w");
    if (pos.resolution_courante==1)
    {
        fprintf(pos.f,"mode1");
    }
    else  if (pos.resolution_courante==2)
    {
        fprintf(pos.f,"mode2");
    }
    Mix_FreeMusic(musique);
    Mix_FreeChunk(ding);
    Mix_CloseAudio();
    SDL_FreeSurface(ecran);
    TTF_Quit();
    SDL_Quit();
 
    return stage;

}
void setting (int *volm, int *volb, position *pos, SDL_Surface *ecran, Mix_Chunk *ding, int *p)
{
	int curseur=1,continuer=1,j,ac=1,i,enter=0;
	TTF_Font *police;
	SDL_Event eventm;
	SDL_Surface  *texteSetting[4], *texteSettingu[4], *volume[20];
	SDL_Color couleurSetting = {247, 199, 134};
	SDL_Color couleurSettingu = {228, 93, 13};
	SDL_Rect positionFond;
	char policeSetting[]="polices/TrueLies.ttf", menu_a[40];
	const int FPS=40;
	Uint32 start;

	positionFond.x = 0;
    positionFond.y = 0;
	TxtSetting (texteSetting,texteSettingu,pos);
	while (continuer)
	{
		if ((*p)>107) (*p)=0;    
		if (pos->resolution_courante==1)
	    	SDL_BlitSurface(pos->Menu_anime[(*p)][0],NULL,ecran,&pos->positionFond);
		else
			SDL_BlitSurface(pos->Menu_anime[(*p)][1],NULL,ecran,&pos->positionFond);
	    (*p)++;
		if (ac!=curseur)
		{
			Mix_PlayChannel(1, ding, 0);
			ac=curseur;
		}
		if (curseur==5) 
		{
			curseur=1;
			ac=1;
		}
		if (curseur==0) 
		{
			curseur=4;
			ac=4;
		}
		for (i=0;i<4;i++)
		{
			if (curseur==(i+1))
			{
				SDL_BlitSurface(texteSettingu[i], NULL, ecran, &(*pos).positionTexteSetting[i]);
			}
			else
			{
				SDL_BlitSurface(texteSetting[i], NULL, ecran, &(*pos).positionTexteSetting[i]);
			}
		}
   		if (((*volm)!=20)&&((*volm)!=0))
		{
			Mix_VolumeMusic(MIX_MAX_VOLUME-((*volm)*7));
		}
		else if ((*volm)==0)
		{
			Mix_VolumeMusic(MIX_MAX_VOLUME);
		}
		else
			Mix_VolumeMusic(0);
		for (j=20;j>(*volm);j--)
		{
			if ((*volm)!=20)
			{
				volume[j] = IMG_Load("buttons/vol1.png");
 				SDL_BlitSurface(volume[j], NULL, ecran, &(*pos).positionVolumeM[20-j]);
			}
			
   		}
		for (j=(*volm);j>0;j--)
		{
			volume[j] = IMG_Load("buttons/vol0.png");
			SDL_BlitSurface(volume[j], NULL, ecran, &(*pos).positionVolumeM[20-j]);
		}
		if (((*volb)!=20)&&((*volb)!=0))
		{
			Mix_Volume(1,MIX_MAX_VOLUME-((*volb)*7));
		}
		else if ((*volb)==0)
		{
			Mix_Volume(1,MIX_MAX_VOLUME);
		}
		else
			Mix_Volume(1,0);
		for (j=20;j>(*volb);j--)
		{
			if ((*volb)!=20)
			{
				volume[j] = IMG_Load("buttons/vol1.png");
 				SDL_BlitSurface(volume[j], NULL, ecran, &(*pos).positionVolumeB[20-j]);
			}
			
   		}
		for (j=(*volb);j>0;j--)
		{
			volume[j] = IMG_Load("buttons/vol0.png");
			SDL_BlitSurface(volume[j], NULL, ecran, &(*pos).positionVolumeB[20-j]);
		}
		SDL_Flip(ecran);
		while (SDL_PollEvent(&eventm))
		{
		switch(eventm.type)	
		{
			case SDL_KEYDOWN: 
				switch(eventm.key.keysym.sym)
				{
					case SDLK_UP:
						curseur--;
					break;
					case SDLK_DOWN:
						curseur++;
					break;
					case SDLK_ESCAPE:
						continuer=0;
					break;
					case SDLK_RIGHT:
						if (curseur==1)
						{
							if ((*volm)!=0)
							{
								(*volm)--;
							}
						}
						if (curseur==2)
						{
							if ((*volb)!=0)
							{
								(*volb)--;
								Mix_PlayChannel(1, ding, 0);
							}
						}
					break;
					case SDLK_LEFT:
						if (curseur==1)
						{
							if ((*volm)<20)
							{
								(*volm)++;
							}
						}
						if (curseur==2)
						{
							if ((*volb)<20)
							{
								(*volb)++;
								Mix_PlayChannel(1, ding, 0);
							}
						}
					break;
					case SDLK_RETURN:
						enter=1;
					break;
					case SDLK_KP_ENTER:
						enter=1;
					break;
				}
			break;
			case SDL_MOUSEBUTTONUP:
				if (eventm.button.button == SDL_BUTTON_LEFT)
				{
					enter=1;
				}
			break;
			case SDL_MOUSEMOTION:
            	if ((eventm.motion.x>(*pos).positionMouseSetting[0][0].x)&&(eventm.motion.x<(*pos).positionMouseSetting[0][1].x)&&(eventm.motion.y>(*pos).positionMouseSetting[0][0].y)&&(eventm.motion.y<(*pos).positionMouseSetting[0][1].y))
            	{
            		curseur=1;
            	}
            	if ((eventm.motion.x>(*pos).positionMouseSetting[1][0].x)&&(eventm.motion.x<(*pos).positionMouseSetting[1][1].x)&&(eventm.motion.y>(*pos).positionMouseSetting[1][0].y)&&(eventm.motion.y<(*pos).positionMouseSetting[1][1].y))
            	{
            		curseur=2;
            	}
            	if ((eventm.motion.x>(*pos).positionMouseSetting[2][0].x)&&(eventm.motion.x<(*pos).positionMouseSetting[2][1].x)&&(eventm.motion.y>(*pos).positionMouseSetting[2][0].y)&&(eventm.motion.y<(*pos).positionMouseSetting[2][1].y))
            	{
            		curseur=3;
            	}
            	if ((eventm.motion.x>(*pos).positionMouseSetting[3][0].x)&&(eventm.motion.x<(*pos).positionMouseSetting[3][1].x)&&(eventm.motion.y>(*pos).positionMouseSetting[3][0].y)&&(eventm.motion.y<(*pos).positionMouseSetting[3][1].y))
            	{
            		curseur=4;
            	}
            break;
   		}
	}
	if (enter==1)
	{
		if (curseur==1)
		{
			if (*volm!=20)
			{
				*volm=20;
				Mix_PlayChannel(1, ding, 0);
			}
			else if (*volm==20)
			{
				*volm=0;
				Mix_PlayChannel(1, ding, 0);
			}
		}
		if (curseur==2)
		{
			if (*volb!=20)
			{
				*volb=20;
				Mix_PlayChannel(1, ding, 0);
			}
			else if (*volb==20)
			{
				*volb=14;
				Mix_PlayChannel(1, ding, 0);
			}
			Mix_PlayChannel(1, ding, 0);
		}
		if (curseur==3)
		{
			if ((*pos).full==0)
			{
				Mix_PlayChannel(1, ding, 0);
				fullscreen(pos);
				SDL_FreeSurface(ecran);
				pos->resolution_courante=2;
				ecran = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
				TxtSetting (texteSetting,texteSettingu,pos);
			}
			else
			{
				Mix_PlayChannel(1, ding, 0);
				smallscreen(pos);
				pos->resolution_courante=1;
				SDL_FreeSurface(ecran);
				ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
				TxtSetting (texteSetting,texteSettingu,pos);
			}
		}
		if (curseur==4)
		{
			Mix_PlayChannel(1, ding, 0);
			continuer=0;
		}
		enter=0;
		if (1000/FPS>SDL_GetTicks()-start)
    	SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	}
}
void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
	    case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
			continuer = 0;
                        break;
                }
                break;
        }
    }
}
void fullscreen(position *pos)
{
	int i,j;
	strcpy((*pos).smenu,"images/menu3/menu_");
	for (i=0;i<6;i++)
	{
    	(*pos).positionButton[i].x += 100;
    	(*pos).positionButton[i].y += 80;
    	(*pos).positionButtonu[i].x += 100;
    	(*pos).positionButtonu[i].y += 80;
    	for (j=0;j<2;j++)
    	{
    		(*pos).positionMouse[i][j].x += 100;
    		(*pos).positionMouse[i][j].y += 80;
    	}
	}
	for (i=0;i<20;i++)
    {
    	(*pos).positionVolumeM[i].y = 255;
    	(*pos).positionVolumeM[i].x = 490+(i*6);
    	(*pos).positionVolumeB[i].y = 355;
    	(*pos).positionVolumeB[i].x = 490+(i*6);
    }
    for (i=0;i<9;i++)
    {
    	(*pos).positionHelp[i].x = 30;
    	(*pos).positionHelp[i].y = 170 + (i*60);
    }
    (*pos).positionTexteSetting[0].x=30;
    (*pos).positionTexteSetting[0].y=250;
    (*pos).positionTexteSetting[1].x=30;
    (*pos).positionTexteSetting[1].y=310+39;
    (*pos).positionTexteSetting[2].x=20;
    (*pos).positionTexteSetting[2].y=409+39;
    (*pos).positionTexteSetting[3].x=20;
    (*pos).positionTexteSetting[3].y=508+39;


    (*pos).positionMouseSetting[0][0].x = (*pos).positionTexteSetting[0].x;
    (*pos).positionMouseSetting[0][0].y = (*pos).positionTexteSetting[0].y;
    (*pos).positionMouseSetting[0][1].x = 400;
    (*pos).positionMouseSetting[0][1].y = 305;
    (*pos).positionMouseSetting[1][0].x = (*pos).positionTexteSetting[1].x;
    (*pos).positionMouseSetting[1][0].y = (*pos).positionTexteSetting[1].y;
    (*pos).positionMouseSetting[1][1].x = 435;
    (*pos).positionMouseSetting[1][1].y = 400;
    (*pos).positionMouseSetting[2][0].x = (*pos).positionTexteSetting[2].x;
    (*pos).positionMouseSetting[2][0].y = (*pos).positionTexteSetting[2].y;
    (*pos).positionMouseSetting[2][1].x = 315;
    (*pos).positionMouseSetting[2][1].y = 505;
    (*pos).positionMouseSetting[3][0].x = (*pos).positionTexteSetting[3].x;
    (*pos).positionMouseSetting[3][0].y = (*pos).positionTexteSetting[3].y;
    (*pos).positionMouseSetting[3][1].x = 210;
    (*pos).positionMouseSetting[3][1].y = 605;

    (*pos).tailleHelp=60;
    (*pos).tailleSetting=60;
    (*pos).full=1;
    (*pos).anim=0;
}
void smallscreen(position *pos)
{
	int i,j;
	strcpy((*pos).smenu,"images/menu2/menu_");
    (*pos).full=0;
    for (i=0;i<20;i++)
    {
    	(*pos).positionVolumeM[i].y = 225;
    	(*pos).positionVolumeM[i].x = 270+(i*6);
    	(*pos).positionVolumeB[i].y = 300;
    	(*pos).positionVolumeB[i].x = 270+(i*6);
    }
    for (i=0;i<9;i++)
    {
    	(*pos).positionHelp[i].x = 30;
    	(*pos).positionHelp[i].y = 150 + (i*39);
    }
    (*pos).positionTexteSetting[0].x=20;
    (*pos).positionTexteSetting[0].y=235;
    (*pos).positionTexteSetting[1].x=20;
    (*pos).positionTexteSetting[1].y=310;
    (*pos).positionTexteSetting[2].x=20;
    (*pos).positionTexteSetting[2].y=385;
    (*pos).positionTexteSetting[3].x=20;
    (*pos).positionTexteSetting[3].y=460;
    (*pos).tailleHelp=35;
    (*pos).tailleSetting=35;
    (*pos).positionFond.x = 0;
    (*pos).positionFond.y = 0;
    (*pos).positionButton[0].x = 130;
    (*pos).positionButton[0].y = 170;
    (*pos).positionButtonu[0].x = 115;
    (*pos).positionButtonu[0].y = 169;
    (*pos).positionButton[1].x = 127;
    (*pos).positionButton[1].y = 240;
    (*pos).positionButtonu[1].x = 112;
    (*pos).positionButtonu[1].y = 239;
    (*pos).positionButton[2].x = 45;
    (*pos).positionButton[2].y = 310;
    (*pos).positionButtonu[2].x = 30;
    (*pos).positionButtonu[2].y = 309;
    (*pos).positionButton[3].x = 72;
    (*pos).positionButton[3].y = 380;
    (*pos).positionButtonu[3].x = 57;
    (*pos).positionButtonu[3].y = 379;
    (*pos).positionButton[4].x = 122;
    (*pos).positionButton[4].y = 450;
    (*pos).positionButtonu[4].x = 107;
    (*pos).positionButtonu[4].y = 449;
    (*pos).positionButton[5].x = 115;
    (*pos).positionButton[5].y = 520;
    (*pos).positionButtonu[5].x = 100;
    (*pos).positionButtonu[5].y = 519;

    (*pos).positionMouse[0][0].x = 130;
    (*pos).positionMouse[0][0].y = 170;
    (*pos).positionMouse[0][1].x = 248;
    (*pos).positionMouse[0][1].y = 221;
    (*pos).positionMouse[1][0].x = 127;
    (*pos).positionMouse[1][0].y = 240;
    (*pos).positionMouse[1][1].x = 251;
    (*pos).positionMouse[1][1].y = 291;
    (*pos).positionMouse[2][0].x = 45;
    (*pos).positionMouse[2][0].y = 310;
    (*pos).positionMouse[2][1].x = 332;
    (*pos).positionMouse[2][1].y = 361;
    (*pos).positionMouse[3][0].x = 72;
    (*pos).positionMouse[3][0].y = 380;
    (*pos).positionMouse[3][1].x = 306;
    (*pos).positionMouse[3][1].y = 431;
    (*pos).positionMouse[4][0].x = 122;
    (*pos).positionMouse[4][0].y = 450;
    (*pos).positionMouse[4][1].x = 256;
    (*pos).positionMouse[4][1].y = 501;
    (*pos).positionMouse[5][0].x = 115;
    (*pos).positionMouse[5][0].y = 520;
    (*pos).positionMouse[5][1].x = 264;
    (*pos).positionMouse[5][1].y = 571;
    (*pos).anim=0;

    (*pos).positionMouseSetting[0][0].x = (*pos).positionTexteSetting[0].x;
    (*pos).positionMouseSetting[0][0].y = (*pos).positionTexteSetting[0].y;
    (*pos).positionMouseSetting[0][1].x = (*pos).positionTexteSetting[0].x+(*pos).positionTexteSetting[0].w;
    (*pos).positionMouseSetting[0][1].y = (*pos).positionTexteSetting[0].y+(*pos).positionTexteSetting[0].h;
    (*pos).positionMouseSetting[1][0].x = (*pos).positionTexteSetting[1].x;
    (*pos).positionMouseSetting[1][0].y = (*pos).positionTexteSetting[1].y;
    (*pos).positionMouseSetting[1][1].x = (*pos).positionTexteSetting[1].x+(*pos).positionTexteSetting[1].w;
    (*pos).positionMouseSetting[1][1].y = (*pos).positionTexteSetting[1].y+(*pos).positionTexteSetting[1].h;
    (*pos).positionMouseSetting[2][0].x = (*pos).positionTexteSetting[2].x;
    (*pos).positionMouseSetting[2][0].y = (*pos).positionTexteSetting[2].y;
    (*pos).positionMouseSetting[2][1].x = (*pos).positionTexteSetting[2].x+(*pos).positionTexteSetting[2].w;
    (*pos).positionMouseSetting[2][1].y = (*pos).positionTexteSetting[2].y+(*pos).positionTexteSetting[2].h;
    (*pos).positionMouseSetting[3][0].x = (*pos).positionTexteSetting[3].x;
    (*pos).positionMouseSetting[3][0].y = (*pos).positionTexteSetting[3].y;
    (*pos).positionMouseSetting[3][1].x = (*pos).positionTexteSetting[3].x+(*pos).positionTexteSetting[3].w;
    (*pos).positionMouseSetting[3][1].y = (*pos).positionTexteSetting[3].y+(*pos).positionTexteSetting[3].h;
}
void help(int tailleHelp, SDL_Color couleurHelp, int *p, position *pos, SDL_Surface *ecran)
{
	int continuer=1,j;
	SDL_Event event;
	TTF_Font *police;
	SDL_Surface *texte[9];
	char menu_a[40],policeH[]="polices/Cardinal.ttf";
    SDL_Rect positionFond;
    Uint32 start;
    const int FPS=40;

	police = TTF_OpenFont(policeH, tailleHelp);
	texte[0] = TTF_RenderText_Blended(police, "Brave Wanderer tells the story of a brave voyager, Dante, ", couleurHelp);
    texte[1] = TTF_RenderText_Blended(police, "a wanderer walking through the different stages of hell.", couleurHelp);
    texte[2] = TTF_RenderText_Blended(police, "In his eternal search for Beatrice, the Lady Eternal,", couleurHelp);
    texte[3] = TTF_RenderText_Blended(police, "Dante meets sinners suffering and paying for their sins,", couleurHelp);
    texte[4] = TTF_RenderText_Blended(police, "those whose trespasses were not forgiven, for they gave", couleurHelp);
    texte[5] = TTF_RenderText_Blended(police, "into temptation: tongues that lied, hands that shed innocent", couleurHelp);
    texte[6] = TTF_RenderText_Blended(police, "blood, feet that was swift in running to mischief, hearts", couleurHelp);
    texte[7] = TTF_RenderText_Blended(police, "that longed for wicked acts and false witnesses who spoke", couleurHelp);
    texte[8] = TTF_RenderText_Blended(police, "lies.", couleurHelp);
	positionFond.x = 0;
    positionFond.y = 0;
    while (continuer)
    {
    	if ((*p)>107) (*p)=0;
		if (pos->resolution_courante==1)
	    	SDL_BlitSurface(pos->Menu_anime[(*p)][0],NULL,ecran,&pos->positionFond);
		else
			SDL_BlitSurface(pos->Menu_anime[(*p)][1],NULL,ecran,&pos->positionFond);
	    (*p)++;
	    for (j=0;j<9;j++)
		{
			SDL_BlitSurface(texte[j], NULL, ecran, &(*pos).positionHelp[j]);
		}
		SDL_Flip(ecran);
    	while (SDL_PollEvent(&event))
    	{
    		switch(event.type)
	        {
		    	case SDL_KEYDOWN:
	                switch(event.key.keysym.sym)
	                {
	                    case SDLK_ESCAPE:
							continuer = 0;
	                    break;
	                }
	            break;
	        }
    	}
    	if (1000/FPS>SDL_GetTicks()-start)
    	SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }

}
void TxtSetting (SDL_Surface *texteSetting[], SDL_Surface *texteSettingu[], position *pos)
{
	SDL_Color couleurSetting = {247, 199, 134};
	SDL_Color couleurSettingu = {228, 93, 13};
	TTF_Font *police;
	char policeSetting[]="polices/TrueLies.ttf";
	police = TTF_OpenFont(policeSetting, (*pos).tailleSetting);
	texteSetting[0] = TTF_RenderText_Blended(police, "Music volume", couleurSetting);
	texteSetting[1] = TTF_RenderText_Blended(police, "Button volume", couleurSetting);
	texteSetting[3] = TTF_RenderText_Blended(police, "Return", couleurSetting);
	texteSettingu[0] = TTF_RenderText_Blended(police, "Music volume", couleurSettingu);
	texteSettingu[1] = TTF_RenderText_Blended(police, "Button volume", couleurSettingu);
	texteSettingu[3] = TTF_RenderText_Blended(police, "Return", couleurSettingu);
	if ((*pos).full==0)
	{
		texteSetting[2] = TTF_RenderText_Blended(police, "Full screen", couleurSetting);
		texteSettingu[2] = TTF_RenderText_Blended(police, "Full screen", couleurSettingu);
	}
	else
	{
		texteSetting[2] = TTF_RenderText_Blended(police, "Windowed", couleurSetting);
		texteSettingu[2] = TTF_RenderText_Blended(police, "Windowed", couleurSettingu);
	}
}
void loading(position *pos)
{
    const int FPS=60;
    Uint32 start;
    SDL_Thread *thread = NULL;
    thread = SDL_CreateThread( initialiser,(void*)pos);
    char path[50];
    int i,loaded=0;
    SDL_Surface  *Menu_anime[250],*ecran=NULL;
   
 	if (pos->resolution_courante==1)
	    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	else
		ecran = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    if (pos->resolution_courante==1)
    {for (i=0; i<210; i++)
        {
            sprintf(path,"images/loading_f/loading animation_%05d.jpg",i);
            Menu_anime[i]=IMG_Load(path);
        }}
    else if (pos->resolution_courante==2)
    {for (i=0; i<210; i++)
        {
            sprintf(path,"images/loading_f2/loading animation_%05d.jpg",i);
            Menu_anime[i]=IMG_Load(path);
        }}
    i=0;
    while(loaded!=1)
    {
        start=SDL_GetTicks();
        if (i>209)
        {
            i=0;
            loaded++;
        }
        SDL_BlitSurface(Menu_anime[i],NULL,ecran,NULL);
        SDL_Flip(ecran);
        i++;
        if (1000/FPS>SDL_GetTicks()-start)
        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    SDL_WaitThread(thread,NULL);
    SDL_FreeSurface(ecran);
}
int initialiser(void *ptr)
{
    position *a = (position*)ptr;
    int i;
    char aa[50];
    smallscreen(a);
    if (a->resolution_courante==2)
    {
        fullscreen(a);
    }
    for (i=0; i<=152; i++)
    {
        sprintf(aa,"images/menu2/menu_%05d.jpg",i);
        a->Menu_anime[i][0]=IMG_Load(aa);
    }
    for (i=0; i<=152; i++)
    {
        sprintf(aa,"images/menu3/menu_%05d.jpg",i);
        a->Menu_anime[i][1]=IMG_Load(aa);
    }
    for (i=0; i<=5; i++)
    {
        sprintf(aa,"buttons/button%d.png",i+1);
        a->button[i]=IMG_Load(aa);
        sprintf(aa,"buttons/button%du.png",i+1);
        a->buttonu[i]=IMG_Load(aa);
    }
    return 0;
}
void read_file(position *a)
{
    char mode[10];
    a->f=fopen(a->nom_fichier,"r");
    if (a->f!=NULL)
    {
        fscanf(a->f,"%s",mode);
    }
    if (strcmp(mode,"mode1")==0)
    {
        a->resolution_courante=1;
    }
    else if (strcmp(mode,"mode2")==0)
    {
        a->resolution_courante=2;
    }
    fclose(a->f);
}