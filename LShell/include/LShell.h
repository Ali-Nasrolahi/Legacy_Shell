#ifndef __LShell_Header__
#define __LShell_Header__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define RL_BUFSIZE 1024
#define TOk_BUFSIZE 64
#define TOK_DELIM " \t\n\n\a"


void        LShell(void);
char        *ReadLine(void);
char        **Parsing(char *Line);
int         Execute(char **args);
int         Launch(char **args);


#endif

