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
};

int random_ints[52];
struct card deck[53];
struct card hand_one[13];
struct card hand_two[13];
struct card hand_three[13];
struct card hand_four[13];

void initialize_card(int value, int suit);
void initialize_deck();
void dislay_card_ranking(int ranking);
void display_card(struct card);
void set_hand(struct card hand[], int ranking, int index);
void deal_random_ints();
void deal_hands();
void display_hand(struct card hand[]);
