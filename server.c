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
  initialize_deck();
  deal_hands();

  char p1hand[1000] = get_hand( hand_one );
  write( to_p1, p1hand, sizeof(p1hand) );

  char p2hand[1000] = get_hand( hand_two );
  write( to_p1, p2hand, sizeof(p2hand) );

  char p3hand[1000] = get_hand( hand_three );
  write( to_p1, p3hand, sizeof(p3hand) );

  char p4hand[1000] = get_hand( hand_four );
  write( to_p1, p4hand, sizeof(p4hand) );

  check_start();

  winner = -1
  // run until a player wins
  while( winner == -1 ){

    // player 1
    if (current_turn == 0){
      char prompt[1000];

      if ( strcmp(current_form, "free") == 0 ){
        // waiting on a form
        int wait_for_form = 1;
        while(wait_for_form) {
          prompt = "Please choose either single, double, or combo\n";
          write( to_p1, prompt, sizeof(prompt) );

          char response[1000];
          read( from_p2, response, sizeof(response) );
          if( strcmp(response, "single") ){
            current_form = "single";
            wait_for_form = 0;
          } else if( strcmp(response, "double") ){
            current_form = "double";
            wait_for_form = 0;
          } else if( strcmp(response, "combo") ){
            current_form = "combo";
            wait_for_form = 0;
          } else {
            prompt = "Inappropriate input\n";
            write( to_p1, prompt, sizeof(prompt) );
          }
        }
      }

      // singles
      if ( strcmp(current_form, "single") == 0 ){
      }

      // doubles
      if ( strcmp(current_form, "double") == 0 ){
      }

      // combo
      if ( strcmp(current_form, "combo") == 0 ){
      }
    }

    // player 2
    if (current_turn == 1){

    }

    // player 3
    if (current_turn == 2){

    }

    // player 4
    if (current_turn == 3){

    }

  }
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
