#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/rlconf.h>
#include <readline/rlstdc.h>
#include <readline/rltypedefs.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>

#define CMD_PWD 87
#define CMD_EXIT 88
#define CMD_UNKNOWN 89
#define CMD_SUCCESS 90

#define SLASH_DEBUG 0
#define MAX_ARGS 100
