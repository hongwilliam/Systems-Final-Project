#include "headers.h"

//WE WORK WITH CARD RANKINGS FROM 1-52
//there should be "choose cards in hand" function

//return -1 if card A < card B, 1 if card A > card B
int compare_single(struct card A, struct card B){
  if (A.rank < B.rank){
    return -1; }
  else{
    return 1; }
}

//return -1 if A1-A2 double < B1-B2 double, 1 if A1-A2 > B1-B2, 0 if not valid input
int compare_double(struct card A1, struct card A2, struct card B1, struct card B2){
  //first, check if A1-A2 and B1-B2 are valid double pairs
  if (A1.value != A2.value || B1.value != B2.value){
    return 0; }

  //then the "value" of the double is the value of its highest ranking single
  //compare the highest ranking single from each double
  int higher_A, higher_B;
  if (compare_single(A1, A2) == -1){
    higher_A = A2.value; }
  else{
    higher_A = A1.value; }

  if (compare_single(B1, B2) == -1){
    higher_B = B2.value; }
  else{
    higher_B = B1.value; }

  if (higher_A < higher_B){
    return -1; }
  else{
    return 1; }
}

//have one big "compare combo" function that combines all the 5 below

//any 5 in a row
int check_straight(struct card A, struct card B, struct card C, struct card D, struct card E){
  //are the rankings increasing in order of value?
  //^ use card.value to retrieve value (1, 2, 3, 4, ...)
  //tie breaker: ranking of card with highest value
}

//any 5 of a suit
int check_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  //do the cards share the same "divisbility" by 4?
  //diamonds -> 1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49
  //clubs -> 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50
  //hearts -> 3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51
  //spades -> 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52
  //tie breaker with same suit: ranking of card with highest value
  //tie breaker with different suits: higher ranked suit played
}

//any triple + double
int check_house(struct card A, struct card B, struct card C, struct card D, struct card E){
  //check case 1: does a triple exist?
  /** idea: values are clustered around certain rankings...
  ex: 3s are between 1-4, 4s are between 5-8, etc...
  check if all possible 3 card combinations of a set of 4 exists */

  //check case 2: does a double exist?
  //tie breaker: higher value of triple duh
}

//4 of a kind and any 1 random card
int check_bomb(struct card A, struct card B, struct card C, struct card D, struct card E){
  //use same idea for checking triples and doubles... clustered rankings
  //tie breaker: higher value of quadruple duh
}

//5 in a row with same suit
int check_straight_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  //if (check_straight() && check_flush()
}
