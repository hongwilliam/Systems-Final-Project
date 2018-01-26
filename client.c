#include "headers.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[1000];

  if (argc == 2)
    server_socket = client_setup( argv[1] );
  else
    server_socket = client_setup( TEST_IP );

  while (1) {
    // display the prompt coming from the server
    read(server_socket, buffer, 1000);
    printf("%s\n", buffer);
    // wait for the user response
    fgets(buffer, 1000, stdin);
    // write the response back to the server
    write(server_socket, buffer, 1000);
  }
}
