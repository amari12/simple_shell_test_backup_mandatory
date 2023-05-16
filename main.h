#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 1024
#define ARGS_SIZE 50

/*file: process_input2.c*/
void get_input(char *input);
void split_input(char *input, char *args[]);
void forking(char *input, char *args[], char *cmd, char *path);

/*file: handle_bi.c*/
int handle_builtins(char *args[], char **environ);

#endif
