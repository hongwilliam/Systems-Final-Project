#include "headers.h"

//WE WORK WITH CARD RANKINGS FROM 1-52
typedef int bool;
#define true 1
#define false 0

//ADD COMPARING SINGLES AND DOUBLES LATER (should be easy)
//below is pseudo code only for 5 card combos!

//ADD ARGUMENTS FOR EACH FUNCTION LATER
//any 5 in a row
bool check_straight(){
  //are the rankings increasing in order of value?
  //^ use card.value to retrieve value (1, 2, 3, 4, ...)
  //tie breaker: ranking of card with highest value
}

//any 5 of a suit
bool check_flush(){
  //do the cards share the same "divisbility" by 4?
  //diamonds -> 1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49
  //clubs -> 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50
  //hearts -> 3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51
  //spades -> 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52
  //tie breaker with same suit: ranking of card with highest value
  //tie breaker with different suits: higher ranked suit played
}

//any triple + double
bool check_house(){
  //check case 1: does a triple exist?
  /** idea: values are clustered around certain rankings...
  ex: 3s are between 1-4, 4s are between 5-8, etc...
  check if all possible 3 card combinations of a set of 4 exists */

  //check case 2: does a double exist?
  //tie breaker: higher value of triple duh
}

//4 of a kind and any 1 random card
bool check_bomb(){
  //use same idea for checking triples and doubles... clustered rankings
  //tie breaker: higher value of quadruple duh
}

//5 in a row with same suit
bool check_straight_flush(){
  //if (check_straight() && check_flush()
}
