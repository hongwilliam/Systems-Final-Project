#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>

//CODE NOT TESTED YET
//PROB LOT OF SYNTAX ERRORS, PLZ FIX IF YOU CAN
//If you have better/efficient ways, feel free to delete some stuff

struct card{
  int value; //3 equals 0, 4 equals 1, etc
  int suit; //diamonds = 0, clubs = 1, etc
  char name[256]; //"3 of Diamonds", etc
};

struct card deck[52];
struct card hand_one[13]; //assuming 4 player game
struct card hand_two[13];
struct card hand_three[13];
struct card hand_four[13];

//inputs information into a card
//this sets up the deck in order of increasing value
//return type void
void initialize_card(int my_value, int my_shape){
  int ranking = (num % 4) + shape; //ex: 3 of diamond would be card 0, 3 of club would be card 1, etc
  deck[ranking]->value = my_value;
  deck[ranking]->suit = my_suit;
  //work on adding name later
}

//return type void
void initialize_deck(){
  int i = 0, v = 0, s = 0;
  while (i < 52){
    while (s < 3){
      initialize_card(v,s);
      s++; }
    v++;
    s = 0;
    i++;
  }
}

//pseudo code only
/**
void deal_hands(){
  int i = 0;
  int random_int = rand() % 52; //not sure if this is right
  while (i < 13){
    hand_one[0] = deck[random_int];
    //generate new random number not used before
    hand_two[0] = deck[random_int];
    //generate new random number not used before
    hand_three[0] = deck[random_int];
    //generate new random number not used before
    hand_four[0] = deck[random_int];
    i++;
}

}
*/

int main(){
  //test later
  return 0;
}
