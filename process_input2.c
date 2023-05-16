#include "main.h"

/**
 * get_input - reads the input from user and saves as string
 * @input: input string
 * Return: void
 */

void get_input(char *input)
{
	char *fgets_result;

	fgets_result = fgets(input, SIZE, stdin);
	if (fgets_result == NULL)
	{ /*reading error*/
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	/*replace new line with string terminator*/
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';
} /*get input*/

/**
 * split_input - splits input string into separate arguments
 * @input: input string
 * @args: separated input string
 * Return: void
 */

void split_input(char *input, char *args[])
{
	int i = 0;
	char cp_input[SIZE + 1];
	char *check_token;

	/*make copy of input string*/
	strcpy(cp_input, input);

	/*split input string into tokens: args*/
	check_token = strtok(cp_input, " ");
	while (check_token != NULL)
	{
		args[i] = check_token;
		i++;
		check_token = strtok(NULL, " ");
	}
	args[i] = NULL; /*last string in array should be NULL*/
} /*split input*/

/**
 * forking - forks parent and child process and exe cmd
 * @input: input string
 * @args: separated input string
 * @cmd: command (args[0])
 * @path: path
 * Return: void
 */

void forking(char *input, char *args[], char *cmd, char *path)
{
	pid_t fork_result;
	char *path_temp, *directory, *full_path = NULL;
	int status;

	fork_result = fork(); /*gives a pid*/
	if (fork_result == -1) /*error*/
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	} /*fail*/
	else if (fork_result == 0) /*success -> child process*/
	{
		path_temp = strdup(path); /*where does path come from?*/
		directory = strtok(path_temp, ":"); /*full_path = NULL;*/
		while (directory != NULL)
		{
			full_path = malloc(strlen(directory) + strlen(input) + 2);
			sprintf(full_path, "%s/%s", directory, cmd);
			if (access(full_path, X_OK) == 0)
			{
				break;
			}
			else
			{
				free(full_path);
				full_path = NULL;
			}
			directory = strtok(NULL, ":");
		} /*while*/
		if (full_path == NULL)
		{ /*cmd not found in path*/
			printf("Command not found in PATH\n");
			exit(EXIT_FAILURE);
		}
		execve(full_path, args, NULL); /*exe cmd*/
		perror("execve failed"); /*if exe fails*/
		exit(EXIT_FAILURE);
	} /*child*/
	else /*parent*/
		wait(&status);
} /*forking*/

