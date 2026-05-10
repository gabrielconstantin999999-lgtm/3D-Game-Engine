main: main.c 
	gcc main.c camera.c math_utils.c renderer.c -o main -lSDL3 -lm