#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10 // This is the total size of the array (10)
#define MAX_MOVES (SIZE * SIZE)

struct XandO // keeps the structure for the scoe
{
    int scoreX;
    int scoreO;
    int checkX;
    int checkO;
};
struct Move
{
    int row;
    int col;
    char player;
};
struct Move moveHistory[MAX_MOVES];
int moveCount = 0;
void makeGrid(char array[][SIZE], int size) // this function prints the grid with the given array information
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
void recordMove(int row, int col, char player)
{
    if (moveCount < MAX_MOVES)
    {
        moveHistory[moveCount].row = row;
        moveHistory[moveCount].col = col;
        moveHistory[moveCount].player = player;
        moveCount++;
    }
}
void replayGame(char array[][SIZE], int size)
{
    printf("\n--- Starting Game Replay ---\n");
    char tempArray[SIZE][SIZE];

    // Clear the temporary board
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tempArray[i][j] = ' ';
        }
    }

    // Replay each move one by one
    for (int i = 0; i < moveCount; i++)
    {
        int r = moveHistory[i].row;
        int c = moveHistory[i].col;
        char p = moveHistory[i].player;

        tempArray[r][c] = p; // Place the move on the temp board

        printf("\nMove %d: Player %c places at Row %d, Col %d\n", i + 1, p, r, c);
        makeGrid(tempArray, size);

        // Wait for user input to show the next move
        printf("Press ENTER to view next move...");
        // Clear potential leftover input, then wait for the ENTER key
        while (getchar() != '\n')
            ;
    }

    printf("\n--- Replay Finished ---\n");

    // Reset moveCount after replay
    moveCount = 0;
}
int CheckWinO(char array[10][10], int arraySize) // Checks if the 'O' player wins
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
            // If it's not 'O', the contiguous line is broken. Reset count and continue checking in the same row.
            else
            {
                count = 0;
            }
            if (count == arraySize) // Check for win inside the inner loop for efficiency in case of non-full-line TTT rules
            {
                printf("winner O");
                return 1;
            }
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
            }
            if (count == arraySize)
            {
                printf("winner O");
                return 1;
            }
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
            count = 0;
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
            count = 0;
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
int CheckWinX(char array[10][10], int arraySize) // Checks if the 'X' player wins
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
            // If it's not 'X', the contiguous line is broken. Reset count and continue checking in the same row.
            else
            {
                count = 0;
            }
            if (count == arraySize)
            {
                printf("winner X");
                return 2;
            }
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
            }
            if (count == arraySize)
            {
                printf("winner X");
                return 2;
            }
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
            count = 0;
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
            count = 0;
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
int spaceCheck(char array[][SIZE], int x, int y) // Bounds For invalid User input
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
    {
        printf("Coordinates are outside the grid boundaries.\n");
        return 1; // Treat out-of-bounds as taken/invalid
    }
    if (array[x][y] != ' ') // If the space is not blank, return 1
    {
        printf("That space is already taken, please choose another\n");
        return 1;
    }
    else
        return 0;
}
int find_strategic_move(char array[][SIZE], int arraySize, char mark, int *moveX, int *moveY)
{
    // This function will find the best move depending on the state of the board

    // The win condition is a line of 'arraySize' marks.
    // We look for 'arraySize - 1' marks with one open spot to win or block.

    // --- 1. Check Horizontal Lines ---
    for (int r = 0; r < arraySize; r++)
    {
        int mark_count = 0;
        int empty_r = -1, empty_c = -1;
        // Reset check variables for each row
        mark_count = 0;
        empty_r = -1;
        empty_c = -1;
        for (int c = 0; c < arraySize; c++)
        {
            if (array[r][c] == mark)
            {
                mark_count++;
            }
            else if (array[r][c] == ' ')
            {
                // Only track one empty spot
                if (empty_r == -1)
                {
                    empty_r = r;
                    empty_c = c;
                }
                else
                {
                    // More than one empty spot in a row means no immediate threat/win
                    mark_count = -100; // Force fail the check for this row
                    break;
                }
            }
            else
            {
                // Opponent mark breaks the potential line
                mark_count = -100; // Force fail the check for this row
                break;
            }
        }

        // Check if we found a line of (size - 1) marks and exactly one empty spot
        if (mark_count == arraySize - 1 && empty_r != -1)
        {
            *moveX = empty_r;
            *moveY = empty_c;
            return 1; // Found a winning/blocking move
        }
    }

    // --- 2. Check Vertical Lines ---
    for (int c = 0; c < arraySize; c++)
    {
        int mark_count = 0;
        int empty_r = -1, empty_c = -1;

        // Reset check variables for each column
        mark_count = 0;
        empty_r = -1;
        empty_c = -1;

        for (int r = 0; r < arraySize; r++)
        {
            if (array[r][c] == mark)
            {
                mark_count++;
            }
            else if (array[r][c] == ' ')
            {
                if (empty_r == -1)
                {
                    empty_r = r;
                    empty_c = c;
                }
                else
                {
                    mark_count = -100;
                    break;
                }
            }
            else
            {
                mark_count = -100;
                break;
            }
        }
        if (mark_count == arraySize - 1 && empty_r != -1)
        {
            *moveX = empty_r;
            *moveY = empty_c;
            return 1;
        }
    }

    // --- 3. Check Diagonal (Top-Left to Bottom-Right) ---
    int mark_count = 0;
    int empty_r = -1, empty_c = -1;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i][i] == mark)
        {
            mark_count++;
        }
        else if (array[i][i] == ' ')
        {
            if (empty_r == -1)
            {
                empty_r = i;
                empty_c = i;
            }
            else
            {
                mark_count = -100;
                break;
            }
        }
        else
        {
            mark_count = -100;
            break;
        }
    }
    if (mark_count == arraySize - 1 && empty_r != -1)
    {
        *moveX = empty_r;
        *moveY = empty_c;
        return 1;
    }

    // --- 4. Check Diagonal (Top-Right to Bottom-Left) ---
    mark_count = 0;
    empty_r = -1;
    empty_c = -1;
    for (int i = 0; i < arraySize; i++)
    {
        int j = arraySize - 1 - i;
        if (array[i][j] == mark)
        {
            mark_count++;
        }
        else if (array[i][j] == ' ')
        {
            if (empty_r == -1)
            {
                empty_r = i;
                empty_c = j;
            }
            else
            {
                mark_count = -100;
                break;
            }
        }
        else
        {
            mark_count = -100;
            break;
        }
    }
    if (mark_count == arraySize - 1 && empty_r != -1)
    {
        *moveX = empty_r;
        *moveY = empty_c;
        return 1;
    }

    return 0; // No strategic move found
}
int AIspaceCheck(char array[][SIZE], int x, int y)
{
    // Check bounds for AI-generated coordinates
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
    {
        return 1; // Out of bounds
    }
    if (array[x][y] != ' ') // If the space is not blank, return 1 (taken)
    {
        return 1;
    }
    else
        return 0; // Available
}
void pvp(char array[][SIZE], int *turn, int size) // Player vs. PLayer function
{
    int x, y;
    printf("=---------Player vs. Player---------=\n\n");
    if (*turn == 0)
        printf("Player X's turn --> Place an X\n");
    else if (*turn == 1)
        printf("Player O's turn --> Place an O\n");

    printf("Coordinates are 0 to %d.\n", size - 1);
    printf("Example: Place at: 0 1 (Row 0, Column 1)\n");
    printf("Place at (Row Col): ");

    // Check for valid number of inputs
    if (scanf("%d%d", &x, &y) != 2)
    {
        printf("Invalid input format. Turn skipped.\n");
        // Clear input buffer to prevent loop on next turn
        while (getchar() != '\n')
            ;
        return;
    }

    // Check bounds
    if (x < 0 || x >= size || y < 0 || y >= size)
    {
        printf("Coordinates (%d %d) are outside the grid boundaries (0 to %d).\n", x, y, size - 1);
        return;
    }

    // Check space
    if (spaceCheck(array, x, y) == 0) // If check returns 0 (space is free)
    {
        if (*turn == 0)
        {
            array[x][y] = 'X';
            recordMove(x, y, 'X');
            *turn = 1; // changes turn to 1 (O)
        }
        else if (*turn == 1)
        {
            array[x][y] = 'O';
            recordMove(x, y, 'O');
            *turn = 0; // changes turn to 0 (X)
        }
    }
}
void pvAI(char array[][SIZE], int *turn, int size)
{
    int x, y;       // Human input
    int ai_x, ai_y; // AI move

    printf("=---------Player vs. AI---------=\n\n");

    if (*turn == 0) // Human Player X's Turn
    {
        printf("Player X's turn --> Place an X\n");
        printf("Coordinates are 0 to %d.\n", size - 1);
        printf("Example: Place at: 0 1 (Row 0, Column 1)\n");
        printf("Place at (Row Col): ");

        // Check for valid number of inputs
        if (scanf("%d%d", &x, &y) != 2)
        {
            printf("Invalid input format. Turn skipped.\n");
            // Clear input buffer to prevent loop on next turn
            while (getchar() != '\n')
                ;
            return;
        }

        // Check bounds
        if (x < 0 || x >= size || y < 0 || y >= size)
        {
            printf("Coordinates (%d %d) are outside the grid boundaries (0 to %d).\n", x, y, size - 1);
            return;
        }

        // Check space
        if (spaceCheck(array, x, y) == 0)
        {
            array[x][y] = 'X';
            recordMove(x, y, 'X');
            *turn = 1; // Change turn to AI
        }
    }
    else if (*turn == 1) // AI Player O's Turn
    {
        printf("Player AI's turn --> Place an O\n");

        // 1. Check for AI winning move ('O')
        if (find_strategic_move(array, size, 'O', &ai_x, &ai_y)) // Stratigic move for O since O is the  ai and will place it at the winning move
        {
            array[ai_x][ai_y] = 'O';
            recordMove(ai_x, ai_y, 'O');
        }
        // 2. Check for human player winning move (Block 'X')
        else if (find_strategic_move(array, size, 'X', &ai_x, &ai_y)) // Stratigic move for X since the ai is trying to find the best place X(the player) can go and stop it
        {
            array[ai_x][ai_y] = 'O';
            recordMove(ai_x, ai_y, 'O');
        }
        // 3. Random move
        else
        {
            do
            {
                ai_x = rand() % size;
                ai_y = rand() % size;
            } while (AIspaceCheck(array, ai_x, ai_y) != 0);

            array[ai_x][ai_y] = 'O';
            recordMove(ai_x, ai_y, 'O');
        }
        *turn = 0; // Change turn to human
    }
}
void reset(char array[][SIZE], int size)
{ // Reset the board
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) // Loop up to size, not SIZE
        {
            array[i][j] = ' ';
        }
    }
}
struct XandO endGame(char array[][SIZE], int size, struct XandO var, int *gameon)
{
    int playAgain = 0; // Local variable for user input
    int gameEnded = 0;
    // Player O Win Check
    if (var.checkO == 1) // Use . to access struct members
    {
        printf(": Player O wins\n");
        var.scoreO++; // Increment the score on the local copy
        printf("\nScore: X: %d --- O: %d\n", var.scoreX, var.scoreO);

        // Prompt to play again
        printf("\nEnter 1 to play again\nEnter 0 to exit\n");
        if (scanf("%d", &playAgain) != 1)
        {
            playAgain = 0;
            while (getchar() != '\n')
                ; // Clear buffer
        }

        if (playAgain == 1)
        {
            reset(array, size);
            var.checkO = 0; // Reset win condition
            var.checkX = 0;
        }
        else if (playAgain == 0)
            *gameon = 0;
        gameEnded = 1;
    }

