#include "slash.h"

const char* shellName = "<$lash/> ";

COMMANDLIST commandsList[] = {
  { "cd", "Change to directory DIR" },
  { "help", "Display this command list" },
  { "ls", "List files in DIR" },
  { "pwd", "Print the current working directory" },
  { "quit", "Exit/Quit" },
  { "exit", "Exit/Quit" },
  { "stat", "Print out statistics on FILE" },
  { "more", "View the contents of FILE" },
  { (char *)NULL, (char *)NULL }
};

/* **************************************************************** */
/*                                                                  */
/*                   Slash Shell Main Routines                      */
/*                                                                  */
/* **************************************************************** */

/* Get Paths Chars from envp[][] to binPath*/
void 
getPathString(char **envp, char *binPath)
{
	int count = 0;
	char *tmp;
	while(1) 
  {
		tmp = strstr(envp[count], "PATH");
		if(tmp == NULL) 
			count++;
    else
			break;
	}
  strncpy(binPath, tmp, strlen(tmp));

  #if SLASH_DEBUG
    printf("%s\n", binPath);
  #endif
}

/* Insert the PATH = fields into pathString */
void 
insertPathStringToSearch(char** searchPath, char *pathString) 
{
	register int index=0;
	char *tmp = pathString;
	char ret[100];

	bzero(ret, 100);

	while(*tmp != '=')
		tmp++;
	tmp++;

	while(*tmp != '\0') 
  {
		if(*tmp == ':') 
    {
			strncat(ret, "/", 1);
			searchPath[index] = (char *) malloc(sizeof(char) * (strlen(ret) + 1));
			strncat(searchPath[index], ret, strlen(ret));
			strncat(searchPath[index], "\0", 1);
			index++;
			bzero(ret, 100);
		} 
    else 
    {
			strncat(ret, tmp, 1);
		}
		tmp++;
	}

  strncat(ret, "/", 1);
  searchPath[index] = (char *) malloc(sizeof(char) * (strlen(ret) + 1));
	strncat(searchPath[index], ret, strlen(ret));
	strncat(searchPath[index], "\0", 1);

  #if SLASH_DEBUG
  int i;
  for(i=0; searchPath[i] != NULL; i++)
    printf("%s\n", searchPath[i]);
  #endif

}

/* Fill arguments for cmd from tmp to argv */
void 
fillArgv(char *tmp_argv, char* my_argv[])
{
  #if SLASH_DEBUG
		printf("tmpArg: %s\n", tmp_argv);
  #endif

	char *foo = tmp_argv;
	int index = 0;
	char ret[100];
	bzero(ret, 100);

	while(*foo != '\0') 
  {
		if(index == MAX_ARGS)
			break;

		if(*foo == ' ') 
    {
      while(*foo == ' ')
        foo++;

      foo--;

			if(my_argv[index] != NULL)
        free(my_argv[index]);

			my_argv[index] = (char *)malloc(sizeof(char) * strlen(ret) + 1);
			bzero(my_argv[index], strlen(ret)+1);
			
			strncpy(my_argv[index], ret, strlen(ret));
			strncat(my_argv[index], "\0", 1);
			bzero(ret, 100);
			index++;
		} 
    else 
    {
			strncat(ret, foo, 1);
		}
    #if SLASH_DEBUG
		printf("foo is %c\n", *foo);
    #endif
		foo++;
	}
	my_argv[index] = (char *)malloc(sizeof(char) * (strlen(ret)+1));
  bzero(my_argv[index], strlen(ret) + 1);
	strncpy(my_argv[index], ret, strlen(ret));
	strncat(my_argv[index], "\0", 1);
  #if SLASH_DEBUG
  int i;
  for(i = 0; my_argv[i] != NULL ; i++ )
		printf("my_argv[%d]: %s\n", i, my_argv[i]);
  #endif
}


