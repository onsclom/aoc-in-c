// run: cc day2-p2.c && ./a.out < day2-input

#include <stdio.h>

#define FILE_MAX_SIZE 1000000

typedef struct {
  unsigned int red;
  unsigned int green;
  unsigned int blue;
} bag;

int main() {
  char buffer[FILE_MAX_SIZE] = {0};
  unsigned long fileLength = fread(buffer, sizeof(char), FILE_MAX_SIZE, stdin);

  unsigned long sum = 0;
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
    // char works = 1;
    bag minBag = { 0 };
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

      if (requiredBag.red > minBag.red) {
        minBag.red = requiredBag.red;
      }
      if (requiredBag.green > minBag.green) {
        minBag.green = requiredBag.green;
      }
      if (requiredBag.blue > minBag.blue) {
        minBag.blue = requiredBag.blue;
      }
    }
    sum += minBag.red * minBag.green * minBag.blue;
    i++;
  }

  printf("idSums: %lu\n", sum);
}
