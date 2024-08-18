// cc day3-p2.c && ./a.out < day3-input
#include <stdio.h>

#define FILE_MAX_SIZE 1000000

typedef struct {
  char *data;
  unsigned long length;
} s8;

typedef struct {
  int num;
  int x;
  int y;
  int len;
} num;

int main() {
  char buffer[FILE_MAX_SIZE] = {0};
  unsigned long fileLength = fread(buffer, sizeof(char), FILE_MAX_SIZE, stdin);

  size_t width = 0;
  size_t height = 0;
  for (size_t i = 0; i < fileLength; i++) {
    if (buffer[i] == '\n') {
      height++;
    }
    else if (height == 0) {
      width++;
    }
  }

  num nums[100000] = {0};
  size_t numCount = 0;

  for (size_t i = 0; i < fileLength; i++) {
    if (buffer[i] >= '0' && buffer[i] <= '9') {
      num *n = &nums[numCount++];
      n->x = i % (width+1);
      n->y = i / (width+1);

      while (buffer[i] >= '0' && buffer[i] <= '9') {
        n->num = n->num * 10 + (buffer[i] - '0');
        i++;
        n->len++;
      }
    }
  }

  unsigned long sum = 0;
  for (size_t i = 0; i < fileLength; i++) {
    if (buffer[i] == '*') {
      int x = i % (width+1);
      int y = i / (width+1);
      int amountTouching = 0;
      int gearRatio = 1;
      for (size_t j = 0; j < numCount; j++) {
        num n = nums[j];
        if (
          x >= n.x-1 && x <= n.x + n.len && y >= n.y-1 && y <= n.y + 1
        ) {
          amountTouching++;
          gearRatio *= n.num;
        }
      }
      if (amountTouching == 2) {
        sum += gearRatio;
      }
    }
  }

  printf("sum: %lu\n", sum);
}
