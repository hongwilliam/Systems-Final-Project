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
  int rank; //from 1-52
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

//0 indicates that it's currently not that player's turn
int player_one_id = 0;
int player_two_id = 0;
int player_three_id = 0;
int player_four_id = 0;

//0 indicates that no player has won yet
int win_condition = 0;


void initialize_card(int value, int suit);
void initialize_deck();
void dislay_card_ranking(int ranking);
void display_card(struct card my_card);
void set_hand(struct card hand[], int ranking, int index);
void deal_random_ints();
void deal_hands();
void display_hand(struct card hand[]);
void swap(int* a, int* b);
int part (int array[], int min, int max);
void quicksort(int array[], int min, int max);
void sort_hand(int hand[]);
int compare_single(struct card A, struct card B);
int compare_double(struct card A1, struct card A2, struct card B1, struct card B2);
int check_straight(struct card A, struct card B, struct card C, struct card D, struct card E);
int check_flush(struct card A, struct card B, struct card C, struct card D, struct card E);
int check_house(struct card A, struct card B, struct card C, struct card D, struct card E);
int check_bomb(struct card A, struct card B, struct card C, struct card D, struct card E);
int check_straight_flush(struct card A, struct card B, struct card C, struct card D, struct card E);
int compare_straight(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5);
int compare_flush(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5);
int compare_house(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5);
int compare_bomb(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5);
int compare_straight_flush(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5);
int identify_combo(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5);
int compare_combo(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5);
void check_start();
int check_win_condition(struct card hand[]);
