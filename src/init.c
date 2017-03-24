#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stage1.h>


void initilisation(perso *per)
{
	int i;
	char im[50];
	(*per).position.x=10;
	(*per).position.y=250;
	(*per).position_affichage.x=10;
	(*per).position_affichage.y=250;
	(*per).tentative=3;
	(*per).state=0;
	(*per).inventory=0;
	strcpy((*per).name,"Dante");
	strcpy((*per).images,"images/perso/");
	sprintf(im,"%sstill.png",(*per).images);
	still=IMG_Load(im);
	for(i=0;i<7;i++)
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
	}
}
