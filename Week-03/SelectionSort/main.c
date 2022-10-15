#include <stdio.h>
#include <stdlib.h>
  
void selectionSort(int arr[], int n);
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
    }
    selectionSort(arr, size);
    printArray(arr, size);
    return 0;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void selectionSort(int arr[], int n)
{
    int i, j, min;
    for (i = 0; i < n-1; i++)
    {
        min = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min]) min = j;
        swap(&arr[min], &arr[i]);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d\n", arr[i]);
}
  

