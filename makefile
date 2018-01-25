testing: game_setup.o compare_hand.o
	gcc -o testing game_setup.o compare_hand.o

game_setup.o: game_setup.c headers.h
	gcc -c game_setup.c

compare_hand.o: compare_hand.c headers.h
	gcc -c compare_hand.c

run: testing
	./testing

clean:
	rm testing
	rm *.o
	rm *~
