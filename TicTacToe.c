
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10 // This is the total size of the array (10)

struct XandO
{
    int scoreX;
    int scoreO;
    int checkX;
    int checkO;
};

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
int CheckWinO(char array[10][10], int arraySize)
{
    int count = 0;

    // Check Horizontal Lines
    for (int x = 0; x < arraySize; x++)
    {
        count = 0;
        for (int j = 0; j < arraySize; j++)
        {
            if (array[x][j] == 'O')
            {
                count++;
            }
            // If it's not 'O', the line is broken. Reset count and break to next row.
            else
            {
                count = 0;
                break;
            }
        }
        // Check for a full line win (count == arraySize for standard TTT)
        if (count == arraySize)
        {
            printf("winner O");
            return 1;
        }
    }

    // Check Vertical Lines
    for (int x = 0; x < arraySize; x++)
    {
        count = 0;
        for (int j = 0; j < arraySize; j++)
        {
            if (array[j][x] == 'O')
            {
                count++;
            }
            else
            {
                count = 0;
                break; // Break and check next column (x)
            }
        }
        if (count == arraySize)
        {
            printf("winner O");
            return 1;
        }
    }

    // Check Diagonal (Top-Left to Bottom-Right)
    count = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i][i] == 'O')
        {
            count++;
        }
        else
        {
            count = 0; // If one element isn't 'O', this diagonal fails
            break;
        }
    }
    if (count == arraySize)
    {
        printf("winner O");
        return 1;
    }

    // Check Diagonal (Top-Right to Bottom-Left)
    count = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i][arraySize - 1 - i] == 'O')
        {
            count++;
        }
        else
        {
            count = 0; // If one element isn't 'O', this diagonal fails
            break;
        }
    }
    if (count == arraySize)
    {
        printf("winner O");
        return 1;
    }
    return 0;
}
int CheckWinX(char array[10][10], int arraySize)
{
    int count = 0;

    // Check Horizontal Lines
    for (int x = 0; x < arraySize; x++)
    {
        count = 0;
        for (int j = 0; j < arraySize; j++)
        {
            if (array[x][j] == 'X')
            {
                count++;
            }
            // If it's not 'O', the line is broken. Reset count and break to next row.
            else
            {
                count = 0;
                break;
            }
        }
        // Check for a full line win (count == arraySize for standard TTT)
        if (count == arraySize)
        {
            printf("winner X");
            return 2;
        }
    }

    // Check Vertical Lines
    for (int x = 0; x < arraySize; x++)
    {
        count = 0;
        for (int j = 0; j < arraySize; j++)
        {
            if (array[j][x] == 'X')
            {
                count++;
            }
            else
            {
                count = 0;
                break; // Break and check next column (x)
            }
        }
        if (count == arraySize)
        {
            printf("winner X");
            return 2;
        }
    }

    // Check Diagonal (Top-Left to Bottom-Right)
    count = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i][i] == 'X')
        {
            count++;
        }
        else
        {
            count = 0; // If one element isn't 'O', this diagonal fails
            break;
        }
    }
    if (count == arraySize)
    {
        printf("winner X");
        return 2;
    }

    // Check Diagonal (Top-Right to Bottom-Left)
    count = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i][arraySize - 1 - i] == 'X')
        {
            count++;
        }
        else
        {
            count = 0; // If one element isn't 'O', this diagonal fails
            break;
        }
    }
    if (count == arraySize)
    {
        printf("winner X");
        return 2;
    }
    return 0;
}
int spaceCheck(char array[][SIZE], int x, int y)
{
    if (array[x][y] != ' ') // If the space is not blank, return 1
    {
        printf("That space is already taken, please choose another\n");
        return 1;
    }
    else
        return 0;
}
int AIspaceCheck(char array[][SIZE], int x, int y) // under development
{
    if (array[x - 1][y - 1] != ' ') // If the space is not blank, return 1
    {
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

        array[x][y] = 'X'; // the -1 is not needed, it just makes the placement more user-friendly
        *turn = 1;         // changes turn to 1
    }
    else if (*turn == 1 && check == 0)
    {
        array[x][y] = 'O';
        *turn = 0; // changes turn to 0
    }
}
void pvAI(char array[][SIZE], int *turn, int size) // under development
{
    int x, y, check, randomX, randomY, checkAI;

    if (*turn == 0)
    {
        printf("Player x's turn --> Place an X\n");
        printf("Example: Place at: 1 2\n");
        printf("Place at: ");
        int placecheck = scanf("%d%d", &y, &x);
        if (placecheck != 2) // makes sure that there are two inputs
        {
            printf("Invalid input\n");
        }
        check = spaceCheck(array, x, y); // If one is returned, do not place anything, but also don't change the turn
    }
    else if (*turn == 1)
    {
        randomX = rand() % (size - 3 + 1) + 3;
        randomY = rand() % (size - 3 + 1) + 3;
        printf("AI's turn\n");
        checkAI = AIspaceCheck(array, randomX, randomY);
    }

    if (*turn == 0 && check == 0)
    {
        array[x - 1][y - 1] = 'x'; // the -1 is not needed, it just makes the placement more user-friendly
        *turn = 1;                 // changes turn to 1
    }
    else if (*turn == 1 && checkAI == 0)
    {
        array[randomX][randomY] = 'o';
        *turn = 0; // changes turn to 0
    }
}
void reset(char array[][SIZE], int size)
{
    for (int i = 0; i < size; i++) // These for loops fill each space in the array, and this must be done for the makeGrid to work
    {
        for (int j = 0; j < 10; j++)
        {
            array[i][j] = ' ';
        }
    }
}
void endGame(char array[][SIZE], int size, struct XandO var, int playAgain, int *gameon)
{
    if (var.checkO == 1)
    {
        printf(": Player O wins\n");
        var.scoreO++;
        printf("\nScore: X: %d --- O: %d", var.scoreX, var.scoreO);
        printf("\nEnter 1 to play again\nEnter 0 to exit\n");
        scanf("%d", &playAgain);
        if (playAgain == 1)
        {
            reset(array, size);
        }
        else if (playAgain == 0)
            *gameon = 0;
    }
    if (var.checkX == 2)
    {
        printf(": Player X wins");
        var.scoreX++;
        printf("\nScore: X: %d --- O: %d", var.scoreX++, var.scoreO++);
        printf("\nEnter 1 to play again\nEnter 0 to exit\n");
        scanf("%d", &playAgain);
        if (playAgain == 1)
        {
            reset(array, size);
        }
        else if (playAgain == 0)
            *gameon = 0;
    }
}
int main()
{
    int size; // This is the grid size wanted, should be user inputted
    int gamemode = 0, gameon = 1;
    int turn = 0, playAgain = 0;
    int checkx = 0, checko = 0, scorex = 0, scoreo = 0;
    struct XandO var;
    var.scoreX = 0;
    var.scoreO = 0;

    srand(time(NULL));

    // User inputs
    do
    {
        printf("\n=---------Tic-Tac-Toe---------=\n\n");
        printf("Player vs. Player: 1\n");
        printf("Player vs. AI: 2\n");
        printf("Gamemode: ");

        scanf("%d", &gamemode);
        if (gamemode != 1 && gamemode != 2)
        {
            printf("Invalid input try again");
        }

    } while (gamemode != 1 && gamemode != 2);
    do
    {
        printf("\nPlease enter one integer (3-10) for the size of the grid\n");
        printf("Example: Input 3 for a 3x3 grid size\n");
        printf("Grid Size: ");
        scanf("%d", &size);
        if (!(size >= 3 && size <= 10))
        {
            printf("Invalid input try again");
        }

    } while (!(size >= 3 && size <= 10));

    char array[SIZE][SIZE]; // Array size must be defined for the makeGrid to work, SIZE is predefined
    reset(array, size);

    makeGrid(array, size);

    while (gameon == 1)
    {
        if (gamemode == 1) // Player vs. Player
        {
            printf("=---------Player vs. Player---------=\n\n");
            pvp(array, &turn); // Needs the array and the address of the turn, so the turn variable can be changed within the function
            makeGrid(array, size);

            var.checkX = CheckWinX(array, size);
            var.checkO = CheckWinO(array, size);

            endGame(array, size, var, playAgain, &gameon);
        }
        else if (gamemode == 2)
        {
            printf("=---------Player vs. AI---------=\n\n");
            pvAI(array, &turn, size);
            makeGrid(array, size);
        }
    }
    return 0;
}