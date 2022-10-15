#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n);
void swap(int *xp, int *yp);
void printArray(int arr[], int size);

int main()
{
    int *arr = (int*) malloc(sizeof(int) * 1);
    int temp;
    int size = 0;
    while (scanf("%d", &temp) != EOF)
    {
        size ++;
        arr = realloc(arr, size * sizeof(int));
        arr[size - 1] = temp;
        //printf("%d", arr[size-1]);
    }
    bubbleSort(arr, size);
    printArray(arr, size);
    return 0;
    
}


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d\n", arr[i]);
}