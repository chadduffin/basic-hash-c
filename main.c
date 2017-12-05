#include <stdio.h>
#include <stdarg.h>

#define R 0x1B  // small prime (29) used for hashing strings
#define M 0x3FB // large prime (1019) used as the hashtable size

int hash_integer(int integer);
int hash_sequence(int count, ...);
int hash_string(char *string, int len);

int main(int argc, char **argv) {
  char *hashtable[M] = { NULL };

  printf("hash_string(\"hello\", 5): %i.\n", hash_string("hello", 5));
  printf("hash_string(\"bye\", 3): %i.\n", hash_string("bye", 3));

  printf("hash_integer(124124): %i.\n", hash_integer(124124));
  printf("hash_integer(594392): %i.\n", hash_integer(594392));
  printf("hash_integer(231837): %i.\n", hash_integer(231837));

  printf("hash_sequence(124124, 594392, 231837): %i.\n", hash_sequence(3, 124124, 594392, 231837));

  return 0;
}

int hash_integer(int integer) {
  return (integer % M);
}

int hash_sequence(int count, ...) {
  int hash = 0;
  va_list list;

  va_start(list, count);

  for (int i = 0; i < count; i++) {
    hash = (R * hash + va_arg(list, int)) % M;
  }

  va_end(list);

  return hash;
}

int hash_string(char *string, int len) {
  int hash = 0;

  for (int i = 0; i < len; i++) {
    hash = (R * hash + string[i]) % M;
  }

  return hash;
}

