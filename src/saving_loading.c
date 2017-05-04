#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "ntasti.h" 
void saving(perso *per)
{
	FILE* f=fopen("saved.txt", "w");
	if (f!=NULL)
	{
		fprintf(f,"%d %d %d %d %d %d\n"stage, per->position.y, per->position.x, per->tentatives, per->inventory, per->state);
		fclose(f);
	}
}
void loading(FILE *f, perso *per)
{
	if (f!=NULL) 
	{
		f=fopen("saved.txt", "r");
		fscanf(f, "%d %d %d %d %d %d\n",&stage, &per->position.y, &per->position.x, &per->tentatives, &per->inventory, &per->state);
		fclose(f);
	}
}