    // Player X Win Check
    if (var.checkX == 2) // Use . to access struct members
    {
        printf(": Player X wins\n");
        var.scoreX++; // Increment the score on the local copy
        printf("\nScore: X: %d --- O: %d\n", var.scoreX, var.scoreO);

        // Prompt to play again
        printf("\nEnter 1 to play again\nEnter 0 to exit\n");
        if (scanf("%d", &playAgain) != 1)
        {
            playAgain = 0;
            while (getchar() != '\n')
                ; // Clear buffer
        }

        if (playAgain == 1)
        {
            reset(array, size);
            var.checkO = 0; // Reset win condition
            var.checkX = 0;
        }
        else if (playAgain == 0)
            *gameon = 0;
        gameEnded = 1;
    }

    if (gameEnded)
    {
        // Clear leftover buffer from score prompt
        while (getchar() != '\n')
            ;

        printf("\nDo you want to see the replay? (1 for Yes, 0 for No): ");
        int doReplay = 0;
        if (scanf("%d", &doReplay) != 1)
        {
            while (getchar() != '\n')
                ;
        }

        if (doReplay == 1)
        {
            replayGame(array, size);
        }

        // After replay, prompt to play again
        printf("\nEnter 1 to play again\nEnter 0 to exit\n");
        if (scanf("%d", &playAgain) != 1)
        {
            playAgain = 0;
            while (getchar() != '\n')
                ; // Clear buffer
        }

        if (playAgain == 1)
        {
            reset(array, size);
            var.checkO = 0; // Reset win condition
            var.checkX = 0;
            // The moveCount is reset inside replayGame, so we don't need to do it here again.
        }
        else if (playAgain == 0)
            *gameon = 0;
    }

