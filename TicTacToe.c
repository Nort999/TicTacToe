
#include <stdio.h>

#define SIZE 10 // This is the total size of the array

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
    array[0][1] = 'x'; // Example for placement
    makeGrid(array, size);
    return 0;
}