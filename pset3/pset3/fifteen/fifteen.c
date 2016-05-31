/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// !extra constants
#define EMPTY_TILE_INT			            0
#define INT_TO_STR_CHAR_BUFFER_SIZE_INT	    128

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[]) 
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
 
 // Global vars detected, gotta be careful now!
void init(void)
{
    bool areDimsOdd = (d & 1) != 0; 
    // in C, the (...!= 0...) part is purely optional, however
    // we still choose to leave it there for clarity.
    
    board[d - 1][d - 1] = EMPTY_TILE_INT;
    if (areDimsOdd) {
        board[d - 1][d - 2] = 1;
        board[d - 1][d - 3] = 2;
    } else {
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }
    int num = 3;
    for (int i = d - 4; i >= 0; --i) {
        board[d - 1][i] = num;
        num++;
    }
    
    num = d;
    for (int row = d - 2; row >= 0; --row) {
        for (int col = d - 1; col >= 0; --col) {
            board[row][col] = num;
            ++num;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
	char buffer[INT_TO_STR_CHAR_BUFFER_SIZE_INT];

    int num;
    for (int row = 0; row < d; ++row) {
        for (int col = 0; col < d; ++col) {
            num = board[row][col];
            snprintf(buffer, INT_TO_STR_CHAR_BUFFER_SIZE_INT, "%d", num);
            printf("%3s", (num == 0) ? "_" : buffer);
        }
        printf("\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    if (tile == EMPTY_TILE_INT) {
        // cannot move the empty tile
        return false;
    }
    if (tile < 0) {
        return false;
    }
    if (tile >= d * d) {
        return false;
    }
    
    for (int row = 0; row < d; ++row) {
        for (int col = 0; col < d; ++col) {
            if (board[row][col] == tile) {
                
                int horizontalCoords[2] = { 
                    col + 1, // leftIndex
                    col - 1  // rightIndex
                };
                
                int verticalCoords[2] = {
                    row + 1, // topIndex
                    row - 1  // bottomIndex  
                };
               
                for (int i = 0; i < 2; ++i) {
                    if (horizontalCoords[i] >= 0 && horizontalCoords[i] < d && board[row][horizontalCoords[i]] == EMPTY_TILE_INT) {
						int temp						= board[row][col];
						board[row][col]					= board[row][horizontalCoords[i]];
						board[row][horizontalCoords[i]] = temp;
						return true;
                    }
                }
                for (int i = 0; i < 2; ++i) {
                    if (verticalCoords[i] >= 0 && verticalCoords[i] < d && board[verticalCoords[i]][col] == EMPTY_TILE_INT) {
						int temp						= board[row][col];
						board[row][col]					= board[verticalCoords[i]][col];
						board[verticalCoords[i]][col]	= temp;
						return true;
                    }
                }

                return false;
            }
        }
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{

	if (board[d - 1][d - 1] != EMPTY_TILE_INT) {
		return false;
	}
	int lastTileValue = board[0][0];
	for (int row = 0; row < d; ++row) {
		for (int col = 0; col < d; ++col) {
			if (board[row][col] != EMPTY_TILE_INT && board[row][col] < lastTileValue) {
				return false;
			}
			lastTileValue = board[row][col];
		}
	}
    return true;
}