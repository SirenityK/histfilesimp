#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 1024
#define HISTFILE "/.histfile"
#define HISTFILE_BACK HISTFILE ".bak"

unsigned int countlines(FILE *file) {
  char buf_data[BUF];
  unsigned int counter = 0;

  rewind(file);

  size_t res;
  while ((res = fread(buf_data, 1, BUF, file)) > 0) {
    for (int i = 0; i < res; i++) {
      if (buf_data[i] == '\n')
        counter++;
    }
  }
  if (ferror(file)) {
    ERROR("Error reading file");
  }

  return counter;
}

int is_in(char strings[MAX_LINES][MAX_LEN], int str_size, char *match) {
  if (str_size == 0) {
    return -1;
  }
  for (int i = 0; i < str_size; i++) {
    if (strcmp(strings[i], match) == 0) {
      return i;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  char *home_path = getenv("HOME");
  size_t hpl = strlen(home_path);
  // allocate history file along with a backup
  char *hpath = (char *)malloc(hpl + strlen(HISTFILE) + 1);
  strcpy(hpath, home_path);
  strcat(hpath, HISTFILE);

  char *bpath = (char *)malloc(hpl + strlen(HISTFILE_BACK) + 1);
  strcpy(bpath, home_path);
  strcat(bpath, HISTFILE_BACK);

  // open files and write
  FOPEN(fptr, hpath, "r");
  // free(hpath);
  FOPEN(bptr, bpath, "w");
  free(bpath);

  char text[MAX_LEN];

  while (fgets(text, MAX_LEN, fptr)) {
    fputs(text, bptr);
  }
  fclose(bptr);

  // Optimize histfile
  int num_lines = countlines(fptr);

  char unique[num_lines][MAX_LEN];
  int len = 0;

  fseek(fptr, 0, SEEK_SET);
  int pos;
  while (fgets(text, MAX_LEN, fptr)) {
    pos = is_in(unique, len, text);
    if (pos == -1) {
      strcpy(unique[len], text);
      len++;
    }
  }
  fclose(fptr);

  FOPEN(file, hpath, "w");
  for (int i = 0; i < len; i++) {
    fputs(unique[i], file);
  }
  fclose(file);
  free(hpath);

  printf("History file optimized\n");

  return 0;
}
