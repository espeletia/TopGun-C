#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Person
{
    int ID;
    int year;
    int month;
    int day;
    char *name;
    char *surname;
} Person;

int binarysearch(Person array[], int l, int r, Person x);
char *getln();
char *getlen();
int comparePpl(Person person1, Person person2);

int main()
{
    int size;
    scanf("%d", &size);
    Person *arr = (Person *)malloc(sizeof(Person) * size);
    /*FIRST PHASE OF ENTRY*/
    int ID;
    char property;
    for (int i = 0; i < size; i++) // O(5n)
    {
        for (int j = 0; j < 5; j++)
        {
            scanf("%d %c", &ID, &property);

            switch (property)
            {
            case 'y':
                scanf("%d", &arr[ID].year);
                break;
            case 'm':
                scanf("%d", &arr[ID].month);
                break;
            case 'd':
                scanf("%d", &arr[ID].day);
                break;
            case 'f':
                arr[ID].name = getln();
                break;
            case 'l':
                arr[ID].surname = getln();
                break;
            default:
                printf("INVALID INPUT");
                return 0;
                break;
            }
        }
        arr[i].ID = i;
    }
    /* SECOND PHASE OF ENTRY*/
    Person search;
    while (scanf("%d %d %d", &search.year, &search.month, &search.day) != EOF) // q
    {
        search.name = getln();
        search.surname = getlen();
        int x = binarysearch(arr, 0, size - 1, search); // log (n)
        if (x == -1)
        {
            printf("Not found\n");
            continue;
        }
        if (strcmp(arr[x].name, search.name) == 0 && strcmp(arr[x].surname, search.surname) == 0)
        {
            printf("Found, %d %s %s\n", arr[x].ID, arr[x].name, arr[x].surname);
            continue;
        }
        else
        {
            printf("Not found\n");
            continue;
        }
    }
    free(arr);
    return 0;
}

int comparePpl(Person person1, Person person2)
{
    if (person1.year == person2.year)
    {
        if (person1.month == person2.month)
        {
            if (person1.day == person2.day)
            {
                if (strcmp(person1.name, person2.name) == 0)
                {
                    if (strcmp(person1.surname, person2.surname) == 0)
                        return 0;

                    return (strcmp(person1.surname, person2.surname) > 0) ? 1 : 2;
                }
                return (strcmp(person1.name, person2.name) > 0) ? 1 : 2;
            }
            return (person1.day > person2.day) ? 1 : 2;
        }
        return (person1.month > person2.month) ? 1 : 2;
    }
    return (person1.year > person2.year) ? 1 : 2;
}

int binarysearch(Person array[], int l, int r, Person x)
{
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (comparePpl(array[m], x) == 0)
            return m;
        if (comparePpl(array[m], x) == 2)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

char *getln()
{
    char x;
    int size = 1;
    char *temp = NULL;
    getc(stdin);
    while ((x = getc(stdin)) && x != '\n' && x != EOF && x != ' ')
    {

        size++;
        temp = realloc(temp, size);
        temp[size - 2] = x;
        temp[size - 1] = '\0';
    }
    return temp;
}
char *getlen()
{
    char x;
    int size = 1;
    char *temp = NULL;
    while ((x = getc(stdin)) && x != '\n' && x != EOF && x != ' ')
    {

        size++;
        temp = realloc(temp, size);
        temp[size - 2] = x;
        temp[size - 1] = '\0';
    }
    return temp;
}