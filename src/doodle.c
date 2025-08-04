
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

const char *readline() {
  uint32_t size = 4096;
  char *buf = malloc(size * sizeof(char));
  uint32_t pos = 0;
  for (int c; (c = getc(stdin)) != EOF;) {
    buf[pos] = c;
    pos++;
    if (pos >= size) {
      buf = realloc(buf, size *= 2);
    }
  }

  buf[pos] = '\0';

  if (!feof(stdin)) {
    perror("shell");
    fprintf(stderr, "Something failed while reading stdin\n");
    free(buf);
    exit(EXIT_FAILURE);
  }
  return buf;
}

int main() {
  // const char *line = readline();
  // printf("Line: %s", line);
  printf("Chelle started\n");
  fflush(stdout);
  uint32_t size = 10;
  int32_t childs[size];
  uint8_t is_parent = 0;
  int32_t pid = 0;
  int32_t id = 0;
  for (uint32_t i = 0; i < size; i++) {
    pid = fork();
    id = i;
    if (pid == 0) {
      is_parent = 0;
      break;
    } else {
      is_parent = 1;
    }
    childs[i] = pid;
  }
  if (is_parent == 1) {
    printf("I have many children:\n[");
    for (uint32_t i = 0; i < size; i++) {
      printf("%d", childs[i]);
      if (i < size - 1) {
        printf(", ");
      }
    }
    printf("]\n");
    for (uint32_t i = 0; i < size; i++) {
      int32_t status;
      waitpid(childs[i], &status, 0);
      printf("My child came back to me %d with status %d\n", childs[i], status);
    }

  } else {
    sleep(id + 1);
    if (id == 0) {
      printf("I feel sick :(\n");
      exit(1);
    }
    printf("Hello i'm child %d i close now pid: %d\n", id, pid);
    exit(0);
  }

  // for (uint32_t i = 0; i < 256; i++) {
  //   errno = i;
  //   perror("Test");
  // }
}
