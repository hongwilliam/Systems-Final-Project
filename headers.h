#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>

struct card{
  int value; //3 equals 1, 4 equals 2, etc
  int suit; //diamonds = 1, clubs = 2, etc
};

int random_ints[52];
int rand_hand_one[13];
int rand_hand_two[13];
int rand_hand_three[13];
int rand_hand_four[13];

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
void display_ints(int hand[]);
void swap(int* a, int* b);
int part (int array[], int min, int max);
void quicksort(int array[], int min, int max);
void sort_hand(int hand[]);
