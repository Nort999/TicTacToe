#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define SIZE 10

struct XandO
{
    int scoreX;
    int scoreO;
    int checkX;
    int checkO;
};
typedef struct
{
    int games_played;
    int wins_player1;
    int wins_player2;
    int draws;
    int *win_patterns;
    int pattern_count;
    int pattern_capacity;
} GameStats;
GameStats *createGameStats()
{
    GameStats *stats = malloc(sizeof(GameStats));
    stats->games_played = 0;
    stats->wins_player1 = 0;
    stats->wins_player2 = 0;
    stats->draws = 0;
    stats->pattern_capacity = 10;
    stats->pattern_count = 0;

    stats->win_patterns = malloc(sizeof(int) * stats->pattern_capacity);
    return stats;
}
void updateStats(GameStats *stats, char winner, int win_type)
{
    stats->games_played++;

    if (winner == 'X')
        stats->wins_player1++;
    else if (winner == 'O')
        stats->wins_player2++;
    else if (winner == 'D')
        stats->draws++;

    if (winner == 'X' || winner == 'O')
    {
        if (stats->pattern_count >= stats->pattern_capacity)
        {
            stats->pattern_capacity *= 2;
            stats->win_patterns =
                realloc(stats->win_patterns, sizeof(int) * stats->pattern_capacity);
        }

        stats->win_patterns[stats->pattern_count++] = win_type;
    }
}
void printStatistics(const GameStats *stats)
{
    printf("\n===== GAME STATISTICS =====\n");
    printf("Total Games Played : %d\n", stats->games_played);
    printf("Player X Wins      : %d\n", stats->wins_player1);
    printf("Player O Wins      : %d\n", stats->wins_player2);
    printf("Draws              : %d\n", stats->draws);

    printf("\nWin Pattern History:\n");
    for (int i = 0; i < stats->pattern_count; i++)
        printf(" Game %d → Pattern %d\n", i + 1, stats->win_patterns[i]);
}
void freeGameStats(GameStats *stats)
{
    free(stats->win_patterns);
    free(stats);
}
void makeGrid(char array[][SIZE], int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf(" %c ", array[i][j]);
            if (j < size - 1)
                printf("|");
        }
        printf("\n");
        for (int k = 0; k < size; k++)
        {
            if (i < size - 1)
            {
                printf("---");
                if (k != size - 1)
                    printf("+");
            }
        }
        printf("\n");
    }
}
int CheckWin(char arr[][SIZE], int S, char mark)
{
    int count;

    // Horizontal
    for (int r = 0; r < S; r++)
    {
        count = 0;
        for (int c = 0; c < S; c++)
            if (arr[r][c] == mark)
                count++;
        if (count == S)
            return 1;
    }

    // Vertical
    for (int c = 0; c < S; c++)
    {
        count = 0;
        for (int r = 0; r < S; r++)
            if (arr[r][c] == mark)
                count++;
        if (count == S)
            return 2;
    }

    // Diagonal TL→BR
    count = 0;
    for (int i = 0; i < S; i++)
        if (arr[i][i] == mark)
            count++;
    if (count == S)
        return 3;

    // Diagonal TR→BL
    count = 0;
    for (int i = 0; i < S; i++)
        if (arr[i][S - 1 - i] == mark)
            count++;
    if (count == S)
        return 4;

    return 0;
}
int CheckWinX(char arr[][SIZE], int S) { return CheckWin(arr, S, 'X'); }
int CheckWinO(char arr[][SIZE], int S) { return CheckWin(arr, S, 'O'); }
int spaceCheck(char array[][SIZE], int x, int y)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
    {
        printf("Coordinates out of bounds.\n");
        return 1;
    }
    if (array[x][y] != ' ')
    {
        printf("That space is taken.\n");
        return 1;
    }
    return 0;
}
int AIspaceCheck(char array[][SIZE], int x, int y)
{
    return (x < 0 || x >= SIZE || y < 0 || y >= SIZE || array[x][y] != ' ');
}
int find_strategic_move(char array[][SIZE], int arraySize, char mark, int *moveX, int *moveY)
{
    // The win condition is a line of 'arraySize' marks.
    // We look for 'arraySize - 1' marks with one open spot to win or block.

    // --- 1. Check Horizontal Lines ---
    for (int r = 0; r < arraySize; r++)
    {
        int mark_count = 0;
        int empty_r = -1, empty_c = -1;

        // This inner loop needs to check for a contiguous line of SIZE-1 marks
        // This implementation checks a whole row/col for SIZE-1 marks, which is fine for small TTT but slow for larger.
        // Given the original structure, we maintain the original logic for simplicity.

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
void pvp(char array[][SIZE], int *turn, int size)
{
    int x, y;
    printf("\n--- Player vs Player ---\n");

    if (*turn == 0)
        printf("Player X turn\n");
    else
        printf("Player O turn\n");

    printf("Row Col: ");
    if (scanf("%d%d", &x, &y) != 2)
    {
        printf("Invalid input.\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (spaceCheck(array, x, y) == 0)
    {
        if (*turn == 0)
            array[x][y] = 'X';
        else
            array[x][y] = 'O';
        *turn = 1 - *turn;
    }
}
void pvAI(char array[][SIZE], int *turn, int size)
{
    int x, y, ai_x, ai_y;

    if (*turn == 0)
    {
        printf("\nPlayer X turn\n");
        printf("Row Col: ");

        if (scanf("%d%d", &x, &y) != 2)
        {
            printf("Invalid input.\n");
            while (getchar() != '\n')
                ;
            return;
        }

        if (spaceCheck(array, x, y) == 0)
        {
            array[x][y] = 'X';
            *turn = 1;
        }
    }
    else
    {
        printf("\nAI turn (O)\n");

        if (find_strategic_move(array, size, 'O', &ai_x, &ai_y))
        {
            array[ai_x][ai_y] = 'O';
        }
        else if (find_strategic_move(array, size, 'X', &ai_x, &ai_y))
        {
            array[ai_x][ai_y] = 'O';
        }
        else
        {
            do
            {
                ai_x = rand() % size;
                ai_y = rand() % size;
            } while (AIspaceCheck(array, ai_x, ai_y));

            array[ai_x][ai_y] = 'O';
        }

        *turn = 0;
    }
}
void reset(char array[][SIZE], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            array[i][j] = ' ';
}
struct XandO endGame(char array[][SIZE], int size, struct XandO var, int *gameon, GameStats *stats)
{
    int playAgain = 0;

    // Player X win
    if (var.checkX > 0)
    {
        printf("\nPlayer X wins! Pattern %d\n", var.checkX);
        var.scoreX++;

        updateStats(stats, 'X', var.checkX);

        printf("Play again? (1=yes 0=no): ");
        scanf("%d", &playAgain);

        if (playAgain)
            reset(array, size);
        else
            *gameon = 0;

        var.checkX = var.checkO = 0;
    }

    // Player O win
    if (var.checkO > 0)
    {
        printf("\nPlayer O wins! Pattern %d\n", var.checkO);
        var.scoreO++;

        updateStats(stats, 'O', var.checkO);

        printf("Play again? (1=yes 0=no): ");
        scanf("%d", &playAgain);

        if (playAgain)
            reset(array, size);
        else
            *gameon = 0;

        var.checkX = var.checkO = 0;
    }

    return var;
}
int main()
{
    int size, gamemode, gameon = 1, turn = 0;

    struct XandO var = {0, 0, 0, 0};
    GameStats *stats = createGameStats();

    srand(time(NULL));

    // Mode
    do
    {
        printf("\n1 = PvP\n2 = PvAI\nSelect: ");
        scanf("%d", &gamemode);
    } while (gamemode != 1 && gamemode != 2);

    // Board size
    do
    {
        printf("Enter board size (3–10): ");
        scanf("%d", &size);
    } while (size < 3 || size > 10);

    char array[SIZE][SIZE];
    reset(array, size);

    makeGrid(array, size);

    while (gameon)
    {
        if (gamemode == 1)
            pvp(array, &turn, size);
        else
            pvAI(array, &turn, size);

        var.checkX = CheckWinX(array, size);
        var.checkO = CheckWinO(array, size);

        makeGrid(array, size);

        var = endGame(array, size, var, &gameon, stats);
    }

    printf("\nFinal Score: X=%d  O=%d\n", var.scoreX, var.scoreO);
    printStatistics(stats);

    freeGameStats(stats);

    return 0;
}