/* In case cmd has a "/" char -> user is supplying full/partial path */
int 
attachPath(char *cmd, char** searchPath)
{
	char ret[100];
	int index;
	int fd;
	bzero(ret, 100);
	for(index=0;searchPath[index]!=NULL;index++) 
  {
		strcpy(ret, searchPath[index]);
		strncat(ret, cmd, strlen(cmd));
		if((fd = open(ret, O_RDONLY)) > 0) 
    {
      #if SLASH_DEBUG
        printf("Got PATH: %s\n", ret);
      #endif
			strncpy(cmd, ret, strlen(ret));
			close(fd);
			return 0;
		}
	}
	return 0;
}

/* Execute the command as Chils Process */
void callFork(char *cmd, char **argv, char **envp)
{
	int i;
  pid_t pid;
  pid = fork();

  if(pid == 0)
  {
		i = execve(cmd, argv, envp);
		if(i < 0) 
    {
			printf("%s: Command Not Found/Could not Execute\n", cmd);
			exit(1);		
		}
  }
  if(pid > 0) /* Parent */
		wait(&i);

  return;
}


/* **************************************************************** */
/*                                                                  */
/*                   Other Shell Functions                          */
/*                                                                  */
/* **************************************************************** */

/* Execute a command line. */
int
execute_line (char* line)
{

  #if SLASH_DEBUG
    printf("EXCUTE_LINE: %s\n", line);
  #endif

  if(strcmp(line, "help") == 0)
  {
    com_help();
    return CMD_SUCCESS;
  }

  if(strcmp(line, "exit") == 0)
  {
    com_quit();
    return CMD_EXIT;
  }

  if(strncmp(line, "stat", 4) == 0)
  { 
    com_stat(line);
    return CMD_SUCCESS;
  }
  return CMD_UNKNOWN;
}


void 
clrScreen(char **argv, char **envp)
{
  #ifdef __TERMCOLOR__
  clearScreen(); /* Will work only on Unix Terms */
  #if SLASH_DEBUG
    printf("Using ASCII CODE to clear screen.\n");
  #endif
  #else
  char clearPath[] = "/usr/bin/clear";
	if(fork() == 0) {
		execve(clearPath, argv, envp);
    printf("Failed!\n");
		exit(1);
	} else {
		wait(NULL);
	}
  #endif
  return;
}

void 
printShellName()
{
	printf("\x1b[91m%s\x1b[00m", shellName); /* 91 = Bright Red Color */
	fflush(stdout);
  return;
}

void 
printCurrentDir()
{  
  char dir[128];
  /* Get Current Working Dir */
  getcwd(dir,sizeof(dir));
  printf("\x1b[96m<%s/>\x1b[00m ", dir);
	fflush(stdout);
  return;
}

void 
handleSignal(int signo)
{
  printf("\n");
	printShellName();
}

/* **************************************************************** */
/*                                                                  */
/*                   Trivial Slash Shell Commands                   */
/*                                                                  */
/* **************************************************************** */

int
com_stat (char *arg)
{
  struct stat finfo;

  #if SLASH_DEBUG
    printf("Stat success.\n");
  #endif

  if (stat (arg, &finfo) == -1)
    {
      perror (arg);
      return (1);
    }

  printf ("Statistics for `%s':\n", arg);

  printf ("%s has %d link%s, and is %d byte%s in length.\n", arg,
          finfo.st_nlink,
          (finfo.st_nlink == 1) ? "" : "s",
          (int)finfo.st_size,
          (finfo.st_size == 1) ? "" : "s");
  printf ("Inode Last Change at: %s", ctime (&finfo.st_ctime));
  printf ("      Last access at: %s", ctime (&finfo.st_atime));
  printf ("    Last modified at: %s", ctime (&finfo.st_mtime));
  return (0);
}

/* Print out help for ARG, or for all of the commands if ARG is
   not present. */
int
com_help ()
{
  register int i;

  for (i = 0; commandsList[i].name; i++)
    printf ("%s\t\t%s.\n", commandsList[i].name, commandsList[i].doc);

  return (0);
}

/* The user wishes to quit using this program. */
int
com_quit (char* arg)
{

  return CMD_EXIT;
}


