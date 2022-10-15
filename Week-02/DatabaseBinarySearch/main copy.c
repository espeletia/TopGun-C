#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Person{
    int ID;
    int year;
    int month;
    int day;
    char name[16];
    char surname[16];
} Person;

int binarySearch(Person array[], int l, int r, int x);

int main(int argc, char const *argv[])
{
    int size;
    scanf("%d", &size); // get the size of the list
    //printf("\n%d\n", size);
    Person *arr = (Person*) malloc(sizeof(Person) * size); //allocate dynamic memory for a list of structs
    /*FIRST PHASE OF ENTRY*/
    int ID;
    char property;
    for (int i = 0; i < size; i++)//O(5n)
    {
        for (int j = 0; j < 5; j++)
    {
        scanf("%d %c", &ID, &property);
        //printf("%c\n", property);
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
            scanf("%s", arr[ID].name);
            break;
        case 'l':
            scanf("%s", arr[ID].surname);
            break;
        default:
            printf("INVALID INPUT");
            return 0;
            break;
        }
    }
        arr[i].ID = i;

        //printf("%d %d %d %d %s %s\n",arr[i].ID, arr[i].year, (arr + i)->month, (arr + i)->day, arr[i].name, arr[i].surname);
    }
    /* SECOND PHASE OF ENTRY*/
    Person search;
    while (scanf("%d %d %d %s %s", &search.year,&search.month,&search.day,search.name,search.surname) != EOF) // q
    {
        //printf(" %d %d %d %s %s\n",search.year, search.month, search.day, search.name, search.surname);

        int x = binarySearch(arr, 0, size - 1, search.year); //log (n)
        if (x == -1)
        {
            printf("Not found\n");
            continue;
        }
        
        if(arr[x].month == search.month && arr[x].day == search.day && strcmp(arr[x].name, search.name) == 0, strcmp(arr[x].surname, search.surname) == 0){
            printf("Found, %d %s %s\n", arr[x].ID, arr[x].name, arr[x].surname);
            continue;
        }
        else{
            
             printf("Not found\n");


        }
        
        
        

    }
    free(arr);
    

    

    return 0;
}

int binarySearch(Person array[], int l, int r, int x){
        while (l <= r)
        {
            int m = l + (r - l);
            if(array[m].year == x) return m;
            if(array[m].year < x) l = m + 1;
            else r = m - 1;
        }
        return -1;
    }



/*NOTES*/
/*
Restructure the code, use dynamic sized structs since the size of a Person is locked to be the sum of the size of all components
first allocate the memory for both strings and then allocate the rest of the struct and append it to an array
us the function realloc(), it might help

*/