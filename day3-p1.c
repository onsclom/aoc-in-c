// run: cc day3-p1.c && ./a.out < day3-input
#include <stdio.h>

#define FILE_MAX_SIZE 1000000

typedef struct {
  char *data;
  unsigned long length;
} s8;

int isSymbolAt(char *buffer, size_t width, size_t height, int x, int y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return 0;
  }
  const char cur = buffer[y * (width+1) + x];
  return cur != '.' && (cur < '0' || cur > '9');
}

int isSymbolTouching(char *buffer, size_t width, size_t height, int x, int y, int len) {
    int touchingSymbol = 0;
    for (int j = 0; j<len; j++) {
      printf("checking %d, %d\n", x+j, y);
      if (
        isSymbolAt(buffer, width, height, x+j, y-1) ||
        isSymbolAt(buffer, width, height, x+j, y+1)
      ) {
        return 1;
      }
    }
    printf("did not find above\n");
    if (
      isSymbolAt(buffer, width, height, x-1, y) ||
      isSymbolAt(buffer, width, height, x-1, y+1) ||
      isSymbolAt(buffer, width, height, x-1, y-1) ||
      isSymbolAt(buffer, width, height, x+len, y) ||
      isSymbolAt(buffer, width, height, x+len, y+1) ||
      isSymbolAt(buffer, width, height, x+len, y-1)
    ) {
      return 1;
    }
    return 0;
}

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

  unsigned long sum = 0;
  for (size_t i = 0; i < fileLength; i++) {
    if (buffer[i] >= '0' && buffer[i] <= '9') {
      int num = 0;
      int len = 0;
      int x = i % (width+1);
      int y = i / (width+1);
      while (buffer[i] >= '0' && buffer[i] <= '9') {
        num = num * 10 + (buffer[i] - '0');
        i++;
        len++;
      }
      if (isSymbolTouching(buffer, width, height, x, y, len)) {
        sum += num;
      }
    }
  }

  printf("sum: %lu\n", sum);
}
