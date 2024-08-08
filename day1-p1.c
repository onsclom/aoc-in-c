#include <stdio.h>

int main() {
  // read input from file
  FILE *file = fopen("day1-input", "r");

  int sum = 0;

  // read char by char
  char c;
  char firstDigit = 0;
  char lastDigit = 0;
  while ((c = fgetc(file)) != EOF) {
    if (c >= '0' && c <= '9') {
      if (firstDigit == 0) {
        firstDigit = c;
      }
      lastDigit = c;
    }

    // if \n we finished reading a line
    if (c == '\n') {
      const int rowAmount = (firstDigit - '0') * 10 + (lastDigit - '0');
      if (firstDigit) // if not last line
      {
        sum += rowAmount;
      }
      firstDigit = 0;
      lastDigit = 0;
    }
  }

  printf("Sum: %d\n", sum);
}
