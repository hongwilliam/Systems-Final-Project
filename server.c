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

  check_start();

  winner = -1
  // run until a player wins
  while( winner == -1 ){

    // player 1
    if (current_turn == 0){
      char prompt[1000];
      char response[1000];

      // display the current hand
      char p1hand[1000] = get_hand( hand_one );
      write( to_p1, p1hand, sizeof(p1hand) );

      // determine the form
      if ( strcmp(current_form, "free") == 0 ){

        // waiting for the user to select a form
        int wait_for_form = 1;
        while(wait_for_form) {
          prompt = "Please choose either single, double, or combo\n";
          write( to_p1, prompt, sizeof(prompt) );

          read( from_p1, response, sizeof(response) );
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
            prompt = "Inappropriate input (hit enter)\n";
            write( to_p1, prompt, sizeof(prompt) );
          }
        }
      }

      // handling the user single
      if ( strcmp(current_form, "single") == 0 ){
        prompt = "Please select the card id you wish to choose\n";
        write( to_p1, prompt, sizeof(prompt) );

        read( from_p1, response, sizeof(response) );
        int card_rank;
        sscanf(response, "%d", &card_rank);
        current_single = get_card( card_rank );

        prompt = "Thank you for your single!\n";
        write( to_p1, prompt, sizeof(prompt) );
      }

      // handling the user double
      if ( strcmp(current_form, "double") == 0 ){
        prompt = "Please select the card ids you wish to choose separated by spaces\n";
        write( to_p1, prompt, sizeof(prompt) );

        read( from_p1, response, sizeof(response) );
        int card_1;
        int card_2;
        sscanf(response, "%d %d", &card_1, &card_2);
        current_double[0] = get_card( card_1 );
        current_double[1] = get_card( card_2 );

        prompt = "Thank you for your double!\n";
        write( to_p1, prompt, sizeof(prompt) );
      }

      // handling the user combo
      if ( strcmp(current_form, "combo") == 0 ){
        prompt = "Please select the card ids you wish to choose separated by spaces\n";
        write( to_p1, prompt, sizeof(prompt) );

        read( from_p1, response, sizeof(response) );
        int card_1, card_2, card_3, card_4, card_5;
        sscanf(response, "%d %d %d %d %d", &card_1, &card_2, &card_3, &card_4, &card_5);
        current_combo[0] = get_card( card_1 );
        current_combo[1] = get_card( card_2 );
        current_combo[2] = get_card( card_3 );
        current_combo[3] = get_card( card_4 );
        current_combo[4] = get_card( card_5 );

        prompt = "Thank you for your combo!\n";
        write( to_p1, prompt, sizeof(prompt) );
      }

      current_turn = (current_turn + 1) % 4;
      prompt = "Your turn is over, please wait for the next turn\n";
      write( to_p1, prompt, sizeof(prompt) );
    }

    // player 2
    if (current_turn == 1){
      char p2hand[1000] = get_hand( hand_two );
      write( to_p1, p2hand, sizeof(p2hand) );
    }

    // player 3
    if (current_turn == 2){
      char p3hand[1000] = get_hand( hand_three );
      write( to_p1, p3hand, sizeof(p3hand) );
    }

    // player 4
    if (current_turn == 3){
      char p4hand[1000] = get_hand( hand_four );
      write( to_p1, p4hand, sizeof(p4hand) );
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
