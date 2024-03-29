#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define DISPLAY1 "PID INDUK** ** pid (%5.5d) ** ********\n"
#define DISPLAY2 "val1(%5.5d) -- val2(%5.5d) -- val3(%5.5d)\n"

int main(int argc, char *argv[]) {

  pid_t val1, val2, val3, father_pid = getpid();
  printf(DISPLAY1, father_pid);
  fflush(stdout);

  val1 = fork();
  waitpid(-1, NULL, 0);

  val2 = fork();
  waitpid(-1, NULL, 0);

  val3 = fork();
  waitpid(-1, NULL, 0);

  if (getpid() == father_pid) {
    char buffer[100];
    sprintf(buffer, "pstree -p %d > multifork.txt", father_pid);
    system(buffer);
  }

  printf(DISPLAY2, val1, val2, val3);

  return EXIT_SUCCESS;
}
