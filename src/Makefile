prog:menu.o stages.o main.o map.o
	gcc main.o stages.o menu.o map.o -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -o prog -g
main.o:main.c
	gcc main.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
stages.o:stages.c
	gcc stages.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
menu.o:menu.c
	gcc menu.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
map.o:map.c
	gcc map.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
make:clean
