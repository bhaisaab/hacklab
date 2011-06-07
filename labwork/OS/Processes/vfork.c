#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int global;

int main()
{
  int local;

  local = 1;
  global = 0;

  if(fork() == 0) /* Child Process */
  {
    printf("CHILD: PID=%ld\n", (long)getpid());
    global = 2; /* Parent's Data Space */
    local = 3;  /* On Parent's Data Stack */
    printf("CHILD: global=%d &global=%lu\n", global, &global);
    printf("CHILD: local=%d  &local=%lu\n\n", local, &local);
    _exit(0);
  }

  wait();
  printf("PARENT: PID=%ld\n", (long)getpid());
  printf("PARENT: global=%d &global=%lu\n", global, &global);
  printf("PARENT: local=%d  &local=%lu\n", local, &local);

  return 0;
}

