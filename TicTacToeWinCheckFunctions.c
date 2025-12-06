#include <math.h>
#include <stdio.h>

// Note: The function signature requires array[][10] based on your original code
int CheckWinO(char array[][10], int arraySize)
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
        // Check for a full line win
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
}
int CheckWinX(char array[][10], int arraySize)//Repeat of CheckWinO modied for player X
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
            return 1;
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
            return 1;
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
        return 1;
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
        return 1;
    }
}
int main()
{
    char array[10][10] = {//testing purposes 
    {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O'}, // Row 0
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 1
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 2
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 3
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 4
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 5
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 6
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 7
    {'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // Row 8
    {'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X'}  // Row 9
};
    int boardSize = 10;
    CheckWinO(array, boardSize);
    CheckWInX(array,boardSize);

    return 0;
}
