all:
	gcc main.c -o main.o -lSDL2 -lSDL2_image -ldl

clean:
	rm *.o