#include "map.h"
#include "stages.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
int map1(int *levels)
{
	int continuer=1,f=0,m=0,s=0;
	SDL_Surface *ecran = NULL;
	SDL_Rect positionFond,camera;
	background level;
	perso per;
	inpu in;
	button butn;
	SDL_Init(SDL_INIT_VIDEO);
	ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	init1 (&per,&camera,&positionFond,&in,ecran,&level,&butn,*levels);
	SDL_BlitSurface(level.back_col,&camera,ecran,&positionFond);
	SDL_BlitSurface(level.back1,&camera,ecran,&positionFond);
	SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
	scrolling1(&per,&camera);
	SDL_Flip(ecran);
	while (continuer!=0)
    {
    	input1(&continuer,&f,&s,&in);
		m=Deplacement_Perso1(&per,&f,&s,&camera,level,&butn);
	    scrolling1(&per,&camera);
	    animation1(&per);
		SDL_BlitSurface(level.back1,&camera,ecran,&positionFond);
		SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
		blit_button(&butn,ecran);
		SDL_Flip(ecran);
		m=0;
	//fprintf(stderr,"%d",f);
	if ((f==10)&&(butn.n_tab==1))
	{
	return 1;
	}
    if ((f==10)&&(butn.n_tab==2))
	{
	return 2;
	}
	if ((f==10)&&(butn.n_tab==3))
	{
	return 3;
	}
    }
    SDL_FreeSurface(ecran);
    SDL_Quit();

}
void input1 (int *continuer, int *f,int *s,inpu *in)
{
	int space=0;
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
							(*continuer)=0;
						break;
		                case SDLK_RIGHT:
							(*in).right=1;
						break;
		                case SDLK_LEFT:
							(*in).left=1;
						break;
		                case SDLK_UP:
							(*in).up=1;
						break;
		                case SDLK_DOWN:
							(*in).down=1;
						break;
		                case SDLK_SPACE:
							space=1;
						break;
						default: break;
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
			if ((*in).up)
				(*f)=5;
			else if ((*in).down)
				(*f)=7;
			else
				(*f)=1;
		}
		else if ((*in).left)
		{
			if ((*in).up)
				(*f)=6;
			else if ((*in).down)
				(*f)=8;
			else
				(*f)=2;
		}
		else if ((*in).up)
		{
			if ((*in).left)
				(*f)=6;
			else if ((*in).right)
				(*f)=5;
			else
				(*f)=3;
		}
		else if ((*in).down)
		{
			if ((*in).left)
				(*f)=8;
			else if ((*in).right)
				(*f)=7;
			else
				(*f)=4;
		}
		else if (space)
		{
			(*f)=10;
		}
		else
		{
			(*f)=0;
		}

}
int Deplacement_Perso1 (perso *per,int *l,int *s,SDL_Rect *camera,background level,button *butn)
{
	int col,m=0,f;
	perso per_0;
	per_0=(*per);
	(*per).state=0;
	f=(*l);
	/*if ((*s)!=0)
		(*per).speed=7;
	else
		(*per).speed=5;
	if ((*s)<=-1)
	{
		if ((*s)<=-3)
		{
			(*per).position.y+=(*s);
			(*s)+=2;
			if (collision_back(per,level)==4)
				(*s)=1;
		}
		else
			(*s)=1;
	}
	if ((*s)>=1)
	{
		if ((*per).position.y<detec_sol(per->position.x + per->render->w-87,level)-147)
		{
			(*per).position.y+=(*s);
			(*s)++;
		}
		else
		{
			(*s)=0;
			(*per).position.y=detec_sol(per->position.x + per->render->w-87,level)-147;
		}
	}*/
	if (f==1)
	{
		if ((*per).position.x<1500)
		{
			(*per).position.x+=(*per).speed;
			(*per).state=1;
			m=1;
		}
	}
	else if (f==2)
	{
		if ((*per).position.x>10)
		{
			m=1;
			(*per).position.x-=(*per).speed;
			(*per).state=2;
		}
	}
	else if (f==3)
	{
		if ((*per).position.y>0)
		{
			m=1;
			(*per).position.y-=(*per).speed;
			(*per).state=3;
		}
	}
	else if (f==4)
	{
		if ((*per).position.y<6000)
		{
			m=1;
			(*per).position.y+=(*per).speed;
			(*per).state=4;
		}
	}
	else if (f==5)
	{
		if ((*per).position.x<5950)
		{
			m=1;
			(*per).position.x+=(*per).speed;
		}
		if ((*per).position.y>0)
		{
			m=1;
			(*per).position.y-=(*per).speed;
		}
	}
	else if (f==6)
	{
		if ((*per).position.x>50)
		{
			m=1;
			(*per).position.x-=(*per).speed;
		}
		if ((*per).position.y>0)
		{
			m=1;
			(*per).position.y-=(*per).speed;
		}
	}
	else if (f==7)
	{
		if ((*per).position.x<5950)
		{
			m=1;
			(*per).position.x+=(*per).speed;
		}
		if ((*per).position.y<260)
		{
			m=1;
			(*per).position.y+=(*per).speed;
		}
	}
	else if (f==8)
	{
		if ((*per).position.x>50)
		{
			m=1;
			(*per).position.x-=(*per).speed;
		}
		if ((*per).position.y<260)
		{
			m=1;
			(*per).position.y+=(*per).speed;
		}
	}
	else
	{
		(*per).state=0;
	}
	col=collision_back1(per,level,butn);
	if (col==1)
	{
		(*per)=per_0;
		(*per).state=0;
		(*s)=0;
	}
	else if (col==5)
	{
		(*per)=per_0;
		(*per).state=0;
		(*l)=0;
	}
	//else if ((*s)==0)
		//(*per).position.y=detec_sol((per->position.x + per->render->w/2 + per->width/2),level)-147;
	return m;
}
void scrolling1 (perso *per, SDL_Rect *camera)
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
	    if( camera->x > map_width - camera->w )
	    {
	        camera->x = map_width - camera->w;
	    }
	    if( camera->y > map_height - camera->h )
	    {
	        camera->y = map_height - camera->h;
	    }
    	per->position_affichage.x=per->position.x-camera->x;
		per->position_affichage.y=per->position.y-camera->y;
}
void init1 (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level,button *butn,int levels)
{
	int i;
	char im[50];
	 init_button(butn);
	if (levels==1)
	{
	per->position.x=10;
	per->position.y=10;
	}
	else if (levels==2)
	{
	per->position.x=500;
	per->position.y=300;
	}
	else if (levels==3)
	{
	per->position.x=800;
	per->position.y=500;
	}
	//(*per).position_affichage.x=10;
	(*per).height=120;
	(*per).width=22;
	(*per).state=0;
	(*per).state0=1;
	(*per).anim=0;
	(*per).inventory=0;
	(*per).speed=5;
	strcpy((*per).name,"Dante");
	strcpy((*per).images,"images/sprites_map/right/");
	sprintf(im,"%sstill.png",(*per).images);
	(*per).render=IMG_Load("images/sprites_map/right/1.png");
	(*level).back1=IMG_Load("polices/Map.jpg");
	(*level).back_col=IMG_Load("polices/Map_col.jpg");
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
	for(i=0;i<3;i++)
	{
		sprintf(im,"%s%d.png",(*per).images,i+1);
		(*per).walk_right[i]=IMG_Load(im);
	}
	strcpy((*per).images,"images/sprites_map/left/");
	for(i=0;i<3;i++)
	{
		sprintf(im,"%s%d.png",(*per).images,i+1);
		(*per).walk_left[i]=IMG_Load(im);
	}
	strcpy((*per).images,"images/sprites_map/up/");
	for(i=0;i<3;i++)
	{
		sprintf(im,"%s%d.png",(*per).images,i+1);
		(*per).walk_up[i]=IMG_Load(im);
	}
	strcpy((*per).images,"images/sprites_map/down/");
	for(i=0;i<3;i++)
	{
		sprintf(im,"%s%d.png",(*per).images,i+1);
		(*per).walk_down[i]=IMG_Load(im);
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
int collision_back1(perso *dante,background a,button *butn)
{
	int col=0;
	butn->show=0;
	butn->n_tab=0;
SDL_Rect point[8];
SDL_Color couleur[8];

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


couleur[0]=GetPixel (a.back_col, point[0].x, point[0].y);
couleur[1]=GetPixel (a.back_col, point[1].x, point[1].y);
couleur[2]=GetPixel (a.back_col, point[2].x, point[2].y);
couleur[3]=GetPixel (a.back_col, point[3].x, point[3].y);
couleur[4]=GetPixel (a.back_col, point[4].x, point[4].y);
couleur[5]=GetPixel (a.back_col, point[5].x, point[5].y);
couleur[6]=GetPixel (a.back_col, point[6].x, point[6].y);
couleur[7]=GetPixel (a.back_col, point[7].x, point[7].y);


/*if (couleur[0].r!=255 || couleur[0].g!=255 || couleur[0].b!=255)
return 10;

else if (couleur[1].r==255 && couleur[1].g==255 && couleur[1].b==255)
return 3;*/


if ((couleur[2].r==254 && couleur[2].g==0 && couleur[2].b==0)||(couleur[6].r==254 && couleur[6].g==0 && couleur[6].b==0)||(couleur[7].r==254 && couleur[7].g==0 && couleur[7].b==0))
	{col= 3;
	butn->show=1;
	butn->n_tab=1;}
if (couleur[3].r==254 && couleur[3].g==0 && couleur[3].b==0)
	{col= 4;
	butn->show=1;
	butn->n_tab=1;}
if ((couleur[4].r==254 && couleur[4].g==0 && couleur[4].b==0)||(couleur[6].r==254 && couleur[6].g==0 && couleur[6].b==0))
	{col= 5;
	butn->show=1;
	butn->n_tab=1;}
/*if ((couleur[6].r==255 && couleur[6].g==255 && couleur[6].b==255)||(couleur[4].r==255 && couleur[4].g==255 && couleur[4].b==255))
return 5;*/
if (couleur[5].r==254 && couleur[5].g==0 && couleur[5].b==0)
	{col= 2;
	butn->show=1;
	butn->n_tab=1;}
if ((couleur[0].r==254 && couleur[0].g==0 && couleur[0].b==0)&&(couleur[4].r==254 && couleur[4].g==0 && couleur[4].b==0)&&(couleur[5].r==254 && couleur[5].g==0 && couleur[5].b==0))
	{col= 1;
	butn->show=1;
	butn->n_tab=1;}



if ((couleur[2].r==0 && couleur[2].g==255 && couleur[2].b==1)||(couleur[6].r==0 && couleur[6].g==255 && couleur[6].b==1)||(couleur[7].r==0 && couleur[7].g==255 && couleur[7].b==1))
	{col= 3;
	butn->show=1;
	butn->n_tab=2;}
if (couleur[3].r==0 && couleur[3].g==255 && couleur[3].b==1)
	{col= 4;
	butn->show=1;
	butn->n_tab=2;}
if ((couleur[4].r==0 && couleur[4].g==255 && couleur[4].b==1)||(couleur[6].r==0 && couleur[6].g==255 && couleur[6].b==1))
	{col= 5;
	butn->show=1;
	butn->n_tab=2;}
/*if ((couleur[6].r==0 && couleur[6].g==255 && couleur[6].b==1)||(couleur[4].r==0 && couleur[4].g==255 && couleur[4].b==1))
return 5;*/
if (couleur[5].r==0 && couleur[5].g==255 && couleur[5].b==1)
	{col= 2;
	butn->show=1;
	butn->n_tab=2;}
if ((couleur[0].r==0 && couleur[0].g==255 && couleur[0].b==1)&&(couleur[4].r==0 && couleur[4].g==255 && couleur[4].b==1)&&(couleur[5].r==0 && couleur[5].g==255 && couleur[5].b==1))
	{col= 1;
	butn->show=1;
	butn->n_tab=2;}



if ((couleur[2].r==0 && couleur[2].g==0 && couleur[2].b==254)||(couleur[6].r==0 && couleur[6].g==0 && couleur[6].b==254)||(couleur[7].r==0 && couleur[7].g==0 && couleur[7].b==254))
	{col= 3;
	butn->show=1;
	butn->n_tab=3;}
if (couleur[3].r==0 && couleur[3].g==0 && couleur[3].b==254)
	{col= 4;
	butn->show=1;
	butn->n_tab=3;}
if ((couleur[4].r==0 && couleur[4].g==0 && couleur[4].b==254)||(couleur[6].r==0 && couleur[6].g==0 && couleur[6].b==254))
	{col= 5;
	butn->show=1;
	butn->n_tab=3;}
/*if ((couleur[6].r==0 && couleur[6].g==0 && couleur[6].b==254)||(couleur[4].r==0 && couleur[4].g==0 && couleur[4].b==254))
return 5;*/
if (couleur[5].r==0 && couleur[5].g==0 && couleur[5].b==254)
	{col= 2;
	butn->show=1;
	butn->n_tab=3;}
if ((couleur[0].r==0 && couleur[0].g==0 && couleur[0].b==254)&&(couleur[4].r==0 && couleur[4].g==0 && couleur[4].b==254)&&(couleur[5].r==0 && couleur[5].g==0 && couleur[5].b==254))
	{col= 1;
	butn->show=1;
	butn->n_tab=3;}


return col;

}
void animation1(perso *per)
{
	if ((*per).state!=(*per).state0)
	{
		(*per).anim=0;
	}
	if ((*per).state==1)
	{
		(*per).state0=(*per).state;
		(*per).render=(*per).walk_right[(*per).anim];
		(*per).anim++;
	}
	else if ((*per).state==2)
	{
		(*per).state0=(*per).state;
		(*per).render=(*per).walk_left[(*per).anim];
		(*per).anim++;
	}
	else if ((*per).state==3)
	{
		(*per).state0=(*per).state;
		(*per).render=(*per).walk_up[(*per).anim];
		(*per).anim++;
	}
	else if ((*per).state==4)
	{
		(*per).state0=(*per).state;
		(*per).render=(*per).walk_down[(*per).anim];
		(*per).anim++;
	}
	else if ((*per).state==0)
	{
		(*per).anim=0;
		if ((*per).state0==1)
			(*per).render=(*per).walk_right[(*per).anim];
		if ((*per).state0==2)
			(*per).render=(*per).walk_left[(*per).anim];
	}
	if ((*per).anim>2)
	{
		(*per).anim=0;
	}
}
void init_button(button *butn)
{
    butn->show=0;
    butn->cnt_blit=0;
    butn->n_tab=0;
    butn->position.x=1200;
    butn->position.y=500;
    butn->button[0]=IMG_Load("buttons/button.png");
    butn->button[1]=IMG_Load("buttons/buttonp.png");
}
