// run: cc day1-p2.c && ./a.out < day1-input

#include <stdio.h>
#include <string.h>

#define FILE_MAX_SIZE 1000000

typedef struct {
  char *data;
  unsigned long length;
} s8;

int main() {
  char buffer[FILE_MAX_SIZE] = {0};
  unsigned long fileLength = fread(buffer, sizeof(char), FILE_MAX_SIZE, stdin);

  int sum = 0;
  {
    char c = 0;
    unsigned int i = 0;
    char firstDigit = 0;
    char lastDigit = 0;
    while ((c = buffer[i++]) != EOF) {
      if (c >= '0' && c <= '9') {
        if (firstDigit == 0) {
          firstDigit = c;
        }
        lastDigit = c;
      }
      else if (c == '\n') {
        const int rowAmount = (firstDigit - '0') * 10 + (lastDigit - '0');
        if (firstDigit) {
          sum += rowAmount;
        }
        firstDigit = 0;
        lastDigit = 0;
      }
      else {
        char *digitStrings[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
        int digitLengths[] = { 4, 3, 3, 5, 4, 4, 3, 5, 5, 4 };
        for (int j = 0; j < 10; j++) {
          if (
            memcmp(
              buffer + i - 1,
              digitStrings[j],
              digitLengths[j]
            ) == 0
          ) {
            if (firstDigit == 0) {
              firstDigit = j + '0';
            }
            lastDigit = j + '0';
            break;
          }
        }
      }
    }
  }

  printf("answer: %d\n", sum);
}
