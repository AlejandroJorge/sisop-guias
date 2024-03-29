#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

  int status;
  pid_t father = getpid();
  pid_t child;
  if ((child = fork())) {
    printf("I'm the parent process with PID: %d\n", father);
    wait(&status);
  } else {
    printf("I'm the child process with PID: %d\n", getpid());
    char shellCommand[100];
    sprintf(shellCommand, "pstree -s %d > ./aprocesos.txt", father);
    system(shellCommand);
  }

  return EXIT_SUCCESS;
}
