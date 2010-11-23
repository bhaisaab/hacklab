#include "common.h"

void getPathString(char **envp, char *binPath);
void insertPathStringToSearch(char** searchPath, char *pathString);
void fillArgv(char *tmp_argv, char* my_argv[]);
int  attachPath(char *cmd, char** searchPath);
void callFork(char *cmd, char **argv, char **envp);

/* The names of functions that actually do the manipulation. */
int com_stat (char *);
int com_help ();
int com_quit ();

typedef struct {
  char *name;			/* User printable name of the function. */
  char *doc;			/* Documentation for this function.  */
} COMMANDLIST;

/* Forward declarations. */
int execute_line (char* line);
void clrScreen(char **argv, char **envp);
void printShellName();
void printCurrentDir();
void handleSignal(int signo);
