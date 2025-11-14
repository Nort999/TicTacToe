
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10 // This is the total size of the array (10)

void makeGrid(char array[][SIZE], int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf(" %c ", array[i][j]);
            if (j < size - 1) // doesn't print the right-most line (aesthetics)
            {
                printf("|");
            }
        }
        printf("\n");
        for (int k = 0; k < size; k++)
        {
            if (i < size - 1) // doesn't print the bottom row (aesthetics)
            {
                printf("---");
                if (k != size - 1) // Doesn't print the right-most plus (aesthetics)
                    printf("+");
            }
        }
        printf("\n");
    }
}

int spaceCheck(char array[][SIZE], int x, int y)
{
    if (array[x - 1][y - 1] != ' ') // If the space is not blank, return 1
    {
        printf("That space is already taken, please choose another\n");
        return 1;
    }
    else
        return 0;
}

void pvp(char array[][SIZE], int *turn) // Player vs. PLayer function
{
    int x, y; // temporary variables (not really needed but if this isn't here there are error lines, but program still works)
    if (*turn == 0)
        printf("Player x's turn --> Place an X\n");
    else if (*turn == 1)
        printf("Player o's turn --> Place a O\n");
    printf("Example: Place at: 1 2\n");
    printf("Place at: ");
    int placecheck = scanf("%d%d", &y, &x);
    if (placecheck != 2) // makes sure that there are two inputs
    {
        printf("Invalid input\n");
    }
    int check = spaceCheck(array, x, y); // If one is returned, do not place anything, but also don't change the turn
    if (*turn == 0 && check == 0)
    {

        array[x - 1][y - 1] = 'x'; // the -1 is not needed, it just makes the placement more user-friendly
        *turn = 1;                 // changes turn to 1
    }
    else if (*turn == 1 && check == 0)
    {
        array[x - 1][y - 1] = 'o';
        *turn = 0; // changes turn to 0
    }
}

int main()
{
    int size = 3;                // This is the grid size wanted, should be user inputted
    char array[SIZE][SIZE];      // Array size must be defined for the makeGrid to work, SIZE is predefined
    for (int i = 0; i < 10; i++) // These for loops fill each space in the array, and this must be done for the makeGrid to work
    {
        for (int j = 0; j < 10; j++)
        {
            array[i][j] = ' ';
        }
    }

    int gamemode = 0;
    int gameon = 1;
    int turn = 0;

    // User inputs
    printf("\n=---------Tic-Tac-Toe---------=\n\n");
    printf("Player vs. Player: 1\n");
    printf("Player vs. AI: 2\n");
    printf("Gamemode: ");
    scanf("%d", &gamemode);

    printf("\nPlease enter one integer (3-10) for the size of the grid\n");
    printf("Example: Input 3 for a 3x3 grid size\n");
    printf("Grid Size: ");
    scanf("%d", &size);

    makeGrid(array, size);

    while (gameon == 1)
    {
        if (gamemode == 1) // Player vs. Player
        {
            printf("=---------Player vs. Player---------=\n\n");
            pvp(array, &turn); // Needs the array and the address of the turn, so the turn variable can be changed within the function
            makeGrid(array, size);

            // Need function for winning/losing to exit gameon
            // Need a function to keep score
        }
        else if (gamemode == 2)
        {
            printf("Under Construction");
        }
    }
    return 0;
}