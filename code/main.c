/* Libraries */
#include <stdlib.h>		/* malloc */
#include <stdio.h>		/* fopen */
#include <string.h>  	/* strcmp, strcat, memcpy, strerror */
#include <errno.h>

/* Defines */
#define ARGS_USAGE "-n NAME	SIZE\t(create a new board named NAME and size SIZE (format 10x5)\n"\
					"-e NAME\t\t(use an existing board called NAME\n"
#define NEW_BOARD "-n"
#define EXISTING_BOARD "-e"
#define SUCCESS 1  /* Every function should return success or failure */
#define FAILURE 0
#define BOARD_PATH "/tmp/boards/" /* Will have to be changed... */
#define MAX_PATH_LEN 260

/* Function Inits */
static int create_new_board(char *name, char *size);
static int use_existing_board(char *name);

/************************************************
main
************************************************/

int main (int argc, char *argv[])
{
	/* Figure out what the person is trying to do
		Possbile args:
			-n NAME	SIZE	new board creation (format for SIZE = "5x10")
			-e NAME			use an existing board
			
	*/

	if (0 == strcmp(argv[1], NEW_BOARD))
	{
		if (argc != 4)
		{
			printf("usage: \n%s\n", ARGS_USAGE);
			return 0;
		}
		printf("Creating a new board named '%s' with size '%s'\n", argv[2], argv[3]);
		create_new_board(argv[2], argv[3]);
		/*TODO Call function to create a new board */
	}
	else if (0 == strcmp(argv[1], EXISTING_BOARD))
	{
		if (argc != 3)
		{
			printf("usage: \n%s\n", ARGS_USAGE);
			return 0;
		}
		printf("Using existing board named '%s'\n", argv[2]);
		use_existing_board(argv[2]);
	}
	else
	{
		printf("usage: \n%s\n", ARGS_USAGE);
		return 0;
	}

	return 1;
}

/************************************************
 create_new_board
 	Creates a new board in the saved_boards directory called name with a size equal to size
 	TEST: will overwrite existing boards with the same name??
 	
 Params:
 	name:	pointer to the name of the board
 	size:	point to the size of the board (format "10x5")

returns:
	FAILURE or SUCCESS
************************************************/
static int create_new_board(char *name, char *size)
{
	int ret = FAILURE;  /* Assume failure */
	char *path = NULL;

	/* Alloc space for path + 1 for null terminator */
	if (NULL == (path = malloc(MAX_PATH_LEN + 1)))
	{
		printf("Failed to allocate space for path\n");
		return ret;
	}

	/* Copy default path to memory just created */
	memcpy(path, BOARD_PATH, sizeof(BOARD_PATH));

	/* Concatenate the name to the end of the path DANGEROUS BUFFER OVERFLOW*/
	strcat(path, name);

	printf("Creating file: %s\n", path);

	errno = 0;
	/* w+ reading writing file is created if it doesn't exist otherwise truncated */
	if (NULL == fopen(path, "w+"))
	{
		printf("Failed to create file\n");
		printf("Error: %s\n", strerror(errno));
		return ret;
	}

	return ret;
}

/************************************************
 use_existing_board
 	Creates a new board in the saved_boards directory called name with a size equal to size
 	TEST: will overwrite existing boards with the same name??
 	
 Params:
 	name:	pointer to the name of the board
 	size:	point to the size of the board (format "10x5")

returns:
	FAILURE or SUCCESS
************************************************/
static int use_existing_board(char *name)
{
	int ret = FAILURE;

	return ret;
}