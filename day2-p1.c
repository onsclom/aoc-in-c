// run: cc day2-p1.c && ./a.out < day2-input

#include <stdio.h>

#define FILE_MAX_SIZE 1000000

typedef struct {
  char *data;
  unsigned long length;
} s8;

typedef struct {
  unsigned int red;
  unsigned int green;
  unsigned int blue;
} bag;

int main() {
  char buffer[FILE_MAX_SIZE] = {0};
  unsigned long fileLength = fread(buffer, sizeof(char), FILE_MAX_SIZE, stdin);

  unsigned long idSums = 0;
  size_t i = 0;
  while (buffer[i] != 0) {
    i += 5; // "Game "
    // parse game num
    unsigned int gameNum = 0;
    while (buffer[i] >= '0' && buffer[i] <= '9') {
      gameNum = gameNum * 10 + (buffer[i] - '0');
      i++;
    }

    i+=2; // ": "
    char works = 1;
    while (buffer[i] != '\n') {
      if (buffer[i] == ';') {
        i+=2; // "; "
      }

      bag requiredBag = { 0 };
      while (buffer[i] != ';' && buffer[i] != '\n') {
        if (buffer[i] == ',') {
          i+=2; // ", "
        }

        unsigned int marbleAmount = 0;
        while (buffer[i] >= '0' && buffer[i] <= '9') {
          marbleAmount = marbleAmount * 10 + (buffer[i] - '0');
          i++;
        }
        i++; // " "

        if (buffer[i] == 'r') {
          requiredBag.red += marbleAmount;
          i += 3; // "red"
        } else if (buffer[i] == 'g') {
          requiredBag.green += marbleAmount;
          i += 5; // "green"
        } else if (buffer[i] == 'b') {
          requiredBag.blue += marbleAmount;
          i += 4; // "blue"
        }
      }
      if (
        requiredBag.red > 12 ||
        requiredBag.green > 13 ||
        requiredBag.blue > 14
      ) {
        works = 0;
      }
    }
    if (works == 1) {
      idSums += gameNum;
    }
    i++;
  }

  printf("idSums: %lu\n", idSums);
}
