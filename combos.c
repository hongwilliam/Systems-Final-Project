#include "headers.h"

//WORK WITH CARD RANKINGS FROM 1-52
//to add later: there should be "choose cards in hand" function
//to add later: have one big "compare combo" function that combines all the 5 below

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
    higher_A = A2.rank; }
  else{
    higher_A = A1.rank; }

  if (compare_single(B1, B2) == -1){
    higher_B = B2.rank; }
  else{
    higher_B = B1.rank; }

  if (higher_A < higher_B){
    return -1; }
  else{
    return 1; }
}


//input ABCDE in increasing order
//any 5 in a row
//return 1 if valid, 0 if not
int check_straight(struct card A, struct card B, struct card C, struct card D, struct card E){
  //check if values are incrementing
  if ( ((A.value + 1) == B.value) && ((B.value + 1) == C.value) && ((C.value + 1) == D.value) && ((D.value + 1) == E.value) ){
    return 1; }
  else{
    return 0; }
}

//any 5 of a suit
//return 1 if valid, 0 if not
int check_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  //not sure if this is right
  if ( (A.suit == B.suit) && (B.suit == C.suit) && (C.suit == D.suit) && (D.suit == E.suit)){
    return 1; }
  else{
    return 0; }
}

//input ABC as triple (increasing order) and DE as double (increasing order)
//any triple + double
//return 1 if valid, 0 if not
int check_house(struct card A, struct card B, struct card C, struct card D, struct card E){
  //check case: does a triple and double exist?
  if ( ((A.value == B.value) && (B.value == C.value)) && (D.value == E.value)){
    return 1; }
  else{
    return 0; }
}

//input ABCD as quadruple (increasing order)
//4 of a kind and any 1 random card
//return 1 if valid, 0 if not
int check_bomb(struct card A, struct card B, struct card C, struct card D, struct card E){
  if ( (A.value == B.value) && (B.value == C.value)  && (C.value == D.value) ){
    return 1; }
  else{
    return 0; }
  //tie breaker: higher value of quadruple duh
}

//5 in a row with same suit
//return 1 if valid, 0 if not
int check_straight_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  //if conditions for both straight and flush are met
  if ( (1 == check_straight(A, B, C, D, E) ) && (1 == check_flush(A, B, C, D, E)) ){
    return 1; }
  else{
    return 0; }
}

//FILL IN LATER

//first, check if the combos are valid using the check functions
//return -1 if combo 1 < combo 2, 1 if combo 1 > combo 2
int compare_straight(){
  //tie breaker for comparing straights: ranking of card with highest value
}

int compare_flush(){
  //tie breaker with same suit: ranking of card with highest value
  //tie breaker with different suits: higher ranked suit played
}

int compare_house(){
  //tie breaker: higher value of triple duh
}

int compare_bomb(){
  //tie breaker: higher value of quadruple duh
}

int compare_straight_flush(){
  //tie breaker: ranking of card with highest value
}
