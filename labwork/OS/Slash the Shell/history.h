#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <malloc.h>
#include <readline/readline.h>
#include <readline/history.h>

void initialize_readline ();
char *command_generator PARAMS((const char *, int));
char **command_completion PARAMS((const char *, int, int));
