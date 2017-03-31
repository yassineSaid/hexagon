#include "collision.h"
#include "stage1.h"

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

int collision_back(perso *dante)
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

couleur[0]=GetPixel (a.back_col, point[0].x, point[0].y);
couleur[1]=GetPixel (a.back_col, point[1].x, point[1].y);
couleur[2]=GetPixel (a.back_col, point[2].x, point[2].y);
couleur[3]=GetPixel (a.back_col, point[3].x, point[3].y);
couleur[4]=GetPixel (a.back_col, point[4].x, point[4].y);
couleur[5]=GetPixel (a.back_col, point[5].x, point[5].y);
couleur[6]=GetPixel (a.back_col, point[6].x, point[6].y);
couleur[7]=GetPixel (a.back_col, point[7].x, point[7].y);

  
if (couleur[1].r==0 && couleur[1].g==0 && couleur[1].b==0)
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


int ajout_cond_collision_back (perso *perso , int state)
{

  SDL_Rect point [4];
  SDL_Color couleur [4];

point[0].x= perso->position.x + perso->render->w;
point[0].y= perso->position.y + perso->render->h/2;

point[1].x= perso->position.x + perso->render->w/2;
point[1].y= perso->position.y + perso->render->h;

point[2].x= perso->position.x;
point[2].y= perso->position.y+perso->render->h/2;

point[3].x= perso->position.x+perso->render->w/2;
point[3].y= perso->position.y;

couleur[0]=GetPixel (a.back_col, point[0].x, point[0].y);
couleur[1]=GetPixel (a.back_col, point[1].x, point[1].y);
couleur[2]=GetPixel (a.back_col, point[2].x, point[2].y);
couleur[3]=GetPixel (a.back_col, point[3].x, point[3].y);

if (state==1)
{ if (couleur[0].r==255 && couleur[0].g==255 && couleur[0].b==255)
return 1;
}
if (state==2)
{ if (couleur[2].r==255 && couleur[2].g==255 && couleur[2].b==255)
return 1;
}
if (state==3)
{ if (couleur[1].r==255 && couleur[1].g==255 && couleur[1].b==255)
return 1;
}
if (state==4)
{ if (couleur[3].r==255 && couleur[3].g==255 && couleur[3].b==255)
return 1;
}
}