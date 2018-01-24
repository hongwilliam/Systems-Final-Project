#include "headers.h"

//no 0 indexing for value and suit system because they make calculating card values more confusing while writing code
//value system is 3 as 1, 4 as 2 ... A as 12, 2 as 13
//suit system is diamonds as 1, clubs as 2, ...


//(PART 1) INIIALIZING THE DECK

//purpose: inputs information into a card
//parameters: value and suit of an individual card (refer to comments on top of the file)
void initialize_card(int value, int suit){
  int ranking = (4 * (value - 1)) + suit; //ex: 3 of diamond would be card 1, 3 of club would be card 2, etc
  deck[ranking].value = value;
  deck[ranking].suit = suit;
  deck[ranking].rank = ranking;
  //ex: 5 of clubs (value: 3, suit: 2) -> ranking is (4 * (3-1)) + 2 = 10
}

//purpose: through the deck array to initialize each card's info...
//this sets up the deck in order of increasing value
//parameters: none
void initialize_deck(){
  int card = 1, value = 1, suit = 1;
  while (card < 53){
    while (suit < 5){
        initialize_card(value, suit);
        card++;
        suit++; }
    value++;
    suit = 1;
  }
}

//(PART 2) DISPLAYING CARDS, DEALING THEM OUT, AND SORTING THE HAND

//purpose: print out a card's value and suit (ex: A of Spades)
//this is ugly but necessary for easier testing
//parameters: card's ranking from 1-52
void display_card_ranking(int ranking){
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
  printf("%s \n", s1);
}

//purpose: print out a card's value and suit
//parameters: a card struct from the deck array
void display_card(struct card my_card){
  int card_value = my_card.value;
  int card_suit = my_card.suit;
  int ranking = (4 * (card_value - 1)) + card_suit;
  display_card_ranking(ranking);
}

//purpose: there are 4 hand arrays (represents each player) initialized in the header file
//this inserts a card into a specificed hand array
//parameters: specified hand array, specified index of hand array (1 of 13 cards in the hand),
//and ranking of the card to be inserted into the hand
void set_hand(struct card hand[], int ranking, int index){
  int card_value = deck[ranking].value;
  int card_suit = deck[ranking].suit;
  hand[index].value = card_value;
  hand[index].suit = card_suit;
}

//purpose: there are 4 int arrays initialized in the header meant to store random ints
//each random int distributed to each array corresponds to a card's ranking from 1-52
//parameters: none
void deal_random_ints(){
  int a = 0;
  while (a < 52){
    random_ints[a] = a+1;
    a++; }

  int i = 0;
  srand(time(NULL));

  while (i < 52){
    int temp = random_ints[i];
    int r = rand() % 52; //random index
    random_ints[i] = random_ints[r];
    random_ints[r] = temp;
    i ++;
  }

  /* for testing purposes only
  int k;
  for (k = 0; k< 52; k++){
    printf("%d ", random_ints[k]); } */
}

//QUICKSORT FUNCTIONS BELOW
//purpose: used old quicksort hw from AP CS
//this is to display a dealt hand in increasing order of ranking
void swap(int* a, int* b){
  int temp = *a;
  *a = *b;
  *b = temp; }

int part (int array[], int min, int max){
  int pivot = array[max];
  int i = (min-1);
  int j = min;
  while (j <= max-1){
    if (array[j] <= pivot){
      i++;
      swap(&array[i], &array[j]); }
    j++;
  }

  swap(&array[i+1], &array[max]);
  return (i+1);
}

void quicksort(int array[], int min, int max){
  if (min < max){
    int position = part(array, min, max);
    quicksort(array, min, position-1);
    quicksort(array, position+1, max); }
}

void sort_hand(int hand[]){
  quicksort(hand, 0, 12);
}

//purpose: to distribute the random ints (representing card rankings) to each hand
//then this function converts each int to the corresponding card on the card struct array used for gameplay
//parameters: none
void deal_hands(){
  deal_random_ints();
  //distribute random ints to each of the 4 "hand" arrays
  int i = 0, r = 0;
  while (i < 13){
    rand_hand_one[i] = random_ints[r];
    r++;

    rand_hand_two[i] = random_ints[r];
    r++;

    rand_hand_three[i] = random_ints[r];
    r++;

    rand_hand_four[i] = random_ints[r];
    r++;

    i++; }

  sort_hand(rand_hand_one);
  sort_hand(rand_hand_two);
  sort_hand(rand_hand_three);
  sort_hand(rand_hand_four);

  //this below sorts the hands!
  int j = 0, k = 0;
  while (j < 13){
    set_hand(hand_one, rand_hand_one[k], j);
    set_hand(hand_two, rand_hand_two[k], j);
    set_hand(hand_three, rand_hand_three[k], j);
    set_hand(hand_four, rand_hand_four[k], j);
    k++;
    j++;
  }
}

//purpose: once the deck is shuffled and each hand receieves its cards
//this function displays the cards in each hand, which are in sorted order to make gameplay convenient
void display_hand(struct card hand[]){
  int i = 0;
  while (i < 13){
    display_card(hand[i]);
    i++; }
}

