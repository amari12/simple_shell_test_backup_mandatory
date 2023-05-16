#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * main - main funtion / entry poin
 * @argc: nr of arguments
 * @argv: arguments
 * Return: int
 */

int main(int argc __attribute__((unused)),
		char *argv[] __attribute__((unused)))
{
	char input[SIZE];
	/*int i;*/
	char /**arg,*/ *cmd;
	char *args[ARGS_SIZE];
	int exit_loop = 0;
	char *path;
	int check; /*for builtin, check for env*/
	char **environ = __environ; /*global variable*/

	path = getenv("PATH"); /*get path*/
	while (exit_loop != 1) /*shell loop*/
	{
		printf("our shell>> "); /*prompt*/
		fflush(stdout); /*flush output buffer*/
		get_input(input); /*read input*/
		split_input(input, args); /*get args list*/
		cmd = args[0];
		/*rg = args[1];*/
		/*test*/
		/*printf("========================\n");*/
		/*printf("Testing output:\n");*/
		/*for (i = 0; args[i] != NULL; i++)*/
		/*{*/
		/*	printf("\tInput %i: %s\n", i, args[i]);*/
		/*}*/
		/*printf("\tInput %i: %s\n", i, args[i]);*/
		/*printf("\tcmd: %s\n", cmd);*/
		/*printf("\targ: %s\n", arg);*/
		/*printf("========================\n");*/
		/*handle builtin*/
		check = handle_builtins(args, environ);
		if (check == 1)
			continue; /*env builtin*/
		/*fork - child process*/
		forking(input, args, cmd, path);
	} /*show prompt*/
	return (0);
}

