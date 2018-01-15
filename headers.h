#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>

struct card{
  int value; //3 equals 0, 4 equals 1, etc
  int suit; //diamonds = 0, clubs = 1, etc
  //char name[256]; //"3 of Diamonds", etc
};

struct card deck[52];
struct card hand_one[13];
struct card hand_two[13];
struct card hand_three[13];
struct card hand_four[13];

void initialize_card(int value, int suit);
void initialize_deck();
void dislay_card(int ranking);
