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

// dimensions
int d;

// board
int board[DIM_MAX][DIM_MAX];

// blank tile variables 
int blank_row;
int blank_col;
int tile_row;
int tile_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int* a, int* b);
int tileSearch(int tile);
bool legalmove(void);

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
void init(void)
{
    int tileNum = (d*d)-1; // creates a variable to store each individual tile's number //
    blank_row = d-1;
    blank_col = d-1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++) // iterate across 2D board, assign tileNum to each tile //
        {
            board[i][j] = tileNum;
            tileNum--;
        }
    }
    if (((d*d)-1) % 2 != 0) // determines if tiles 1 and 2 need to be switched //
    {
        swap(&board[d-1][d-3], &board[d-1][d-2]);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++) //iterate across rows and columns of array //
        {
            if (board[i][j] < 10) // single digit numbers need an extra space //
            {
                if (board[i][j] == 0)
                {
                    printf(" [__]"); //print an underscore for blank space //
                }
                else 
                {
                    printf("[%2i]", board[i][j]); //create room for 2 digit numbers //
                }
            }
            else
            {
                printf("[%i]", board[i][j]);
            }
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
    // TODO
    tileSearch(tile); // search for the tile //
    
    if (legalmove() == true) //check if the move is legal, if so swap & assign new value to track blank tile //
    {
        int temp_i = tile_row;
        int temp_j = tile_col;
        swap(&board[tile_row][tile_col], &board[blank_row][blank_col]);
        blank_row = temp_i;
        blank_col = temp_j;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter = 1;
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (board[row][col] == counter) // count up through array to check values //
            {
                counter++;
                if (counter == d*d && board[d-1][d-1] == 0) // checks if last tile is blank //
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void swap(int* a, int* b) // * swap function used throughout //
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int tileSearch(int tile)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile) // once tile is found assign tile_row tile_col to i and j values //
            {
                tile_row = i;
                tile_col = j;
            }
        }
    }
    return 1;
}

bool legalmove(void) // looks to see if blank tile is adjacent to user's chosen tile //
{
    if (tile_row > 0 && board[tile_row-1][tile_col] == 0) // check above //
    {
        return true;
    }
    else if (tile_row < (d-1) && board[tile_row+1][tile_col] == 0) // check below //
    {
        return true;
    }
    else if (tile_col > 0 && board[tile_row][tile_col-1] == 0) // check left //
    {
        return true;
    }
    else if (tile_col < (d-1) && board[tile_row][tile_col+1] == 0) // check right //
    {
        return true;
    }
    else
    {
    return false;
    }
}