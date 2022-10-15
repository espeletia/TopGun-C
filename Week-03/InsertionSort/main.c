#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int size);
void insertionSort(int arr[], int n);

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
    insertionSort(arr, size);
    printArray(arr, size);
    return 0;
    
}
 
void insertionSort(int arr[], int n)
{
   int x, y;
   for (int i = 1; i < n; i++)
   {
        x = arr[i];
        y = i - 1;

        while (y >= 0 && arr[y] > x)    
        {
            arr[y + 1] = arr[y];
            y--; 
        }
        arr[y + 1] = x;
   }
   
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d\n", arr[i]);
}