    return var; // Return the modified struct back to main
}
int main()
{
    int size = 0;
    int gamemode = 0, gameon = 1;
    int turn = 0;
    struct XandO var;
    var.scoreX = 0;
    var.scoreO = 0;
    var.checkX = 0;
    var.checkO = 0;

    srand(time(NULL));

    // User inputs for gamemode
    do
    {
        printf("\n=---------Tic-Tac-Toe---------=\n\n");
        printf("Player vs. Player: 1\n");
        printf("Player vs. AI: 2\n");
        printf("Gamemode: ");

        if (scanf("%d", &gamemode) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            gamemode = 0; // Reset gamemode
            while (getchar() != '\n')
                ; // Clear input buffer
        }
        else if (gamemode != 1 && gamemode != 2)
        {
            printf("Invalid gamemode input. Try again.\n");
        }

    } while (gamemode != 1 && gamemode != 2);

    // User inputs for size
    do
    {
        printf("\nPlease enter one integer (3-10) for the size of the grid\n");
        printf("Grid Size: ");

        if (scanf("%d", &size) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            size = 0; // Reset size
            while (getchar() != '\n')
                ; // Clear input buffer
        }
        else if (!(size >= 3 && size <= SIZE)) // SIZE is 10
        {
            printf("Invalid size input. Try again.\n");
        }

    } while (!(size >= 3 && size <= SIZE));

    char array[SIZE][SIZE];
    reset(array, size);

    makeGrid(array, size);

    while (gameon == 1)
    {
        if (gamemode == 1) // Player vs. Player
        {
            pvp(array, &turn, size);
        }
        else if (gamemode == 2) // Player vs. AI
        {
            pvAI(array, &turn, size);
        }

        // Check win conditions after every move
        var.checkX = CheckWinX(array, size);
        var.checkO = CheckWinO(array, size);

        makeGrid(array, size);

        var = endGame(array, size, var, &gameon);
    }

    printf("\n--- Final Score ---\n");
    printf("Player X: %d\n", var.scoreX);
    printf("Player O: %d\n", var.scoreO);
    printf("-------------------\n");

    return 0;
}
