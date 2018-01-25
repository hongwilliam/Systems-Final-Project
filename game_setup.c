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

//purpose: print out a card's value and suit (ex: A of Spades) based on ranking
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

//purpose: print out a card's value and suit based on a struct card
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
    a++;
  }

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
  *b = temp;
}

int part (int array[], int min, int max){
  int pivot = array[max];
  int i = (min-1);
  int j = min;
  while (j <= max-1){
    if (array[j] <= pivot){
      i++;
      swap(&array[i], &array[j]);
    }
    j++;
  }

  swap(&array[i+1], &array[max]);
  return (i+1);
}

void quicksort(int array[], int min, int max){
  if (min < max){
    int position = part(array, min, max);
    quicksort(array, min, position-1);
    quicksort(array, position+1, max);
  }
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
    i++;
  }
}

//(PART 4) DEALING WITH GAMEPLAY MECHANICS (TURNS, ETC)

//purpose: the three of diamonds will allow a player to start the game
//returns: the id of the player whose turn it now is
int check_start(){
  if (hand_one[0].rank == 1){
    current_turn = 1; //1 indicates that it is currently that player's turn
    printf("\nPlayer 1 will begin the game! \n");
    return 1;
  }
  if (hand_two[0].rank == 1){
    current_turn = 2;
    printf("\nPlayer 2 will begin the game! \n");
    return 2;
  }
  if (hand_three[0].rank == 1){
    current_turn = 3;
    printf("\nPlayer 3 will begin the game! \n");
    return 3;
  }
  if (hand_four[0].rank == 1){
    current_turn = 4;
    printf("\nPlayer 4 will begin the game! \n");
    return 4;
  }
  return -1;
}

/**
//purpose: once a hand is left with no cards, the player wins
//this function checks if the hand array is empty. Then it will end the game with a print message. Return 1 to end the game. Return 0 will continue the game.
//we want to check if each index of an array is empty. The hand is not shuffled when the player uses cards from whatever index.
int check_win_condition(struct card hand[]){
  for(int i; i < 13; i++){
    //remember to add function to remove cards from hands
    if (hand[i] == NULL){
      return 1;
      win_condition = 1;
      printf("Congratulations");
    }
    else{
      return 0;
    }
  }
} */

//purpose: take a player's input as to what kind of cards he wants to play on his free
// void process_input_free(char * line){
//   if (strncmp(line, "single", sizeof(line)) == 0){
//     card_type = 0;
//     printf("\nCard type set as single until next free\n"); }
//   else{
//     if (strncmp(line, "double", sizeof(line)) == 0){
//       card_type = 1;
//       printf("\nCard type set as double until next free\n"); }
//     else{
//       if (strncmp(line, "combo", sizeof(line)) == 0){
//         card_type = 2;
//         printf("\nCard type set as combo until next free\n"); }
//       else{
//         printf("\nInvalid card type played, please enter: single, double, or combo\n"); }
//     }
//   }
// }


int main(){
  initialize_deck();

  printf("testing shuffling and dealing hands \n");
  deal_hands();

  // char input[1024];
  // while (1){
  //   printf("Anthony and William's Excellent Shell:" );
  //   fgets(input, 1024, stdin);
  //
  //   //insert terminating null into end of command
  //   *strchr(input, '\n') = 0;
  //
  //   if (strncmp(input, "exit", sizeof(input)) != 0){
  //     process_input_free(input); }
  //   else{
  //     exit(0); //exit the shell if user typed in exit
  //   }
  // }

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
    deck[2], deck[6], deck[10], deck[14], deck[18]) );
  printf("now testing two combos of different type.. (should be 1) %d \n", compare_combo(deck[1], deck[37], deck[41], deck[45], deck[49],
    deck[1], deck[6], deck[9], deck[14], deck[19]));
  printf("now testing two combos of same type.. (should be 1) %d \n", compare_combo(deck[1], deck[37], deck[41], deck[45], deck[49],
    deck[5], deck[9], deck[13], deck[17], deck[25]) );
  printf("now testing to see if function catches invalid combo played (should be 0) %d \n", compare_combo(deck[1], deck[37], deck[41], deck[45], deck[49],
    deck[3], deck[4], deck[5], deck[6], deck[52]) ); */
  return 0;
}
