#ifndef SHELL_H
#define SHELL_H
/*
** Standard library includes for core functionality:
** unistd.h    - POSIX operating system API (fork, exec, etc.)
** stdlib.h    - General utilities (malloc, free, exit)
** time.h      - For ctime()
** stdio.h     - Input/output operations
** errno.h     - System error numbers
** string.h    - String manipulation
** stdbool.h   - Add bool
** sys/stat.h  - for stat() and file info (permessi, dimensione, tipo, timestamp…)
** sys/wait.h  - Process control (wait, waitpid) ?
** sysexits.h  - System exit values ?
** dirent.h    - For ls command
*/
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h> //for different type as DIR
#include <sys/stat.h>
#include <dirent.h> 


#define MAX_PATH 1024
/*
** ANSI Color codes for terminal output formatting:
** Y    - Yellow
** G    - Green
** C    - Cyan
** RED  - Red
** RST  - Reset to default color
*/

#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST 	"\033[0m"

/*
ADD SOME MACROS
*/

#define NPOW "\n\n\n\n"
#define LINE "-------------------------------------------------------------------\n"
/*
ADD Struct for Command + function with command
*/
typedef struct build{
    const char* command_to_execute;
    int (*foo)(char** token);
}command;

int carbonara_echo(char **av);
int pizza_pwd(char **av);
int cannolo_ls(char** av);


/*
ADD Struct for ls_Command + function with command
*/
typedef struct builds{
    const char* ls_command_to_execute;
    int (*foo)(DIR* path);
}ls_command;

typedef struct{
    char *name;
    time_t time;
}FileInfo;

int torroncino_ls(DIR* path);
int pistacchio_ls(DIR* path);
int mario_ls(DIR* path);
int luigi_ls(DIR* path);
int panino_ls(DIR* path);
/*
ADD Function
*/
void printbanner(void);    /* Shell banner display */
char* read_line(ssize_t* read,char* cwd);
ssize_t read_right(ssize_t* read);
//Rewriting functions + with error messages
void tokenizer(char* phrase,char** token_phrase);
int conteggio_token(char* str);
void controllo_uscita(char* line,char** toks);
void Chdirs(const char *path,char* cwd);
const char* get_permission(mode_t mode);
int comparefiletime(const void *a, const void *b);
#endif