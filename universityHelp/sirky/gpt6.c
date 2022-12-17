#include <stdbool.h>
#include <stdio.h>

// Check if all the sticks are either crosses or empty
bool is_solution(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (array[i] != 0 && array[i] != 2)
        {
            return false; // not a solution
        }
    }

    return true; // it is a solution
}

// Recursive function to find all solutions to the puzzle
void FindSolutions(int *array, int size, int skip, int* jumps, int* jumpOrientation, int jumpIndex)
{
    // Check if the puzzle is solved
    if (is_solution(array, size))
    {
        printf("SOLVED\n");
        return;
    }

    // Make sure skip is not negative
    if (skip < 0)
    {
        return;
    }

    // Try making a move from each position in the array
    for (int index = 0; index < size; index++)
    {
        // Make sure index is within bounds
        if (index < 0 || index >= size)
        {
            continue;
        }

        // Try jumping to the left
        int landing = index;
        bool valid = true;
        for (int j = skip + 1; j > 0; j--)
        {
            // Make sure landing is within bounds
            landing--;
            if (landing < 0 || landing >= size)
            {
                valid = false;
                break;
            }
            if (array[landing] == 2)
            {
                j--;
            }
            if (array[landing] == 0)
            {
                j++;
            }
        }
        if (array[landing] == 1 && valid)
        {
            array[landing] = 2;
            array[index] = 0;
            jumps[jumpIndex] = index;
            jumpOrientation[jumpIndex] = 0;
            FindSolutions(array, size, skip, jumps, jumpOrientation, jumpIndex + 1);
            array[landing] = 1;
            array[index] = 1;
        }

        // Try jumping to the right
        landing = index;
        valid = true;
        for (int j = skip + 1; j > 0; j--)
        {
            // Make sure landing is within bounds
            landing++;
            if (landing < 0 || landing >= size)
            {
                valid = false;
                break;
            }
            if (array[landing] == 2)
            {
                j--;
            }
            if (array[landing] == 0)
            {
                j++;
            }
        }
        if (array[landing] == 1 && valid)
        {
            array[landing] = 2;
            array[index] = 0;
            jumps[jumpIndex] = index;
            jumpOrientation[jumpIndex] = 1;
            FindSolutions(array, size, skip, jumps, jumpOrientation, jumpIndex + 1);
            array[landing] = 1;
            array[index] = 1;
        }
    }
}

int main()
{
    int size, skip, check;
    printf("Pocet sirek:\n");
    check = (scanf("%d", &size));
    if ((size <= 0) || (check != 1))
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    printf("Velikost skoku:\n");
    check = (scanf("%d", &skip));
    if ((skip < 0) || (check != 1))
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    if (size % 2 != 0)
    {
        printf("Celkem reseni: 0\n");
        return 0;
    }
    int *array = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        array[i] = 1;
    }
    int *jumps = (int*)malloc(size * sizeof(int));
    int *jumpOrientation = (int*)malloc(size * sizeof(int));


    // for(int i = 0; i < size; i ++)FindSolutions(size, skip, i);
    FindSolutions(array, size, skip, jumps, jumpOrientation, 0);

    free(array);

    return 0;
}
