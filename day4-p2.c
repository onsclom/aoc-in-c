// cc day4-p2.c && ./a.out < day4-input
#include <math.h>
#include <stdio.h>

#define FILE_MAX_SIZE 1000000
#define NUMS_MAX 100
#define CARDS_MAX 1000

typedef struct {
  int winners[NUMS_MAX];
  int winnerCount;
  int nums[NUMS_MAX];
  int numCount;
  int matching;
  unsigned long copies;
} card;

int main() {
  char buffer[FILE_MAX_SIZE] = {0};
  unsigned long fileLength = fread(buffer, sizeof(char), FILE_MAX_SIZE, stdin);

  size_t curChar = 0;
  card cards[CARDS_MAX] = {0};
  size_t cardAmount = 0;

  while (curChar < fileLength) {
    card *curCard = &cards[cardAmount++];

    // "Card"
    curChar += 4;
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
      curCard->winners[curCard->winnerCount++] = num;
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
      curCard->nums[curCard->numCount++] = num;
      // " "
      while (buffer[curChar] == ' ') {
        curChar++;
      }
    }

    // check nums against winners
    int winners = 0;
    for (int i = 0; i < curCard->numCount; i++) {
      for (int j = 0; j < curCard->winnerCount; j++) {
        if (curCard->nums[i] == curCard->winners[j]) {
          curCard->matching++;
        }
      }
    }
    curChar++;
  }

  unsigned long score = 0;
  unsigned long cardCount = 0;

  for (size_t i = 0; i < cardAmount; i++) {
    card *curCard = &cards[i];
    curCard->copies += 1; // og copy
    for (size_t j = 0; j < curCard->matching && j + i + 1 < cardAmount; j++) {
      cards[i + j + 1].copies += curCard->copies;
    }
    cardCount += curCard->copies;
  }

  printf("totalTotal %ld\n", cardCount);
}
