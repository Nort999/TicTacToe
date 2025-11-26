#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

typedef struct
{
    int X, O;
} Score;

static void initBoard(char b[][MAX_SIZE], int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            b[i][j] = ' ';
}

static void printBoard(char b[][MAX_SIZE], int n)
{
    putchar('\n');
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf(" %c ", b[i][j]);
            if (j < n - 1)
                putchar('|');
        }
        putchar('\n');
        if (i < n - 1)
        {
            for (int j = 0; j < n; ++j)
            {
                printf("---");
                if (j < n - 1)
                    putchar('+');
            }
            putchar('\n');
        }
    }
    putchar('\n');
}

static int checkWin(char b[][MAX_SIZE], int n)
{
    // rows & cols
    for (int i = 0; i < n; ++i)
    {
        char r = b[i][0], c = b[0][i];
        int row_ok = (r != ' '), col_ok = (c != ' ');
        for (int j = 1; j < n && (row_ok || col_ok); ++j)
        {
            if (row_ok && b[i][j] != r)
                row_ok = 0;
            if (col_ok && b[j][i] != c)
                col_ok = 0;
        }
        if (row_ok && r != ' ')
            return (r == 'X') ? 2 : 1;
        if (col_ok && c != ' ')
            return (c == 'X') ? 2 : 1;
    }
    // diag TL-BR
    char d = b[0][0];
    int diag_ok = (d != ' ');
    for (int i = 1; i < n && diag_ok; ++i)
        if (b[i][i] != d)
            diag_ok = 0;
    if (diag_ok && d != ' ')
        return (d == 'X') ? 2 : 1;
    // diag TR-BL
    d = b[0][n - 1];
    diag_ok = (d != ' ');
    for (int i = 1; i < n && diag_ok; ++i)
        if (b[i][n - 1 - i] != d)
            diag_ok = 0;
    if (diag_ok && d != ' ')
        return (d == 'X') ? 2 : 1;
    return 0;
}

static int boardFull(char b[][MAX_SIZE], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (b[i][j] == ' ')
                return 0;
    return 1;
}

static void playerMove(char b[][MAX_SIZE], int n, char mark)
{
    int r, c;
    while (1)
    {
        printf("Player %c - enter row and column (1-%d): ", mark, n);
        if (scanf("%d%d", &r, &c) != 2)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input\n");
            continue;
        }
        if (r < 1 || r > n || c < 1 || c > n)
        {
            printf("Out of range\n");
            continue;
        }
        if (b[r - 1][c - 1] != ' ')
        {
            printf("Cell taken\n");
            continue;
        }
        b[r - 1][c - 1] = mark;
        break;
    }
}

static void aiMove(char b[][MAX_SIZE], int n, char mark)
{
    int attempts = 0;
    while (attempts++ < 500)
    {
        int r = rand() % n, c = rand() % n;
        if (b[r][c] == ' ')
        {
        } // no-op to placate some linters
        if (b[r][c] == ' ')
        {
            b[r][c] = mark;
            return;
        }
    }
    // fallback linear scan
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (b[i][j] == ' ')
            {
                b[i][j] = mark;
                return;
            }
}

int main(void)
{
    srand((unsigned)time(NULL));
    int mode, n;
    Score score = {0, 0};
    char board[MAX_SIZE][MAX_SIZE];

    printf("Tic-Tac-Toe (3-%d)\n1) PvP  2) PvAI\nMode: ", MAX_SIZE);
    if (scanf("%d", &mode) != 1)
        return 0;
    printf("Grid size: ");
    if (scanf("%d", &n) != 1 || n < 3 || n > MAX_SIZE)
        return 0;

    int play = 1;
    while (play)
    {
        initBoard(board, n);
        int turn = 0; // 0 => X, 1 => O
        int winner = 0;
        while (!winner && !boardFull(board, n))
        {
            printBoard(board, n);
            if (turn == 0)
                playerMove(board, n, 'X');
            else
            {
                if (mode == 1)
                    playerMove(board, n, 'O');
                else
                {
                    printf("AI (O) is thinking...\n");
                    aiMove(board, n, 'O');
                }
            }
            winner = checkWin(board, n);
            turn = 1 - turn;
        }
        printBoard(board, n);
        if (winner == 2)
        {
            printf("X wins\n");
            score.X++;
        }
        else if (winner == 1)
        {
            printf("O wins\n");
            score.O++;
        }
        else
            printf("Draw\n");
        printf("Score: X=%d O=%d\nPlay again? (1=yes,0=no): ", score.X, score.O);
        if (scanf("%d", &play) != 1)
            break;
    }
    return 0;
}