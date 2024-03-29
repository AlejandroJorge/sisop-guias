#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int i, status, chain_len = 4;
  pid_t child, pid_ancestro;

  pid_ancestro = getpid();
  for (i = 1; i < chain_len; ++i)
    if ((child = fork())) // Will break if the current process is the father
      break;
  fprintf(stderr, "Esta es la vuelta nro %d\n", i);
  fprintf(stderr, "Recibi de fork el valor de %d\n", child);
  fprintf(stderr, "Soy el proceso %d con padre %d\n", getpid(), getppid());

  if (i == chain_len - 1) {
    // Runs only on the last process of the chain
    char buffer[100];
    sprintf(buffer, "pstree -s %d > ./chainp.txt", pid_ancestro);
    system(buffer);
  }

  wait(&status);

  return EXIT_SUCCESS;
}
