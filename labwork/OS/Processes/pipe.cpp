#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
 char str[1024], *cp;
 int pipefd[2];
 pid_t pid;
 int status, died;

  pipe (pipefd);
  pid = fork();

  switch(pid)
  {
   case -1: printf("can't fork\n");
            exit(-1);
   
   case 0 : // this is the code the child runs 
            close(1);      // close stdout
            // pipefd[1] is for writing to the pipe. We want the output
            // that used to go to the standard output (file descriptor 1)
            // to be written to the pipe. The following command does this,
            // creating a new file descripter 1 (the lowest available) 
            // that writes where pipefd[1] goes.
            dup (pipefd[1]); // points pipefd at file descriptor
            // the child isn't going to read from the pipe, so
            // pipefd[0] can be closed
            close (pipefd[0]);
            execl ("/bin/date","date",0);
            exit(0);
   default: // this is the code the parent runs 

            close(0); // close stdin
            // Set file descriptor 0 (stdin) to read from the pipe
            dup (pipefd[0]);
            // the parent isn't going to write to the pipe
            close (pipefd[1]);
            // Now read from the pipescc
            scanf("%[^\n]s", str);
            //cin.getline(str, 1023);
            //cout << "The date is " << str << endl;
            printf("%s\n", str);
            died = wait(&status);
   }
  return 0;
}

