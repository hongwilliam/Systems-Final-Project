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

//have one big "compare combo" function that combines all the 5 below later

//ASSUMPTION: each card inputted goes in increasing ranking !!!!



//any 5 in a row
//return 1 if valid, 0 if not
int check_straight(struct card A, struct card B, struct card C, struct card D, struct card E){
  //tie breaker for comparing straights: ranking of card with highest value
  int AB = B.rank - A.rank, BC = C.rank - B.rank, CD = D.rank - C.rank, DE = E.rank - D.rank;
  if ( (4 <= AB <= 7) && (4 <= BC <= 7) && (4 <= CD <= 7) && (4 <= DE <= 7) ){
    return 1; }
  else{
    return 0; }
}

//any 5 of a suit
//return 1 if valid, 0 if not
int check_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  //tie breaker with same suit: ranking of card with highest value
  //tie breaker with different suits: higher ranked suit played

  //not sure if this is right
  if (A.suit == B.suit == C.suit == D.suit == E.suit){
    return 1; }
  else{
    return 0;
  }

}

//any triple + double
//input ABC as triple and DE as double
//return 1 if valid, 0 if not
int check_house(struct card A, struct card B, struct card C, struct card D, struct card E){
  //check case: does a triple and double exist?
  if ((A.value == B.value == C.value) && (D.value == E.value)){
    return 1; }
  else{
    return 0; }
  //tie breaker: higher value of triple duh
}

//4 of a kind and any 1 random card
//input ABCD as quadruple
//return 1 if valid, 0 if not
int check_bomb(struct card A, struct card B, struct card C, struct card D, struct card E){
  if (A.value == B.value == C.value == D.value){
    return 1; }
  else{
    return 0; }
  //tie breaker: higher value of quadruple duh
}

//5 in a row with same suit
//return 1 if valid, 0 if not
int check_straight_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  if (1 == check_straight(A, B, C, D, E) == check_flush(A, B, C, D, E)){
    return 1; }
  else{
    return 0; }
}
