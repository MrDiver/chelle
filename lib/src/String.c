#include "String.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define WHITE_SPACE " \t\n\r\v\f"

String String_new(char *text) {
  size_t len = strlen(text);
  char *ptr = malloc(sizeof(char) * (len + 1));
  memcpy(ptr, text, sizeof(char) * (len + 1));
  String s = {ptr, len};
  return s;
}

void String_delete(String *this) { free(this->text); }

uint8_t cmp_chr(const char c, const char *cmplst) {
  size_t len = strlen(cmplst);
  for (size_t i = 0; i < len; i++) {
    if (c == cmplst[i]) {
      return 1;
    }
  }
  return 0;
}

void skip_space(String const *str, size_t *pos) {
  skip_any(str, pos, WHITE_SPACE);
}

void skip_any(String const *str, size_t *pos, const char *skipchrs) {
  while (*pos < str->size && cmp_chr(str->text[*pos], skipchrs)) {
    *pos += 1;
  }
}

void find(String const *str, size_t *pos, const char c) {
  while (*pos < str->size && str->text[*pos] != c) {
    *pos += 1;
  }
}

void findany(String const *str, size_t *pos, const char *chrs) {
  while (*pos < str->size && !cmp_chr(str->text[*pos], chrs)) {
    *pos += 1;
  }
}

String *splitatwhite(String const *line, size_t *out_size) {
  return splitat(line, out_size, WHITE_SPACE);
}

String *splitat(String const *line, size_t *out_size, const char *splitchrs) {
  size_t num_args = 10;
  size_t current_arg = 0;
  size_t start = 0, end = 0;

  String *args = malloc(sizeof(String) * num_args);

  skip_space(line, &end);
  while (1) {
    start = end;
    // printf("init:\tstart %lu end %lu diff %lu\n", start, end, end - start);
    findany(line, &end, splitchrs);
    size_t size = end - start;
    // printf("findany:\tstart %lu end %lu diff %lu\n", start, end, end -
    // start);
    args[current_arg].text = malloc(sizeof(char) * (size + 1));
    memcpy(args[current_arg].text, line->text + start, size * sizeof(char));
    args[current_arg].text[size] = '\0';
    args[current_arg].size = size;
    // printf("Found: %s\n", args[current_arg].text);
    current_arg += 1;
    end += 1;
    skip_space(line, &end);

    // printf("skip_space:\tstart %lu end %lu diff %lu\n", start, end, end -
    // start);
    if (end >= line->size) {
      args = realloc(args, sizeof(String) * current_arg);
      *out_size = current_arg;
      return args;
    }
    if (current_arg >= num_args) {
      args = realloc(args, sizeof(String) * (num_args *= 2));
    }
  }
}
