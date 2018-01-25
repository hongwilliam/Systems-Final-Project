#include "headers.h"

//(PART 3) COMPARING SINGLES, DOUBLES, AND 5 CARD COMBOS

//purpose: compare singles played
//parameters: card A and card B
//return -1 if card A < card B, 1 if card A > card B
int compare_single(struct card A, struct card B){
  if (A.rank < B.rank){
    return -1; }
  else{
    return 1; }
}

//purpose: compare doubles played
//parameters: double pair A1-A2 are double pair B1-B2
//return -1 if A1-A2 double < B1-B2 double, 1 if A1-A2 > B1-B2, 0 if invalid input
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

//purpose: check to see if a combo played is a straight (any 5 in a row)
//parameters: input cards ABCDE in increasing order of value
//return 1 if valid, 0 if not
int check_straight(struct card A, struct card B, struct card C, struct card D, struct card E){
  //check if values are incrementing
  if ( ((A.value + 1) == B.value) && ((B.value + 1) == C.value) && ((C.value + 1) == D.value) && ((D.value + 1) == E.value) ){
    return 1; }
  else{
    return 0; }
}

//purpose: check to see if a combo played is a flush (any 5 of a suit)
//parametes: 5 cards ABCDE
//return 1 if valid, 0 if not
int check_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  //not sure if this is right
  if ( (A.suit == B.suit) && (B.suit == C.suit) && (C.suit == D.suit) && (D.suit == E.suit)){
    return 1; }
  else{
    return 0; }
}

//purpose: check to see if a combo played is a house (any triple + double)
//parameters: input ABC as triple (increasing order) and DE as double (increasing order)
//return 1 if valid, 0 if not
int check_house(struct card A, struct card B, struct card C, struct card D, struct card E){
  //check case: does a triple and double exist?
  if ( ((A.value == B.value) && (B.value == C.value)) && (D.value == E.value)){
    return 1; }
  else{
    return 0; }
}

//purpose: check to see if a combo played is a bomb (quadruple + any single)
//parameters: input ABCD as quadruple and E as random single
//return 1 if valid, 0 if not
int check_bomb(struct card A, struct card B, struct card C, struct card D, struct card E){
  if ( (A.value == B.value) && (B.value == C.value)  && (C.value == D.value) ){
    return 1; }
  else{
    return 0; }
}

//purpose: check to see if a combo played is a straight flush (5 cards in increasing order of value with same suit)
//parameters: input cards ABCDE in increasing order of value
//return 1 if valid, 0 if not
int check_straight_flush(struct card A, struct card B, struct card C, struct card D, struct card E){
  //if conditions for both straight and flush are met
  if ( (1 == check_straight(A, B, C, D, E) ) && (1 == check_flush(A, B, C, D, E)) ){
    return 1; }
  else{
    return 0; }
}

//purpose: compare two straights to each other
//parameters: straight of A1, A2, A3, A4, A5 and straight of B1, B2, B3, B4, B5
//return -1 if combo 1 < combo 2, 1 if combo 1 > combo 2, 0 if invalid combo was played
int compare_straight(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5){
  //tie breaker for comparing straights: ranking of card with highest value
  if( (1 == check_straight(A1, A2, A3, A4, A5)) && (1 == check_straight(B1, B2, B3, B4, B5)) ){
    if(A5.rank < B5. rank){
      return -1; }
    else{
      return 1; }
  }
  else{
    return 0; }
}

//purpose: compare two flushes to each other
//parameters: flush of A1, A2, A3, A4, A5 and flush of B1, B2, B3, B4, B5
//return -1 if combo 1 < combo 2, 1 if combo 1 > combo 2, 0 if invalid combo was played
int compare_flush(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5){
  //tie breaker with different suits: higher ranked suit played
  //tie breaker with same suit: ranking of card with highest value
  //priority: (1) suit, then (2) highest ranking card
  if ((1 == check_flush(A1, A2, A3, A4, A5)) && (1 == check_flush(B1, B2, B3, B4, B5)) ){
    if (A5.suit == B5.suit){
      if (A5.rank < B5. rank){
        return -1; }
      else{
        return 1; }
      }

    else{
      if (A5.suit < B5.suit){
        return -1; }
      else{
        return 1; }
    }
  }
  else{
    return 0; }
}

