#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int size);
void quickSort(int arr[], int l, int r);
int partition(int arr[], int l, int r);
void swap(int *xp, int *yp);


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
    quickSort(arr, 0, size - 1);
    printArray(arr, size);
    return 0;
    
}

int partition(int arr[], int l, int r){
    
    int pivot = arr[r];

    int i = (l - 1);

    for (int j = l; j < r; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
        
    }
    
    swap(&arr[i + 1], &arr[r]);
    return i + 1;
}
 
void quickSort(int arr[], int l, int r)
{
   if(l < r){
       int m = partition(arr, l, r);

       quickSort(arr, l, m - 1);
       quickSort(arr, m + 1, r);
   }
   
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d\n", arr[i]);
}


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}