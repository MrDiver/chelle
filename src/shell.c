#include <String.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
// #include <fcntl.h>
// #include <stdlib.h>
// #include <unistd.h>

String readline() {
  uint32_t size = 4096;
  char *buf = malloc(size * sizeof(char));
  uint32_t pos = 0;
  int c;
  for (; (c = getc(stdin)) != EOF;) {
    if (c == '\n') {
      break;
    }
    buf[pos] = c;
    pos++;
    if (pos >= size) {
      buf = realloc(buf, size *= 2);
    }
  }

  buf[pos] = '\0';
  buf = realloc(buf, pos);

  if (c == EOF && !feof(stdin)) {
    perror("shell");
    fprintf(stderr, "Something failed while reading stdin\n");
    free(buf);
    exit(EXIT_FAILURE);
  }
  String str = {buf, pos};
  if (c == EOF) {
    str.size = -1;
  }
  return str;
}

#define WHITE_SPACE " \t\n\r\v\f"

void execute_command(String *tokens, size_t num_toks) {
  if (strcmp(tokens[0].text, "cd") == 0) {
    if (num_toks > 1) {
      chdir(tokens[1].text);
    } else {
      char *home = getenv("HOME");
      chdir(home);
    }
  } else if (strcmp(tokens[0].text, "exit") == 0) {
    exit(0);
  } else {
    int pid = fork();
    if (pid == 0) {
      char **argv = malloc(sizeof(char *) * num_toks);
      for (size_t i = 0; i < num_toks; i++) {
        argv[i] = tokens[i].text;
      }
      execvp(tokens[0].text, argv);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }
}

void parse_command() {
  String line = readline();
  if (line.size == -1) {
    String_delete(&line);
    exit(0);
  }
  size_t num_toks = 0;
  String *tokens = splitat(&line, &num_toks, WHITE_SPACE);

  if (tokens != 0) {
    execute_command(tokens, num_toks);
  }

  // Free
  for (size_t i = 0; i < num_toks; i++) {
    String_delete(&tokens[i]);
  }
  free(tokens);
  String_delete(&line);
}

int main() {
  printf("Welcome to my shell :3\n");
  while (1) {
    char *cwd = getcwd(NULL, 0);
    printf("%s$ ", cwd);
    free(cwd);
    parse_command();
  }
}
