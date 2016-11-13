/* Libraries */
#include <stdlib.h>		/* malloc, free */
#include <stdio.h>		/* sscanf */
#include <string.h>  	/* strcmp, strcat, memcpy, strerror */
#include <errno.h>
#include <sys/types.h>	/* open */
#include <sys/stat.h>	/* open */
#include <fcntl.h>		/* open */
#include <unistd.h>		/* write */

/* Defines */
#define ARGS_USAGE "-n NAME	ROWS COLS\t(create a new board named NAME"\
					" and size SIZE (format 10x5)\n"\
					"-e NAME\t\t(use an existing board called NAME\n"
#define NEW_BOARD "-n"
#define EXISTING_BOARD "-e"
#define SUCCESS 1  /* Every function should return success or failure */
#define FAILURE 0
#define BOARD_PATH "/tmp/boards/" /* Will have to be changed... */
#define MAX_PATH_LEN 260
#define PIECE_SIZE sizeof(char)  /* A piece is represent in memory by a char
									usable acii numbers 33 - 126 (93) */

/* Function Inits */
static int create_new_board(char *name, char *rows, char *cols);
static int use_existing_board(char *name);

/*TODO create default pieces (ground ~ null byte;) */

/* Globals */
static char *g_game_board = NULL;  /* A pointer to the game board */

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
		if (argc != 5)
		{
			printf("usage: \n%s\n", ARGS_USAGE);
			return 0;
		}
		printf("Creating a new board named '%s' with size %sx%s\n", argv[2], 
			   argv[3], argv[4]);
		create_new_board(argv[2], argv[3], argv[4]);
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
 	Creates a new board in the saved_boards directory called name with rows and cols
 	TEST: will overwrite existing boards with the same name??
 	
 Params:
 	name:	pointer to the name of the board
 	rows:	pointer to the number of rows
	cols:	pointer to the number of columns

returns:
	FAILURE or SUCCESS
************************************************/
static int create_new_board(char *name, char *rows, char *cols)
{
	int ret = FAILURE;  /* Assume failure */
	char *path = NULL;
	int fd = -1;
	int row = 0;
	int col = 0;
	int size = 0;  /* Size of the baord */
	char *board = NULL;
	int lcv = 0;

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

	/* create the file with write permissions for this user */
	if (-1 == (fd = open(path, O_RDWR | O_CREAT, S_IRWXU)))
	{
		printf("Failed to create file\n");
		return ret;  /*TODO memory cleanup */
	}

	/* Calculate the size of the board rows*cols*PIECE_SIZE */
	sscanf(rows, "%d", &row);  /* Convert char * into int */
	sscanf(cols, "%d", &col);
	size = row*col*PIECE_SIZE;
	printf("Size of board: %d\n", size);

	/* Allocate space for the board - init it to 0 (null byte ~ ground) */
	if (NULL == (board = calloc(1, size + 1)))
	{
		printf("Failed to allocate space for the board\n");
		return ret;
	}

	/* Init all the chars in the board to '0' dec=48 */
	for (lcv = 0; lcv < size; lcv++)
	{
		board[lcv] = 48;
	}

	/* Null terminate the buffer */
	board[lcv] = '\0';

	/* Write the board to file TODO this should be moved to a save function for repetition */
	if (-1 == write(fd, board, size))
	{
		printf("Error writing to file\n");
		return ret;
	}

	g_game_board = board;  /* Set the global board pointer */
	/* Free stuff before returning */
	free(path);
	board = NULL;
	path = NULL;
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