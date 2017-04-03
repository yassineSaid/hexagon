#include "stage1.h"
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
	SDL_BlitSurface(level.back_col,&camera,ecran,&positionFond);
	per.position.y=detec_sol(per.position.x,level)-119;
	SDL_BlitSurface(level.back,&camera,ecran,&positionFond);
	SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
	//SDL_Flip(ecran);
	while (continuer!=0)
    {
    	input(&continuer,&f,&s,&in);
		m=Deplacement_Perso(&per,f,&s,&camera,level);
	    scrolling(&per,&camera);
	    animation(&per);
		SDL_BlitSurface(level.back,&camera,ecran,&positionFond);
		SDL_BlitSurface(per.render,NULL,ecran,&per.position_affichage);
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
int Deplacement_Perso (perso *per,int f,int *s,SDL_Rect *camera,background level)
{
	int col,m=0,i=8;
	perso per_0;
	per_0=(*per);
	(*per).state=0;
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
			(*per).position.y=detec_sol((*per).position.x,level)-119;
		}
	}
	if (f==1)
	{
		if ((*per).position.x<10950)
		{
			(*per).position.x+=(*per).speed;
			(*per).state=1;
			m=1;
		}
	}
	else if (f==2)
	{
		if ((*per).position.x>50)
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
	else
	{
		(*per).state=0;
	}
	col=collision_back(per,level);
	if (col!=10)
	{
		(*per)=per_0;
		
	}
	
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
	(*per).position.y=300;
	(*per).position_affichage.x=10;
	(*per).height=175;
	(*per).width=175;
	(*per).state=0;
	(*per).state0=1;
	(*per).anim=0;
	(*per).inventory=0;
	(*per).speed=5;
	strcpy((*per).name,"Dante");
	strcpy((*per).images,"pablo_testing_imin/pablo_");
	sprintf(im,"%sstill.png",(*per).images);
	(*per).render=IMG_Load("bassem.png");
	(*level).back=IMG_Load("stage1 edit.jpg");
	(*level).back_col=IMG_Load("stage1_col.png");
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
	for(i=0;i<49;i++)
	{
		sprintf(im,"%s%05d.png",(*per).images,i);
		(*per).walk_right[i]=IMG_Load(im);
	printf("%d\n",i);
	}
	strcpy((*per).images,"pablo_testing_isar/pablo_");
	for(i=0;i<49;i++)
	{
		sprintf(im,"%s%05d.png",(*per).images,i);
		(*per).walk_left[i]=IMG_Load(im);
	printf("%d\n",i);
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

/*int collision_back(perso *dante,background *level)
{

SDL_Rect point[8];
SDL_Color couleur[8];

point[0].x=dante->position.x + dante->render->w;
point[0].y=dante->position.y + dante->render->h/2;


point[4].x=dante->position.x + dante->render->w;
point[4].y=dante->position.y +dante->render->h/4;

point[5].x=dante->position.x + dante->render->w;
point[5].y=dante->position.y + (dante->render->h*3)/4;

point[1].x=dante->position.x + dante->render->w/2;
point[1].y=dante->position.y + dante->render->h;

point[2].x=dante->position.x;
point[2].y=dante->position.y + dante->render->h/2;

point[6].x=dante->position.x;
point[6].y=dante->position.y + dante->render->h/4;

point[7].x=dante->position.x;
point[7].y=dante->position.y + (dante->render->h*3)/4;

point[3].x=dante->position.x + dante->render->w/2;
point[3].y=dante->position.y;

couleur[0]=GetPixel ((*level).back_col, point[0].x, point[0].y);
couleur[1]=GetPixel ((*level).back_col, point[1].x, point[1].y);
couleur[2]=GetPixel ((*level).back_col, point[2].x, point[2].y);
couleur[3]=GetPixel ((*level).back_col, point[3].x, point[3].y);
couleur[4]=GetPixel ((*level).back_col, point[4].x, point[4].y);
couleur[5]=GetPixel ((*level).back_col, point[5].x, point[5].y);
couleur[6]=GetPixel ((*level).back_col, point[6].x, point[6].y);
couleur[7]=GetPixel ((*level).back_col, point[7].x, point[7].y);

  
if (couleur[1].r!=255 && couleur[1].g!=255 && couleur[1].b!=255)
return 10;

else if (couleur[3].r==255 && couleur[3].g==255 && couleur[3].b==255)
return 4;

else if (couleur[1].r==255 && couleur[1].g==255 && couleur[1].b==255)
return 3;

else if ((couleur[2].r==255 && couleur[2].g==255 && couleur[2].b==255)||(couleur[6].r==255 && couleur[6].g==255 && couleur[6].b==255)||(couleur[7].r==255 && couleur[7].g==255 && couleur[7].b==255))
return 2;

else if ((couleur[0].r==255 && couleur[0].g==255 && couleur[0].b==255)||(couleur[4].r==255 && couleur[4].g==255 && couleur[4].b==255)||(couleur[5].r==255 && couleur[5].g==255 && couleur[5].b==255))
return 1;

else return 0;

}*/
int collision_back(perso *dante,background a)
{

SDL_Rect point[8];
SDL_Color couleur[8];

point[0].x=dante->position.x + dante->render->w-87;
point[0].y=dante->position.y + dante->render->h/2;


point[4].x=dante->position.x + dante->render->w-87;
point[4].y=dante->position.y + dante->render->h/4;

point[5].x=dante->position.x + dante->render->w-87;
point[5].y=dante->position.y + (dante->render->h*3)/4;

point[1].x=dante->position.x + dante->render->w/2;
point[1].y=dante->position.y + dante->render->h;

point[2].x=dante->position.x+87;
point[2].y=dante->position.y + dante->render->h/2;

point[6].x=dante->position.x+87;
point[6].y=dante->position.y + dante->render->h/4;

point[7].x=dante->position.x+87;
point[7].y=dante->position.y + (dante->render->h*3)/4;

point[3].x=dante->position.x + dante->render->w/2;
point[3].y=dante->position.y;

couleur[0]=GetPixel (a.back_col, point[0].x, point[0].y);
couleur[1]=GetPixel (a.back_col, point[1].x, point[1].y);
couleur[2]=GetPixel (a.back_col, point[2].x, point[2].y);
couleur[3]=GetPixel (a.back_col, point[3].x, point[3].y);
couleur[4]=GetPixel (a.back_col, point[4].x, point[4].y);
couleur[5]=GetPixel (a.back_col, point[5].x, point[5].y);
couleur[6]=GetPixel (a.back_col, point[6].x, point[6].y);
couleur[7]=GetPixel (a.back_col, point[7].x, point[7].y);

  
if (couleur[1].r!=255 && couleur[1].g!=255 && couleur[1].b!=255)
return 10;


else if (couleur[3].r==255 && couleur[3].g==255 && couleur[3].b==255)
return 4;

else if (couleur[1].r==255 && couleur[1].g==255 && couleur[1].b==255)
return 3;

else if ((couleur[2].r==255 && couleur[2].g==255 && couleur[2].b==255)||(couleur[6].r==255 && couleur[6].g==255 && couleur[6].b==255)||(couleur[7].r==255 && couleur[7].g==255 && couleur[7].b==255))
return 2;

else if ((couleur[0].r==255 && couleur[0].g==255 && couleur[0].b==255)||(couleur[4].r==255 && couleur[4].g==255 && couleur[4].b==255)||(couleur[5].r==255 && couleur[5].g==255 && couleur[5].b==255))
return 1;

else return 0;

}
void animation(perso *per)
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
	else if ((*per).state==0)
	{
		(*per).anim=0;
		if ((*per).state0==1)
			(*per).render=(*per).walk_right[(*per).anim];
		if ((*per).state0==2)
			(*per).render=(*per).walk_left[(*per).anim];
	}
	if ((*per).anim>48)
	{
		(*per).anim=10;
	}
}
int detec_sol (int x,background a)
{
	int i,y;
	SDL_Color couleur;
	i=level_height-50;
	y=0;
	while ((i>0)&&(y==0))
	{
		couleur=GetPixel (a.back_col, x, i);
		if (couleur.r!=255 || couleur.g!=255 || couleur.b!=255)
			y=i;
		i--;
	}
	if (y==0)
		y=400;
	return y;
}