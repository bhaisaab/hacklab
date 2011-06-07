#include "common.h"
#include "termcolor.h"
#include "history.h"
#include "slash.h"

typedef void (*sighandler_t)(int);

const char* aboutSlash = "**************************************************"
                       "\n*  Slash Shell version 1.0 (i486-pc-linux-gnu)   *"
                       "\n*  Created by Rohit Yadav and Abhishek Kumar     *"
                       "\n*  Copyright 2009, under GNU GPL v2 or later     *"
                       "\n*  Please help for a brief command help list     *"
                       "\n**************************************************\n\n";

static char *slashArgv[MAX_ARGS];
static char *searchPath[50];

void 
freeArgv(char* my_argv[])
{
  #if SLASH_DEBUG
    printf("Free: sArgv\n");
  #endif

	int index;
	for(index=0;my_argv[index]!=NULL;index++)
  {
		bzero(my_argv[index], strlen(my_argv[index])+1);
		free(my_argv[index]);
		my_argv[index] = NULL;
	}
}

void nullifyArgv(char* argv[])
{
	int index;
	for(index=0; argv[index]!=NULL;index++)
    argv[index] = NULL;
}

int 
main(int argc, char *argv[], char *envp[])
{
  char *line;

  int returnValue;

	int i, fd;

	char *pathString = (char *)malloc(sizeof(char) * 256);
	char *cmd = (char *)malloc(sizeof(char) * 256);

  bzero(pathString, 256);
  bzero(cmd, 256);

  /* Manage Signals */
  signal(SIGINT, SIG_IGN);	
  signal(SIGQUIT,SIG_IGN);
//  signal(SIGCHLD,SIG_IGN);
  signal(SIGKILL,SIG_IGN);
  signal(SIGTERM,SIG_IGN);

	signal(SIGINT, handleSignal);

  /* Extract the PATH= var from envp */
	getPathString(envp, pathString);
  /* Insert each path to be searched into searchPath[][] */
  insertPathStringToSearch(searchPath, pathString);

  /* Print about Slash */
  clrScreen(argv, envp);
  printf("%s", aboutSlash);
  printf("PID=%d\n", getpid());

#if SLASH_DEBUG
  for(i=0; envp[i] != NULL; i++)
    printf("%s\n", envp[i]);
#endif

  /* Bind our completer + History Feature */
  initialize_readline();

  while(1)
  {
    line = readline ("\x1b[96m<$lash/>\x1b[00m "); /* Print in Red! */

    #if SLASH_DEBUG
      printf("Input: %s\n", line);
    #endif

    if(*line)
    {
      add_history (line);
      returnValue = execute_line (line);

      if(returnValue == CMD_EXIT)
        break;

      if(returnValue == CMD_UNKNOWN)
      {
        #if SLASH_DEBUG
          printf("CMD_UNKNOWN: %s\n", line);
        #endif
        /* Extract args to command into slashArgv[][] */
        nullifyArgv(slashArgv);
        fillArgv(line, slashArgv);
        bzero(cmd, 256);
				strncpy(cmd, slashArgv[0], strlen(slashArgv[0]));
				strncat(cmd, "\0", 1);

        #if SLASH_DEBUG
          printf("arg[0]: %s\n", slashArgv[0]);
          printf("cmd: %s\n", cmd);
        #endif

				if(index(cmd, '/') == NULL) 
        {
				  if(attachPath(cmd, searchPath) == 0) 
          {
					  callFork(cmd, slashArgv, envp);
					} 
          else 
					  printf("%s: command not found\n", cmd);
        } 
        else 
        {
				  if((fd = open(cmd, O_RDONLY)) > 0) 
          {
					  close(fd);
						callFork(cmd, slashArgv, envp);
					} 
          else 
					  printf("%s: command not found\n", cmd);
			  }
        freeArgv(slashArgv);
      }
    }

    if(line != NULL)
    free(line);
	  fflush(stdout);
  }

  free(cmd);
	free(pathString);
	for(i=0;i<50;i++)
		free(searchPath[i]);
	return 0;
}

