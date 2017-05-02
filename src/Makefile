prog:menu.o stage1.o main.o map.o
	gcc main.o stage1.o menu.o map.o -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -o prog -g
main.o:main.c
	gcc main.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
stage1.o:stage1.c
	gcc stage1.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
menu.o:menu.c
	gcc menu.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
map.o:map.c
	gcc map.c -lSDL -lSDL_image -lSDL_mixer  -lSDL_ttf -lSDL_gfx -c -g
make:clean
