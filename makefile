all: game_setup.c
	gcc game_setup.c

run: all
	./a.out

clean:
	rm *.o
	rm *~
	rm a.out
