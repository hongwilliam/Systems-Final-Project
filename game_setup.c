#include "headers.h"

//no 0 indexing for value and suit system because they make calculating card values more confusing while writing code
//value system is 3 as 1, 4 as 2 ... A as 12, 2 as 13
//suit system is diamonds as 1, clubs as 2, ...

//WRITE IDEAS HERE
/**
(1) Each card has a ranking from 1-52, each corresponding in order of increasing value (no 0 indexing to make calculations easier)
(2) When dealing cards, the deal function first deals randomly integers from 1-52
(3) Another function then converts each int into the respective card
*/


//inputs information into a card
//this sets up the deck in order of increasing value
//return type void
void initialize_card(int value, int suit){
  int ranking = (4 * (value - 1)) + suit; //ex: 3 of diamond would be card 1, 3 of club would be card 2, etc
  deck[ranking].value = value;
  deck[ranking].suit = suit;
  //ex: 5 of clubs (value: 3, suit: 2) -> ranking is (4 * (3-1)) + 2 = 10
  //work on adding name later for display only
}

// return type void
void initialize_deck(){
  int card = 1, value = 1, suit = 1;
  while (card < 52){
    while (suit < 4){
        initialize_card(value, suit);
        card++;
        suit++; }
    value++;
    suit = 1;
  }
}

//this is ugly but necessary for easier testing
void display_card(int ranking){
  int card_value = deck[ranking].value;
  int card_suit = deck[ranking].suit;

  char s1[16]; //value
  char s2[16]; //suit
  if (card_value == 1){strcpy(s1, "3 of "); }
  if (card_value == 2){strcpy(s1, "4 of "); }
  if (card_value == 3){strcpy(s1, "5 of "); }
  if (card_value == 4){strcpy(s1, "6 of "); }
  if (card_value == 5){strcpy(s1, "7 of "); }
  if (card_value == 6){strcpy(s1, "8 of "); }
  if (card_value == 7){strcpy(s1, "9 of "); }
  if (card_value == 8){strcpy(s1, "10 of "); }
  if (card_value == 9){strcpy(s1, "J of "); }
  if (card_value == 10){strcpy(s1, "Q of "); }
  if (card_value == 11){strcpy(s1, "K of "); }
  if (card_value == 12){strcpy(s1, "A of "); }
  if (card_value == 13){strcpy(s1, "2 of "); }

  if (card_suit == 1){strcpy(s2, "Diamonds"); }
  if (card_suit == 2){strcpy(s2, "Clubs"); }
  if (card_suit == 3){strcpy(s2, "Hearts"); }
  if (card_suit == 4){strcpy(s2, "Spades"); }

  strcat(s1, s2);
  printf("Card: %s \n", s1);
}

//struct card deal_card();
//struct card deal_hands();

//pseudo code only
/**
void deal_hands(){
  set up array of ints from 0-51
  deal each only once and randomly to each of the hands
}
*/

int main(){
  //test later
  initialize_deck();
  display_card(5);
  display_card(27);
  display_card(1);
}
