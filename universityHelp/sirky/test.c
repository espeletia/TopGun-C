#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int index;
    int direction;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
} LinkedList;

LinkedList *createLinkedList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void appendToLinkedList(LinkedList *list, int index, int direction)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->index = index;
    newNode->direction = direction;
    newNode->next = NULL;
    if (list->tail == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void freeLinkedList(LinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

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

int solutions = 0; // global variable

void FindSolutions(int *array, int size, int skip, LinkedList *list)
{
    if (is_solution(array, size))
    {
        solutions++;
        Node *current = list->head;
        while (current != NULL)
        {
            printf("%d", current->index);
            if (current->direction)
                printf("R");
            else
                printf("L");
            current = current->next;
            if (current != NULL)
                printf(",");
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
                // an empty space doesn't count as a stick so we don't need to substract anything from the remaing skipabble sticks
                j++;
                continue;
            }
            if (array[landing] == 2)
            {
                // a cross is two sticks together so we substract another stick
                j--;
            }
        }
        if (landing < 0 || landing >= size)
            valid = 0;
        if (valid)
        {
            if (array[landing] == 1)
            {
                // making the jump
                array[landing] = 2;
                array[i] = 0;

                // storing the jump
                appendToLinkedList(list, i, 0);

                FindSolutions(array, size, skip, list); // recursion

                // undoing the jump to test other possible solutions
                array[landing] = 1;
                array[i] = 1;
                // removing the last jump from the list
                if (list->tail == list->head)
                {
                    free(list->head);
                    list->head = NULL;
                    list->tail = NULL;
                }
                else
                {
                    Node *current = list->head;
                    while (current->next != list->tail)
                    {
                        current = current->next;
                    }
                    free(list->tail);
                    current->next = NULL;
                    list->tail = current;
                }
            }
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
        if (landing < 0 || landing >= size)
            valid = 0;
        if (valid)
        {
            if (array[landing] == 1)
            {
                // making the jump
                array[landing] = 2;
                array[i] = 0;

                // storing the jump
                appendToLinkedList(list, i, 1);

                FindSolutions(array, size, skip, list); // recursion

                // undoing the jump to test other possible solutions
                array[landing] = 1;
                array[i] = 1;
                // removing the last jump from the list
                if (list->tail == list->head)
                {
                    free(list->head);
                    list->head = NULL;
                    list->tail = NULL;
                }
                else
                {
                    Node *current = list->head;
                    while (current->next != list->tail)
                    {
                        current = current->next;
                    }
                    free(list->tail);
                    current->next = NULL;
                    list->tail = current;
                }
            }
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

    // creating a linked list to store the solution jumps
    LinkedList *list = createLinkedList();

    // finding all possible solutions
    FindSolutions(array, size, skip, list);

    // printing the number of solutions found
    printf("Celkem reseni: %d\n", solutions);

    // freeing the linked list
    freeLinkedList(list);
    free(array);

    return 0;
}