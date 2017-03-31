#include "stage1.h"
#include "collision.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
void stage1()
{
	int continuer=1,x=0,y=0,f=0,m=0,s=0;
	SDL_Surface *ecran = NULL,*fond = NULL;
	SDL_Rect positionFond,camera;
	SDL_Event event;
	background level;
	perso per;
	inpu in;
	SDL_Init(SDL_INIT_VIDEO);
	ecran = SDL_SetVideoMode(1366, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	init (&per,&camera,&positionFond,&in,ecran,&level);
	SDL_BlitSurface(level.back,&camera,ecran,&positionFond);
	SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
	SDL_Flip(ecran);
	while (continuer!=0)
    {
    	input(&continuer,&f,&s,&in);
	    a=collision_back(&per);
	    while(a!=5)
	    {
	    	
		m=Deplacement_Perso(&per,f,&s,&camera);
	    scrolling(&per,&camera);
	    }
		SDL_BlitSurface(fond,&camera,ecran,&positionFond);
		SDL_BlitSurface(bass,NULL,ecran,&per.position_affichage);
		SDL_Flip(ecran);
		m=0;
    }
    SDL_FreeSurface(ecran);
    SDL_Quit();
 
}
void input (int *continuer, int *f,int *s,inpu *in)
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
							space=1;
						break;
		                /*case SDLK_DOWN: 
							(*in).down=1;
						break;*/
		                case SDLK_SPACE: 
							space=1;
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
		/*else if ((*in).up)
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
		}*/
		else
		{
			(*f)=0;
		}
		if ((space)&&((*s)==0))
		{
			(*s)=-20;
		}

}
int Deplacement_Perso (perso *per,int f,int *s,SDL_Rect *camera)
{
	int col,m=0,i=8;
	perso per_0;
	per_0=(*per);
	if ((*s)<=-1)
	{
		if ((*s)<=-3)	
		{
			(*per).position.y+=(*s);
			(*s)+=2;
		}
		else
			(*s)=1;
	}
	if ((*s)>=1)
	{
		if ((*per).position.y<=(level_height-(*per).render->h-10))
		{
			(*per).position.y+=(*s);
			(*s)++;
		}
		else
		{
			(*s)=0;
			(*per).position.y=250;
		}
	}
	if (f==1)
	{
		if ((*per).position.x<5950)
		{
			(*per).position.x+=(*per).speed;
			m=1;
		}
	}
	else if (f==2)
	{
		if ((*per).position.x>50)
		{
			m=1;
			(*per).position.x-=(*per).speed;
		}
	}
	else if (f==3)
	{
		if ((*per).position.y>0)
		{
			m=1;
			(*per).position.y-=(*per).speed;
		}
	}
	else if (f==4)
	{
		if ((*per).position.y<260)
		{
			m=1;
			(*per).position.y+=(*per).speed;
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
	//col=collision(*per);
	//if (col==1)
		//(*per)=per_0;
	return m;
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
void init (perso *per,SDL_Rect *camera,SDL_Rect *positionFond,inpu *in,SDL_Surface *ecran,background *level)
{
	int i;
	char im[50];
	(*per).position.x=10;
	(*per).position.y=250;
	(*per).position_affichage.x=10;
	(*per).position_affichage.y=250;
	(*per).tentatives=3;
	(*per).state=0;
	(*per).inventory=0;
	(*per).speed=10;
	strcpy((*per).name,"Dante");
	strcpy((*per).images,"images/perso/");
	sprintf(im,"%sstill.png",(*per).images);
	(*per).render=IMG_Load("bassem.png");
	(*level).back=IMG_Load("stage1 edit.jpg");
	(*camera).x=0;
	(*camera).y=0;
	(*camera).h=600;
	(*camera).w=1366;
	(*positionFond).x=0;
	(*positionFond).y=0;
	(*in).up=0;
	(*in).down=0;
	(*in).left=0;
	(*in).right=0;
	/*for(i=0;i<7;i++)
	{
		sprintf(im,"%swalk_left%d.png",(*per).images,i+1);
		walk_left[i]=IMG_Load(im);
	}
	for(i=0;i<7;i++)
	{
		sprintf(im,"%swalk_right%d.png",(*per).images,i+1);
		walk_right[i]=IMG_Load(im);
	}
	for(i=0;i<7;i++)
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