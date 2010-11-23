#include "history.h"

extern char *xmalloc (size_t);

void initialize_readline ()
{
  /* Tell the completer that we want a crack first. */
  rl_attempted_completion_function = command_completion;
}

/* Attempt to complete on the contents of TEXT.  START and END show the
   region of TEXT that contains the word to complete.  We can use the
   entire line in case we want to do some simple parsing.  Return the
   array of matches, or NULL if there aren't any. */
char **
command_completion (const char* text, int start, int end)
{
  char **matches;

  matches = (char **)NULL;

  /* If this word is at the start of the line, then it is a command
     to complete.  Otherwise it is the name of a file in the current
     directory. */
  if (start == 0)
    matches = rl_completion_matches(text, command_generator);

  return (matches);
}

char *
dupstr (char* s)
{
  char *r;

  r = xmalloc (strlen (s) + 1);
  strcpy (r, s);
  return (r);
}

/* Generator function for command completion.  STATE lets us know whether
   to start from scratch; without any state (i.e. STATE == 0), then we
   start at the top of the list. */
char *
command_generator (const char* text, int state)

{
  static int list_index, len;
  char *name;

  /* Popular Commands */
  char *possible_commands[] = 
  { "alias", "bash", "cd", "chmod", "pwd", "chown", "echo", "kill", "mv", "bzcat", "ed",
    "nano", "tar", "cp", "ln", "nc", "rm", "grep", "touch", "login", "ls", "date",
    "sed", "dd", "gzip", "sh", "more", "df", "dir", "mkdir", "ping", "sleep", "cat",
    "ps", "su", "sudo", "reboot", "exit", "quit", "help", "more", "less", "vim"
  };

  /* If this is a new word to complete, initialize now.  This includes
     saving the length of TEXT for efficiency, and initializing the index
     variable to 0. */
  if (!state)
    {
      list_index = 0;
      len = strlen (text);
    }

  /* Return the next name which partially matches from the command list. */
  while( (name = possible_commands[list_index]) )
    {
      list_index++;

      if (strncmp (name, text, len) == 0)
        return (dupstr(name));
    }

  /* If no names matched, then return NULL. */
  return ((char *)NULL);
}


