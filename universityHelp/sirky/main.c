#include <stdio.h>
#include <stdlib.h>

int is_solution(int *array, int n)
{
    // Check if all the sticks are either crosses or empty
    for (int i = 0; i < n; i++)
    {
        if (array[i] != 0 && array[i] != 2)
        {
            return 0; // not a solution
        }
    }

    return 1; // it is a solution
}
// helper function for debugging it can be removed
void printListSticks(int *array, int n)
{
    printf("CURRENT STICK ARRAY: ");
    for (int i = 0; i < n; i++)
    {
        switch (array[i])
        {
        case 0:
            printf(" , ");
            break;
        case 1:
            printf("|, ");
            break;
        case 2:
            printf("X, ");
            break;
        default:
            break;
        }
    }
    printf("\n");
}

int solutions = 0; //global variable

//find all solutions
void FindSolutions(int *array, int size, int skip, int *jumps, int *jumpOrientation, int jumpIndex)
{
    // printListSticks(array, size);

    if (is_solution(array, size))
    {
        solutions++;
        for (int i = 0; i < jumpIndex; i++)
        {
            if (i == jumpIndex - 1)
            {
                printf("%d", jumps[i]);
                if (jumpOrientation[i])
                    printf("R");
                else
                    printf("L");
                continue;
            }
            printf("%d", jumps[i]);
            if (jumpOrientation[i])
                printf("R,");
            else
                printf("L,");
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if (array[i] != 1)
        {
            // if this is not a stick, we skip it
            continue;
        }
        int landing = i;
        int valid = 1;
        // attempt to jump to the left
        for (int j = skip + 1; j > 0; j--)
        {
            landing--;
            if (landing < 0 || landing >= size)
            {
                // we are outside the bounds of the array so we mark this jump as invalid and break the loop
                valid = 0;
                break;
            }
            if (array[landing] == 0)
            {
                //an empty space doesn't count as a stick so we don't need to substract anything from the remaing skipabble sticks
                j++;
                continue;
            }
            if (array[landing] == 2)
            {
                //a cross is two sticks together so we substract another stick
                j--;
            }
        }

        if (array[landing] == 1 && valid == 1)
        {
            // making the jump
            array[landing] = 2;
            array[i] = 0;

            // storing the jump
            jumps[jumpIndex] = i;
            jumpOrientation[jumpIndex] = 0;
            
            
            FindSolutions(array, size, skip, jumps, jumpOrientation, jumpIndex + 1); // recursion

            // undoing the jump to test other possible solutions
            array[landing] = 1;
            array[i] = 1;
        }


        // if this index didn't jump to the left, we try to jump to the right, all the logic is the same

        landing = i;
        valid = 1;
        for (int j = skip + 1; j > 0; j--)
        {
            landing++;
            if (landing < 0 || landing >= size)
            {
                valid = 0;
                break;
            }
            if (array[landing] == 0)
            {
                j++;
                continue;
            }
            if (array[landing] == 2)
            {
                j--;
            }
        }
        if (array[landing] == 1 && valid == 1)
        {
            array[landing] = 2;
            array[i] = 0;
            jumps[jumpIndex] = i;
            jumpOrientation[jumpIndex] = 1;
            FindSolutions(array, size, skip, jumps, jumpOrientation, jumpIndex + 1);
            array[landing] = 1;
            array[i] = 1;
        }
    }

    return;
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
    int *jumps = (int *)malloc((size / 2) * sizeof(int));
    int *jumpOrientation = (int *)malloc((size / 2) * sizeof(int));

    FindSolutions(array, size, skip, jumps, jumpOrientation, 0);
    printf("Celkem reseni: %d\n", solutions);
    free(jumpOrientation);
    free(array);
    free(jumps);

    return 0;
}