int collision_entites(SDL_Surface A , SDL_Surface B ,SDL_Rect posA , SDL_Resct posB)
{
	int a;
	if(posA.x<posB.x)
	{
		if(((posA.x+A->w) >= posB.x) && (posB.y >= posA.y) && (posB.y <= (posA.y+A->h))) 
		{
			a=1;	
		}
		else
		{
		a=0;
		}
	}
	else
	{
		if(((posB.x+B->w) >= posA.x) && (posA.y >= posB.y) && (posA.y <= (posB.y+B->h))) 
		{
			a=1;
		}
		else
		{
			a=0;
		}
	}
return a;	
}