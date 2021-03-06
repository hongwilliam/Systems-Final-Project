network: client server

networking.o: networking.c headers.h
	gcc -c networking.c

server: server.o networking.o game_setup.o compare_hand.o
	gcc -o server server.o networking.o game_setup.o compare_hand.o

server.o: server.c headers.h
	gcc -c server.c

client: client.o networking.o
		gcc -o client client.o networking.o

client.o: client.c headers.h
		gcc -c client.c


game_setup.o: game_setup.c headers.h
	gcc -c game_setup.c

compare_hand.o: compare_hand.c headers.h
	gcc -c compare_hand.c

clean:
	rm *.o
	rm client
	rm server
	rm testing
	rm *~
