#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *const *argv) {
  int pid = fork();
  uint8_t *bla = malloc(1024 * 1024 * 1024);
  if (pid == 0) {
    sleep(5);
    free(bla);
    execvp("grep", argv);
  } else {
    int status;
    waitpid(pid, &status, 0);
    printf("Hallo ich bin hier! und mein kind war ls %d\n", status);
  }
  free(bla);
}