//purpose: the three of diamonds will allow a player to start the game
void check_start(struct card hand[], int ranking, int index)){
  if (hand[index].value = 1 && hand[index].suit = 1){ //if the card's rank is 1, or 3 of diamonds
    // this is where the player should be prompted to player the 3 of Diamonds as a single or with other cards
  }
}

//purpose: once a hand is left with no cards, the player wins
//this function checks if the hand array is empty. Then it will end the game with a print message. Return 1 to end the game. Return 0 will continue the game.
//we want to check if each index of an array is empty. The hand is not shuffled when the player uses cards from whatever index.
int win_condition(struct card hand[]){
  for(int i : hand[13]){
    if (hand[i] = NULL){
      return 1;
      printf("Congratulations");
    }
    else{
      return 0;
    }
  }
}

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

int main(){
  initialize_deck();


  printf("testing shuffling and dealing hands \n");
  deal_hands();

  printf("\nHere is hand one: \n");
  display_hand(hand_one);

  printf("\nHere is hand two: \n");
  display_hand(hand_two);

  printf("\nHere is hand three: \n");
  display_hand(hand_three);

  printf("\nHere is hand four: \n");
  display_hand(hand_four);

  /**
  //note: input card ranking into array index (ex: 3 of diamonds is deck[1])
  //random testing, here is the format to check and compare combos
  printf("checking valid straight (should be 1) %d \n", check_straight(deck[1], deck[6], deck[12], deck[15], deck[17]) );
  printf("checking invalid straight (should be 0) %d \n", check_straight(deck[1], deck[2], deck[7], deck[11], deck[17]) );

  printf("checking valid flush (should be 1) %d \n", check_flush(deck[3], deck[11], deck[15], deck[23], deck[31]) );
  printf("checking invalid flush (should be 0) %d \n", check_flush(deck[3], deck[4], deck[11], deck[15], deck[19]) );

  printf("checking valid house (should be 1) %d \n", check_house(deck[50], deck[51], deck[52], deck[1], deck[4]) );
  printf("checking invalid house (should be 0) %d \n", check_house(deck[1], deck[6], deck[12], deck[15], deck[17]) );

  printf("checking valid bomb (should be 1) %d \n", check_bomb(deck[49], deck[50], deck[51], deck[52], deck[1]) );
  printf("checking invalid bomb (should be 0) %d \n", check_bomb(deck[1], deck[6], deck[12], deck[15], deck[17]) );

  printf("checking valid straight flush (should be 1) %d \n", check_straight_flush(deck[1], deck[5], deck[9], deck[13], deck[17]) );
  printf("checking invalid straight flush (should be 0) %d \n", check_straight_flush(deck[1], deck[2], deck[7], deck[11], deck[17]) );

  printf("comparing two straights (should be -1) %d \n", compare_straight(deck[1], deck[6], deck[9], deck[14], deck[19],
    deck[2], deck[5], deck[10], deck[13], deck[20]) );

  printf("comparing two flushes of different suit (should be 1) %d \n", compare_flush(deck[2], deck[6], deck[10], deck[14], deck[22],
    deck[1], deck[5], deck[9], deck[13], deck[49]) );

  printf("comparing two flushes of same suit (should be 1) %d \n", compare_flush(deck[1], deck[37], deck[41], deck[45], deck[49],
    deck[5], deck[9], deck[13], deck[17], deck[25]) );

  printf("comparing two houses (should be -1) %d \n", compare_house(deck[1], deck[2], deck[3], deck[5], deck[6],
    deck[9], deck[10], deck[11], deck[13], deck[14]) );

  printf("comparing two bombs (should be 1) %d \n", compare_bomb(deck[49], deck[50], deck[51], deck[52], deck[48],
    deck[1], deck[2], deck[3], deck[4], deck[5]) );

  printf("comparing two straight flushes of same suit (should be -1) %d \n", compare_straight_flush(deck[1], deck[5], deck[9], deck[13], deck[17],
    deck[33], deck[37], deck[41], deck[45], deck[49]) );

  printf("comparing two straight flushes of different suit (should be -1) %d \n", compare_straight_flush(deck[33], deck[37], deck[41], deck[45], deck[49],
    deck[2], deck[6], deck[10], deck[14], deck[18]) ); */

  printf("now testing two combos of different type.. (should be 1) %d \n", compare_combo(deck[1], deck[37], deck[41], deck[45], deck[49],
    deck[1], deck[6], deck[9], deck[14], deck[19]));

  printf("now testing two combos of same type.. (should be 1) %d \n", compare_combo(deck[1], deck[37], deck[41], deck[45], deck[49],
    deck[5], deck[9], deck[13], deck[17], deck[25]) );

  printf("now testing to see if function catches invalid combo played (should be 0) %d \n", compare_combo(deck[1], deck[37], deck[41], deck[45], deck[49],
    deck[3], deck[4], deck[5], deck[6], deck[52]) );
}
