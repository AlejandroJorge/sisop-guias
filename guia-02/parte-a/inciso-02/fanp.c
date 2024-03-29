#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int i, status, fan_len = 4;
  pid_t child, pid_padre;

  pid_padre = getpid();
  for (i = 1; i < fan_len; ++i)
    if ((child = fork()) <= 0)
      break; // Will break if is the child process or an error occurs
    else
      // Runs when the current process is the father
      fprintf(stderr,
              "Este es el ciclo nro %d y se esta creando el proceso %d\n", i,
              child);

  if (pid_padre == getpid()) {
    char buffer[100];
    sprintf(buffer, "pstree -s %d > ./fanp.txt", pid_padre);
    system(buffer);

    // The father process waits for all the children
    for (int i = 1; i < fan_len; ++i)
      wait(&status);
  }

  fprintf(stderr, "Este es el proceso %d con padre %d\n", getpid(), getppid());

  return EXIT_SUCCESS;
}
