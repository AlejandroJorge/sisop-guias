#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int ii = 0;
  pid_t ancestor_pid = getpid();

  if ((fork()) == 0)
    ii++;
  waitpid(-1, NULL, 0);

  if ((fork()) == 0)
    ii++;
  waitpid(-1, NULL, 0);

  if ((fork()) == 0)
    ii++;
  waitpid(-1, NULL, 0);

  pid_t current = getpid();
  printf("Result = %3.3d, PID: %d \n", ii, current);

  if (current == ancestor_pid) {
    char buffer[100];
    sprintf(buffer, "pstree -p %d > isengfork.txt", current);
    system(buffer);
  }

  return EXIT_SUCCESS;
}
