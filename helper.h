#include <string.h>

typedef struct {
  char *data;
  unsigned long length;
} s8;

s8 s8_from_cstr(const char *cstr) {
  s8 result = {0};
  result.data = (char *)cstr;
  result.length = strlen(cstr);
  return result;
}
