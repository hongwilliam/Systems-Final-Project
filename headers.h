#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>

struct card{
  int value; //3 equals 0, 4 equals 1, etc
  int suit; //diamonds = 0, clubs = 1, etc
  char name[256]; //"3 of Diamonds", etc
};
