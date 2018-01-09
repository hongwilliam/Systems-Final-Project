#include "headers.h"

//CODE NOT TESTED YET
//PROB LOT OF SYNTAX ERRORS, PLZ FIX IF YOU CAN
//If you have better/efficient ways, feel free to delete some stuff


struct card deck[52];
struct card hand_one[13]; //assuming 4 player game
struct card hand_two[13];
struct card hand_three[13];
struct card hand_four[13];

//inputs information into a card
//this sets up the deck in order of increasing value
//return type void
void initialize_card(int value, int suit){
  int ranking = (num % 4) + suit; //ex: 3 of diamond would be card 0, 3 of club would be card 1, etc
  deck[ranking]->value = value;
  deck[ranking]->suit = suit;
  //work on adding name later
}

// return type void
void initialize_deck(){
  int card = 0, value = 0, suit = 0;
  while (card < 52){
    while (suit < 3){
        deck[card]->value =
      initialize_card(value,suit);
      suit++; }
    value++;
    suit = 0;
    card++;
  }
}

struct card deal_card();

struct card deal_hands();

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
*/

int main(){
  //test later
  return 0;
}
