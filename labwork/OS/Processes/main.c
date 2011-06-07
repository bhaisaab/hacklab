/* main.c - Studying Process Tree in Unix
 * Copyright (C) 2009, Rohit Yadav
 *
 * This program is free software and licensed under GNU GPL v3.
 *
 */

/* STD C */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/* POSIX */
#include <sys/param.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/time.h> 
#include <unistd.h>

#define FORK_BOMB 50

char choice;
pid_t PPID;
int pipefd[2];

pid_t Fork();

pid_t
Fork()
{
  if(choice == 'v')
  {
    //printf("vfork() Selected\n");
    return vfork();
  }
  else
  {
    //printf("fork() Selected\n");
    return fork();
  }
}

void
callPsTree()
{
  char strPid[8];
  snprintf(strPid, 7, "%d", PPID);
  
  close(1);
  dup (pipefd[1]); // points pipefd at file descriptor
  close (pipefd[0]);
  execl ("/usr/bin/pstree","pstree", "-p", strPid, NULL);
  _exit(0);
}


void
sigkill(int sig)
{
  printf("I'm getting killed %d\n", getpid());
  callPsTree();
  signal(SIGCHLD, SIG_DFL);
  _exit(0);
}

void 
sigcld(int sig)
{
  printf("Child of Parent(%d) Killed\n", getpid());
  
  signal(SIGCHLD, sigcld); /* Re-enable Signals to default routines */
}

void
createTree(int degree, int height)
{
  --height;
  if(height == 0) /* Leaf reached */
  {
    return;
  }

  int i;
  pid_t pid; 
  int status;

	for(i = 0; i < degree; i++)
  {
		pid = Fork();
		
		if(pid < 0) 
    {
			printf("Error: Fork()...\n");
			_exit(1);
		}
		/* Child */
		else 
    if ( pid == 0 ) 
    {
      printf("PARENT(%d) forked CHILD(%d)\n", getppid(), getpid());
      //signal(SIGKILL, sigkill);
      //signal(SIGQUIT, sigkill);    
      //signal(SIGCHLD, signalHandler);
      //for(i = 0; i < degree; i++)
	      createTree(degree, height);     

      for(;;);
	  }
	  else
    if(pid > 0)
    {
      //sleep(3);
      signal(SIGCHLD, sigcld);
    }
	}
  for(;;);
  /*{
    close(0);
    dup (pipefd[0]);
    close (pipefd[1]);
    char ch;            
    for(i = 0; (scanf("%c", &ch) != EOF); i++)
      putchar(ch);
  }*/
}

int
main(int argc, char *argv[])
{ 
  int height;
  int degree;

  if(argc < 3){
    printf("Usage: %s height degree(Number of Nodes at each level)\n", argv[0]);  
    _exit(1);
  }

  height = atoi(argv[1]); /* Root is at Level 0 */
  degree = atoi(argv[2]);  

  /* Check for Fork Bomb Conditions */
  if(height*degree > FORK_BOMB ){
    printf("Fork Bomb Condition!\n");
    _exit(1);
  }

  PPID = getpid();

  printf("\nROOT NODE(%d): Enter Forking Mechanism:\n1. vfork()\t2. fork()\nEnter Choice: ", PPID);
  scanf("%c", &choice);   
  choice = (choice == '1') ? 'v': 'f';

//  signal(SIGINT, signalHandler);
//  signal(SIGQUIT, signalHandler);
//  signal(SIGKILL, signalHandler);
//  signal(SIGCHLD, signalHandler);

  int j;
  for(j = 0; j < degree; j++)
    createTree(degree, height);
  
  return 0;
}

