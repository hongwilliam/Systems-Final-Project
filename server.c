#include "headers.h"

// void process(char *s);
// void subserver(int from_client);
void player_coms( int to_player, int from_player, struct card hand[]);
void subserver( int client_socket, char * to_player_pipe, char * from_player_pipe);


int main() {

  int num_players = 0;
  int player_pids[4];

  int listen_socket;
  int f;
  listen_socket = server_setup();

  mkfifo("to_p1", 0644);
  mkfifo("from_p1", 0644);
  int to_p1;
  int from_p1;

  mkfifo("to_p2", 0644);
  mkfifo("from_p2", 0644);
  int to_p2;
  int from_p2;

  mkfifo("to_p3", 0644);
  mkfifo("from_p3", 0644);
  int to_p3;
  int from_p3;

  mkfifo("to_p4", 0644);
  mkfifo("from_p4", 0644);
  int to_p4;
  int from_p4;

  while (num_players != 4) {

    // poor coding but I don't really understand select statements so...
    if (num_players == 0) {
      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        subserver(client_socket, "to_p1", "from_p1");
        exit(0);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        to_p1 = open("to_p1", O_WRONLY, 0644);
        from_p1 = open("from_p1", O_RDONLY, 0644);
        close(client_socket);
      }
    }

    if (num_players == 1) {
      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        subserver(client_socket, "to_p2", "from_p2");
        exit(0);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        int to_p2 = open("to_p2", O_WRONLY, 0644);
        int from_p2 = open("from_p2", O_RDONLY, 0644);
        close(client_socket);
      }
    }

    if (num_players == 2) {
      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        subserver(client_socket, "to_p3", "from_p3");
        exit(0);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        to_p3 = open("to_p3", O_WRONLY, 0644);
        from_p3 = open("from_p3", O_RDONLY, 0644);
        close(client_socket);
      }
    }

    if (num_players == 3) {
      int client_socket = server_connect(listen_socket);
      f = fork();
      if (f == 0) {
        subserver(client_socket, "to_p4", "from_p4");
        exit(0);
      } else {
        player_pids[ num_players ] = f;
        num_players++;
        to_p4 = open("to_p4", O_WRONLY, 0644);
        from_p4 = open("from_p4", O_RDONLY, 0644);
        close(client_socket);
      }
    }

  }

  printf("\nAll four players have connected!\n");

  // set up the game
  initialize_deck();
  deal_hands();
  current_form = "free";
  check_start();


  // the game loop
  int winner = -1;
  while( winner == -1 ){
    // player 1
    if (current_turn == 1){
      player_coms( to_p1, from_p1, hand_one );
    }
    // player 2
    if (current_turn == 2){
      player_coms( to_p2, from_p2, hand_two );
    }
    // player 3
    if (current_turn == 3){
      player_coms( to_p3, from_p3, hand_three );
    }
    // player 4
    if (current_turn == 4){
      player_coms( to_p4, from_p4, hand_four );
    }
  }
}



// handles communication between the subservers and the main server
void player_coms(int to_player, int from_player, struct card hand[]){
  char * prompt;
  char response[1000];

  // prompt the player
  prompt = get_hand( hand, 13 );
  write( to_player, prompt, 1000 );

  // handle if it's a free slot
  if ( strcmp(current_form, "free") == 0 ){

    // waiting for the user to select a form
    int wait_for_form = 1;
    while(wait_for_form) {
      prompt = "Please choose either single, double, or combo\n";
      write( to_player, prompt, 1000 );

      read( from_player, response, 1000 );
      printf("%s\n", response);
      if( strcmp(response, "single") == 0 ){
        current_form = "single";
        wait_for_form = 0;
      } else if( strcmp(response, "double") == 0 ){
        current_form = "double";
        wait_for_form = 0;
      } else if( strcmp(response, "combo") == 0){
        current_form = "combo";
        wait_for_form = 0;
      } else {
        prompt = "Inappropriate input (hit enter)\n";
        write( to_player, prompt, 1000 );
      }
    }
  }

  // handling the user single
  if ( strcmp(current_form, "single") == 0 ){
    prompt = "Please select the card id you wish to choose\n";
    write( to_player, prompt, 1000 );

    read( from_player, response, 1000 );
    int card_rank;
    sscanf(response, "%d", &card_rank);

    /*
      handle figuring out if it's a valid play
    */

    current_single = get_card( card_rank );
    prompt = "Thank you for your single!\n";
    write( to_player, prompt, 1000 );
  }

  // handling the user double
  if ( strcmp(current_form, "double") == 0 ){
    prompt = "Please select the card ids you wish to choose (separated by spaces)\n";
    write( to_player, prompt, 1000 );

    read( from_player, response, 1000 );
    int card_1;
    int card_2;
    sscanf(response, "%d %d", &card_1, &card_2);

    /*
      handle figuring out if it's a valid play
    */

    current_double[0] = get_card( card_1 );
    current_double[1] = get_card( card_2 );
    prompt = "Thank you for your double!\n";
    write( to_player, prompt, 1000 );
  }

  // handling the user combo
  if ( strcmp(current_form, "combo") == 0 ){
    prompt = "Please select the card ids you wish to choose (separated by spaces)\n";
    write( to_player, prompt, 1000 );

    read( from_player, response, 1000 );
    int card_1, card_2, card_3, card_4, card_5;
    sscanf(response, "%d %d %d %d %d", &card_1, &card_2, &card_3, &card_4, &card_5);

    /*
      handle figuring out if it's a valid play
    */

    current_combo[0] = get_card( card_1 );
    current_combo[1] = get_card( card_2 );
    current_combo[2] = get_card( card_3 );
    current_combo[3] = get_card( card_4 );
    current_combo[4] = get_card( card_5 );
    prompt = "Thank you for your combo!\n";
    write( to_player, prompt, 1000 );
  }

  current_turn = (current_turn + 1) % 4;
  prompt = "Your turn is over, please wait for the next turn\n";
  write( to_player, prompt, 1000 );
}


// the subserver instructions
void subserver( int client_socket, char * to_player_pipe, char * from_player_pipe){
  int from_server = open(to_player_pipe, O_RDONLY, 0644);
  int to_server = open(from_player_pipe, O_WRONLY, 0644);
  remove(to_player_pipe);
  remove(from_player_pipe);
  char buffer[1000];

  while( read(from_server, buffer, 1000) ){
    // send the prompt to the client
    write(client_socket, buffer, 1000);
    // wait for the client's response
    read( client_socket, buffer, sizeof(buffer) );
    // send the response back to the server
    write(to_server, buffer, 1000);
  }
  close(client_socket);
  exit(0);
}














/*
void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while ( read(client_socket, buffer, sizeof(buffer)) ) {

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
*/
