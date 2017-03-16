int input ()
{
	int up=0,down=0,right=0,left=0,space=0;
	while (SDL_PollEvent(&event))
		{
			case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
	            {
	                case SDLK_RIGHT: 
						right=1;
					break;
	                case SDLK_LEFT: 
						left=1;
					break;
	                case SDLK_UP: 
						up=1;
					break;
	                case SDLK_DOWN: 
						down=1;
					break;
	                case SDLK_SPACE: 
						space=1;
					break;
				}
			break;
			case SDL_KEYUP
			switch(event.key.keysym.sym)
				{
					case SDLK_RIGHT: 
						right=0;
					break;
	                case SDLK_LEFT: 
						left=0;
					break;
	                case SDLK_UP: 
						up=0;
					break;
	                case SDLK_DOWN: 
						down=0;
					break;
	                case SDLK_SPACE: 
						space=0;
					break;
				}
			break;
		}
		if (right)
		{
			if (up)
				f=5;
			else if (down)
				f=7;
			else
				f=1;
		}
		else if (left)
		{
			if (up)
				f=6;
			else if (down)
				f=8;
			else
				f=2;
		}
		else if (up)
		{
			if (left)
				f=6;
			else if (right)
				f=5;
			else
				f=3;
		}
		else if (down)
		{
			if (left)
				f=8;
			else if (right)
				f=7;
			else
				f=4;
		}
		else
		{
			f=0;
		}
		return f;
}