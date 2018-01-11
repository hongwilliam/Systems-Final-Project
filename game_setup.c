#include "headers.h"

//CODE NOT TESTED YET

//WRITE IDEAS HERE
/**
(1) Each card has a ranking from 0-51, each corresponding in order of increasing value
(2) When dealing cards, the deal function first deals randomly integers from 0-51
(3) Another function then coverts each int into the respective card

*/

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
  set up array of ints from 0-51
  deal each only once and randomly to each of the hands
}
*/

int main(){
  //test later
  return 0;
}
