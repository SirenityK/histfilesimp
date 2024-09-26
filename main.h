#include <stdio.h>

#define MAX_LEN 300
#define print_each(arr, size, format)                                          \
  for (int i = 0; i < size; i++)                                               \
  printf(format, arr[i])
#define ERROR(...)                                                             \
  fprintf(stderr, __VA_ARGS__);                                                \
  exit(1)
#define FOPEN(name, path, modes)                                               \
  FILE *name = fopen(path, modes);                                             \
  if (name == NULL) {                                                          \
    ERROR("Failed to read file %s\n", path);                                   \
  }
#define MIN_LINES 100
#define MAX_LINES 10000