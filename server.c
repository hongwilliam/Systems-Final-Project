#include "headers.h"

void process(char *s);
void subserver(int from_client);

int main() {

  int num_players = 0;
  int player_pids[4];

  int listen_socket;
  int f;
  listen_socket = server_setup();

  while (num_players != 4) {

    // poor coding but I don't really understand select statements so...

    if (num_players == 0) {
      // PLAYER 1
      mkfifo("to_p1", 0644);
      mkfifo("from_p1", 0644);

      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        int to_p1 = open("to_p1", O_RDONLY, 0644);
        int from_p1 = open("from_p1", O_WRONLY, 0644);
        subserver(client_socket);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        int to_p1 = open("to_p1", O_WRONLY, 0644);
        int from_p1 = open("from_p1", O_RDONLY, 0644);
        close(client_socket);
      }
    }

    if (num_players == 1) {
      // PLAYER 2
      mkfifo("to_p2", 0644);
      mkfifo("from_p2", 0644);

      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        int to_p1 = open("to_p2", O_RDONLY, 0644);
        int from_p1 = open("from_p2", O_WRONLY, 0644);
        subserver(client_socket);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        int to_p1 = open("to_p2", O_WRONLY, 0644);
        int from_p1 = open("from_p2", O_RDONLY, 0644);
        close(client_socket);
      }
    }

    if (num_players == 2) {
      // PLAYER 3
      mkfifo("to_p3", 0644);
      mkfifo("from_p3", 0644);

      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        int to_p1 = open("to_p3", O_RDONLY, 0644);
        int from_p1 = open("from_p3", O_WRONLY, 0644);
        subserver(client_socket);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        int to_p1 = open("to_p3", O_WRONLY, 0644);
        int from_p1 = open("from_p3", O_RDONLY, 0644);
        close(client_socket);
      }
    }

    if (num_players == 3) {
      // PLAYER 4
      mkfifo("to_p4", 0644);
      mkfifo("from_p4", 0644);

      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        int to_p1 = open("to_p4", O_RDONLY, 0644);
        int from_p1 = open("from_p4", O_WRONLY, 0644);
        subserver(client_socket);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        int to_p1 = open("to_p4", O_WRONLY, 0644);
        int from_p1 = open("from_p4", O_RDONLY, 0644);
        close(client_socket);
      }
    }



  }

  printf("\nAll four players have connected\n");
}




void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
