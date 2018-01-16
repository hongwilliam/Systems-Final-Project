#include "headers.h"

//no 0 indexing for value and suit system because they make calculating card values more confusing while writing code
//value system is 3 as 1, 4 as 2 ... A as 12, 2 as 13
//suit system is diamonds as 1, clubs as 2, ...

//(1) INIIALIZING FUNCTIONS
//inputs information into a card
//this sets up the deck in order of increasing value
//return type void
void initialize_card(int value, int suit){
  int ranking = (4 * (value - 1)) + suit; //ex: 3 of diamond would be card 1, 3 of club would be card 2, etc
  deck[ranking].value = value;
  deck[ranking].suit = suit;
  //ex: 5 of clubs (value: 3, suit: 2) -> ranking is (4 * (3-1)) + 2 = 10
}

// return type void
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

//this is ugly but necessary for easier testing
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

void display_card(struct card my_card){
  int card_value = my_card.value;
  int card_suit = my_card.suit;
  int ranking = (4 * (card_value - 1)) + card_suit;
  display_card_ranking(ranking);
}

//sets the value of the a card in a hand
void set_hand(struct card hand[], int ranking, int index){
  int card_value = deck[ranking].value;
  int card_suit = deck[ranking].suit;
  hand[index].value = card_value;
  hand[index].suit = card_suit;
}

//shoutout to stack overflow for providing useful info
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

void deal_hands(){
  deal_random_ints();
  //distribute random ints to each of the 4 "hand" arrays
  int i = 0, r = 0;
  while (i < 13){
    set_hand(hand_one, random_ints[r], i);
    rand_hand_one[i] = random_ints[r]; //for testing purposes only
    r++;

    set_hand(hand_two, random_ints[r], i);
    rand_hand_two[i] = random_ints[r];
    r++;

    set_hand(hand_three, random_ints[r], i);
    rand_hand_three[i] = random_ints[r];
    r++;

    set_hand(hand_four, random_ints[r], i);
    rand_hand_four[i] = random_ints[r];
    r++;

    i++; }
}

void display_hand(struct card hand[]){
  int i = 0;
  while (i < 13){
    display_card(hand[i]);
    i++; }
}

void display_ints(int hand[]){
  printf("Here is a hand\n");
  int i = 0;
  while (i < 13){
    printf("%d \n", hand[i]);
    i++; }
  printf("\n");
}

//used old quicksort hw from AP CS lol
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


int main(){
  initialize_deck();
  printf("\ntesting card ranking 34 (J of Clubs) \n");
  display_card_ranking(34);

  printf("testing card ranking 45 (A of diamonds) \n");
  display_card_ranking(45);

  printf("testing card ranking 18 (7 of clubs) \n");
  display_card_ranking(18);

  printf("testing card ranking 48 (A of spades) \n");
  display_card_ranking(48);
  printf("\n");

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

  sort_hand(rand_hand_one);
  sort_hand(rand_hand_two);
  sort_hand(rand_hand_three);
  sort_hand(rand_hand_four);

  display_ints(rand_hand_one);
  display_ints(rand_hand_two);
  display_ints(rand_hand_three);
  display_ints(rand_hand_four);


}