//purpose: compare two houses to each other
//parameters: house of A1, A2, A3, A4, A5 and house of B1, B2, B3, B4, B5
//return -1 if combo 1 < combo 2, 1 if combo 1 > combo 2, 0 if invalid combo was played
int compare_house(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5){
  //tie breaker: higher value of triple duh
  if ((1 == check_house(A1, A2, A3, A4, A5)) && (1 == check_house(B1, B2, B3, B4, B5)) ){
    if (A3.rank < B3.rank){
      return -1; }
    else{
      return 1; }

  }
  else{
    return 0; }
}

//purpose: compare two bombs to each other
//parameters: bomb of A1, A2, A3, A4, A5 and bomb of B1, B2, B3, B4, B5
//return -1 if combo 1 < combo 2, 1 if combo 1 > combo 2, 0 if invalid combo was played
int compare_bomb(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5){
  //tie breaker: higher value of quadruple duh
  if ((1 == check_bomb(A1, A2, A3, A4, A5)) && (1 == check_bomb(B1, B2, B3, B4, B5)) ){
    if (A4.rank < B4.rank){
      return -1; }
    else{
      return 1; }
  }
  else{
    return 0; }
}

//purpose: compare two straight flushes to each other
//parameters: straight flush of A1, A2, A3, A4, A5 and straight flush of B1, B2, B3, B4, B5
//return -1 if combo 1 < combo 2, 1 if combo 1 > combo 2, 0 if invalid combo was played
int compare_straight_flush(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5){
  //tie breaker: just use compare flush; same tie breakers as flush (suit gets precedent, then highest ranking card)
  if ((1 == check_straight_flush(A1, A2, A3, A4, A5)) && (1 == check_straight_flush(B1, B2, B3, B4, B5)) ){
    return compare_flush(A1, A2, A3, A4, A5, B1, B2, B3, B4, B5); }
  else{
    return 0; }
}

//purpose: identify what kind of combo is played
//parameters: 5 cards of ABCDE
//returns 0 = invalid, 1 = straight, 2 = flush, 3 = house, 4 = bomb, 5 = straight flush
int identify_combo(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5){
  if (check_straight_flush(A1, A2, A3, A4, A5) == 1){
    return 5; }
  else{
    if (check_bomb(A1, A2, A3, A4, A5) == 1){
      return 4; }
    else{
      if (check_house(A1, A2, A3, A4, A5) == 1){
        return 3; }
      else{
        if (check_flush(A1, A2, A3, A4, A5) == 1){
          return 2; }
        else{
          if (check_straight(A1, A2, A3, A4, A5) == 1){
            return 1; }
          else{
            return 0; }
        }
      }
    }
  }
}

//VERY IMPORTANT
//purpose: compare two combos to each other, regardless of what type they are
//parameters: combo A1, A2, A3, A4, A5 and combo B1, B2, B3, B4, B5
//return -1 if combo A < combo B, 1 if A > B, 0 if invalid combo was played
int compare_combo(struct card A1, struct card A2, struct card A3, struct card A4, struct card A5,
  struct card B1, struct card B2, struct card B3, struct card B4, struct card B5){
    int A_combo_power = identify_combo(A1, A2, A3, A4, A5), B_combo_power = identify_combo(B1, B2, B3, B4, B5);
    if ( (A_combo_power == 0) || (B_combo_power == 0)){
      return 0; }
    else{
      if (A_combo_power < B_combo_power){
        return -1; }
      else{
        if (A_combo_power > B_combo_power){
          return 1; }
        else{
          if ( (A_combo_power == 5) && (B_combo_power == 5) ){
            return compare_straight_flush(A1, A2, A3, A4, A5, B1, B2, B3, B4, B5); }
          else{
            if ( (A_combo_power == 4) && (B_combo_power == 4) ){
              return compare_bomb(A1, A2, A3, A4, A5, B1, B2, B3, B4, B5); }
            else{
              if ( (A_combo_power == 3) && (B_combo_power == 3) ){
                return compare_house(A1, A2, A3, A4, A5, B1, B2, B3, B4, B5); }
              else{
                if ( (A_combo_power == 2) && (B_combo_power == 2) ){
                  return compare_flush(A1, A2, A3, A4, A5, B1, B2, B3, B4, B5); }
                else{
                    return compare_straight(A1, A2, A3, A4, A5, B1, B2, B3, B4, B5); }
                  }
                }
              }
            }
          }
        }
}
