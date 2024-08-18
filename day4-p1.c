// cc day4-p1.c && ./a.out < day4-input
#include <math.h>
#include <stdio.h>

#define FILE_MAX_SIZE 1000000
#define NUMS_MAX 100

typedef struct {
  int winners[NUMS_MAX];
  int winnerCount;
  int nums[NUMS_MAX];
  int numCount;
} card;

int main() {
  char buffer[FILE_MAX_SIZE] = {0};
  unsigned long fileLength = fread(buffer, sizeof(char), FILE_MAX_SIZE, stdin);
  long score = 0;

  size_t curChar = 0;

  while (curChar < fileLength) {
    // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
    // [card]: [winning nums] | [your nums]
    card curCard = {0};

    // "Card"
    curChar += 4;

    // skip until :
    while (buffer[curChar] != ':') {
      curChar++;
    }
    curChar += 1;

    // skip spaces
    while (buffer[curChar] != ' ') {
      curChar++;
    }

    // read winning nums
    while (buffer[curChar] != '|') {
      // read num
      int num = 0;
      while (buffer[curChar] != ' ') {
        num = num * 10 + (buffer[curChar] - '0');
        curChar++;
      }
      curCard.winners[curCard.winnerCount++] = num;

      // " "
      while (buffer[curChar] == ' ') {
        curChar++;
      }
    }

    // "|"
    curChar++;
    while (buffer[curChar] == ' ') {
      curChar++;
    }

    // read your nums
    while (buffer[curChar] != '\n') {
      // read num
      int num = 0;
      while (buffer[curChar] >= '0' && buffer[curChar] <= '9') {
        num = num * 10 + (buffer[curChar] - '0');
        curChar++;
      }
      curCard.nums[curCard.numCount++] = num;

      // " "
      while (buffer[curChar] == ' ') {
        curChar++;
      }
    }

    // check nums against winners
    int winners = 0;
    for (int i = 0; i < curCard.numCount; i++) {
      for (int j = 0; j < curCard.winnerCount; j++) {
        if (curCard.nums[i] == curCard.winners[j]) {
          winners++;
        }
      }
    }

    if (winners > 0) {
      int curScore = pow(2, winners - 1);
      score += curScore;
    }

    curChar++;
  }

  printf("score %ld\n", score);
}
